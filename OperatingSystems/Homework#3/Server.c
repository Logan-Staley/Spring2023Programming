#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

typedef struct {
    int type;
    int length;
    char *data;
} Message;

typedef struct QueueNode {
    Message message;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* head;
    QueueNode* tail;
} Queue;

Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

bool is_empty(Queue* queue) {
    return queue->head == NULL;
}

void enqueue(Queue* queue, Message message) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->message = message;
    node->next = NULL;

    if (is_empty(queue)) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
}

Message dequeue(Queue* queue) {
    if (is_empty(queue)) {
        Message empty_message = {-1, 0, ""};
        return empty_message;
    }

    QueueNode* node = queue->head;
    Message message = node->message;
    queue->head = node->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(node);
    return message;
}

void delete_queue(Queue* queue) {
    while (!is_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}
bool is_client_registered(int client_pid, int *client_pids, int num_clients) {
    for (int i = 0; i < num_clients; i++) {
        if (client_pids[i] == client_pid) {
            return true;
        }
    }
    return false;
}



const int SEND_MSG = 1;
const int RECEIVE_MSG = 2;
const int MAX_CLIENTS = 5;
int main() {


    const char* pipe_name = "server_pipe";
    mkfifo(pipe_name, 0666);
    int pipe_fd = open(pipe_name, O_RDWR);


    int client_pids[MAX_CLIENTS];
    int num_clients = 0;
    Queue* queue = create_queue();

    while (1) {
        char buffer[1024] = {0};
        read(pipe_fd, buffer, sizeof(buffer));

        int client_pid, syscall_num;
        sscanf(buffer, "%d %d", &client_pid, &syscall_num);

        if (!is_client_registered(client_pid, client_pids, num_clients)) {
        client_pids[num_clients++] = client_pid;
        printf("New client %d connected. Total clients: %d\n", client_pid, num_clients);
    }
        // Create unique pipe name for each client
        char client_pipe_name[256];
        snprintf(client_pipe_name, sizeof(client_pipe_name), "client_pipe_%d", client_pid);
        int client_pipe_fd = open(client_pipe_name, O_WRONLY);


        if (syscall_num == SEND_MSG) {
            Message msg;
            sscanf(buffer, "%*d %*d %d %d %[^\n]", &msg.type, &msg.length, msg.data);
            enqueue(queue, msg);
            printf("Client %d sent a message (type: %d, data: %s)\n", client_pid, msg.type, msg.data);
        } else if (syscall_num == RECEIVE_MSG) {
            int requested_type;
            sscanf(buffer, "%*d %*d %d", &requested_type);

            Message found_message = {-1, 0, ""};
            Queue* temp_queue = create_queue();

            while (!is_empty(queue)) {
                Message msg = dequeue(queue);
                if (msg.type == requested_type || (requested_type < 0 && msg.type <= -requested_type)) {
                    found_message = msg;
                    break;
                } else {
                    enqueue(temp_queue, msg);
                }
            }

            while (!is_empty(temp_queue)) {
                enqueue(queue, dequeue(temp_queue));
            }

            delete_queue(temp_queue);

            if (found_message.type != -1) {
                printf("Client %d received a message (type: %d, data: %s)\n", client_pid, found_message.type, found_message.data);
            } else {
                printf("Client %d requested type %d, but no message was available.\n", client_pid, requested_type);
            }

            char reply[1024] = {0};
            snprintf(reply, sizeof(reply), "%d %d %s", found_message.type, found_message.length, found_message.data);
            write(client_pipe_fd, reply, strlen(reply));
        close(client_pipe_fd);
        }
    }

    close(pipe_fd);
    delete_queue(queue);
    unlink(pipe_name);

    return 0;
}