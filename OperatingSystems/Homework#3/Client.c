#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const int SEND_MSG = 1;
const int RECEIVE_MSG = 2;

void send_message(int pipe_fd, int type, const char *data) {
    int length = strlen(data);
    char buffer[1024] = {0};
    snprintf(buffer, sizeof(buffer), "%d %d %d %d %s", getpid(), SEND_MSG, type, length, data);
    write(pipe_fd, buffer, strlen(buffer));
}

void receive_message(int pipe_fd, int requested_type) {
    char buffer[1024] = {0};
    snprintf(buffer, sizeof(buffer), "%d %d %d", getpid(), RECEIVE_MSG, requested_type);
    write(pipe_fd, buffer, strlen(buffer));

    memset(buffer, 0, sizeof(buffer));
    read(pipe_fd, buffer, sizeof(buffer));

    int type, length;
    char data[256];
    sscanf(buffer, "%d %d %[^\n]", &type, &length, data);

    if (type != -1) {
        printf("Client %d received a message (type: %d, data: %s)\n", getpid(), type, data);
    } else {
        printf("Client %d requested type %d, but no message was available.\n", getpid(), requested_type);
    }
}

int main() {
    const char *pipe_name = "server_pipe";
    int pipe_fd = open(pipe_name, O_RDWR);

    if (pipe_fd < 0) {
        perror("Error opening pipe");
        exit(1);
    }

    // Example usage:
    // Send a message with type 1 and data "Hello"
    send_message(pipe_fd, 1, "Hello");

    // Receive a message with type 1
    receive_message(pipe_fd, 1);

    close(pipe_fd);

    return 0;
}
