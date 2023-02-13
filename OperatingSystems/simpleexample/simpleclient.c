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
  
  printf("Enter a number between 0 and 9: ");
  scanf("%d", &num);
  sprintf(buf, "%d", num);
  fd = open(FIFO_NAME, O_WRONLY);
  write(fd, buf, strlen(buf) + 1);
  read(fd, buf, 100);
  printf("Server responce %s\n", buf);

  printf("Enter a number in text form (zero, one, two, etc): ");
  scanf("%s", buf);
  fd = open(FIFO_NAME, O_WRONLY);
  write(fd, buf, strlen(buf) + 1);
  read(fd, buf, 100);
  sscanf(buf, "%d", &num);
  close(fd);
  return 0;
}



// basic test for Client, Shows its running with a endless loop

   // char arr1[80], arr2[80]; 
    // while (1) 
    // { 
    //     fd = open(myfifo, O_WRONLY); 
    //     fgets(arr2, 80, stdin); 
    //     write(fd, arr2, strlen(arr2)+1); 
    //     close(fd); 
    //     fd = open(myfifo, O_RDONLY); 
    //     read(fd, arr1, sizeof(arr1)); 
    //     printf("User2: %s\n", arr1); 
    //     close(fd); 
    // } 