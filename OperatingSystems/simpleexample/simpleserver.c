#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO_NAME "myfifo"

int main() 
{
  char buf[100];
  int fd;
  int num;
  char *numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  
  mkfifo(FIFO_NAME, 0666);
  printf("Waiting for a client...\n");
  fd = open(FIFO_NAME, O_RDONLY);
  read(fd, buf, 100);
  sscanf(buf, "%d", &num);
  printf("User1: %s\n", numbers[num]);
  strcpy(buf, numbers[num]);
  write(fd, buf, strlen(buf) + 1);
  close(fd);
  unlink(FIFO_NAME);
  return 0;
}







//a test to verify fifo working
    // char arr1[80], arr2[80]; 
    // while (1) 
    // { 
    //     fd = open(myfifo, O_RDONLY); 
    //     read(fd, arr1, sizeof(arr1)); 
    //     printf("User1: %s\n", arr1); 
    //     close(fd); 
    //     fd = open(myfifo, O_WRONLY); 
    //     fgets(arr2, 80, stdin); 
    //     write(fd, arr2, strlen(arr2)+1); 
    //     close(fd); 
    // } 