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

    // Open the FIFO for writing
    fifo_fd = open(FIFO_NAME, O_WRONLY);
    if (fifo_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write data to the FIFO
    while (fgets(buf, BUF_SIZE, stdin)) {
        write(fifo_fd, buf, strlen(buf));
    }

    // Close the FIFO
    close(fifo_fd);

    return 0;
}
