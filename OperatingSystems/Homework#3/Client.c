#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const int CONNECT = 0;
const int SEND_MSG = 1;
const int RECEIVE_MSG = 2;

void send_message(int pipe_fd, int type, const char *data)
{
    int length = strlen(data);
    char buffer[1024] = {0};
    snprintf(buffer, sizeof(buffer), "%d %d %d %d %s", getpid(), SEND_MSG, type, length, data);
    write(pipe_fd, buffer, strlen(buffer));
}

void receive_message(int pipe_fd, int client_pipe_fd, int requested_type)
{
    char buffer[1024] = {0};
    snprintf(buffer, sizeof(buffer), "%d %d %d", getpid(), RECEIVE_MSG, requested_type);
    write(pipe_fd, buffer, strlen(buffer));

    memset(buffer, 0, sizeof(buffer));
    int flags = fcntl(client_pipe_fd, F_GETFL, 0);
    fcntl(client_pipe_fd, F_SETFL, flags & ~O_NONBLOCK);
    read(client_pipe_fd, buffer, sizeof(buffer));
    fcntl(client_pipe_fd, F_SETFL, flags);

    int type, length;
    char data[256];
    sscanf(buffer, "%d %d %[^\n]", &type, &length, data);

    if (type != -1)
    {
        printf("Client %d received a message (type: %d, data: %s)\n", getpid(), type, data);
    }
    else
    {
        printf("Client %d requested type %d, but no message was available.\n", getpid(), requested_type);
    }
}

int main()
{
    const char *pipe_name = "server_pipe";
    int pipe_fd = open(pipe_name, O_WRONLY);

    if (pipe_fd < 0)
    {
        perror("Error opening pipe");
        exit(1);
    }

    // Create unique pipe name for each client
    char client_pipe_name[256];
    snprintf(client_pipe_name, sizeof(client_pipe_name), "client_pipe_%d", getpid());
    mkfifo(client_pipe_name, 0666);
    int client_pipe_fd = open(client_pipe_name, O_RDONLY | O_NONBLOCK);
    char buffer[1024] = {0};
    snprintf(buffer, sizeof(buffer), "%d %d", getpid(), CONNECT);
    write(pipe_fd, buffer, strlen(buffer));
    while (1)
    {
        printf("\nOptions:\n");
        printf("1. Send message\n");
        printf("2. Receive message\n");
        printf("3. Quit\n");

        int option;
        printf("Enter your option: ");
        scanf("%d", &option);

        if (option == 1)
        {
            int type;
            char data[256];
            printf("Message Types: 0:int 1:char/string 2: ");
            printf("Enter message type(): ");
            scanf("%d", &type);
            printf("Enter message data: ");
            getchar(); // Consume newline character
            fgets(data, sizeof(data), stdin);
            data[strcspn(data, "\n")] = 0; // Remove newline character
            send_message(pipe_fd, type, data);
        }
        else if (option == 2)
        {
            int requested_type;
            printf("Enter requested message type (negative for types less than or equal to X): ");
            scanf("%d", &requested_type);
            receive_message(pipe_fd, client_pipe_fd, requested_type);
        }
        else if (option == 3)
        {
            break;
        }
        else
        {
            printf("Invalid option.\n");
        }
    }

    close(pipe_fd);
    close(client_pipe_fd);
    unlink(client_pipe_name);

    return 0;
}