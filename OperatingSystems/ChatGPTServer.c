#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "my_fifo"
#define BUF_SIZE 256

int main() {
    int fifo_fd;
    char buf[BUF_SIZE];

    // Create the FIFO
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for reading
    fifo_fd = open(FIFO_NAME, O_RDONLY);
    if (fifo_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read data from the FIFO
    while (read(fifo_fd, buf, BUF_SIZE) > 0) {
        printf("Received: %s\n", buf);
    }

    // Close the FIFO
    close(fifo_fd);

    // Remove the FIFO
    unlink(FIFO_NAME);

    return 0;
}
