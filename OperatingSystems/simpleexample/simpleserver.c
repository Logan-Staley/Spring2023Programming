#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO_NAME "myfifo"

// global variables 
int number_to_num(char *number) {
  if (strcmp(number, "zero") == 0) return 0;
  if (strcmp(number, "one") == 0) return 1;
  if (strcmp(number, "two") == 0) return 2;
  if (strcmp(number, "three") == 0) return 3;
  if (strcmp(number, "four") == 0) return 4;
  if (strcmp(number, "five") == 0) return 5;
  if (strcmp(number, "six") == 0) return 6;
  if (strcmp(number, "seven") == 0) return 7;
  if (strcmp(number, "eight") == 0) return 8;
  if (strcmp(number, "nine") == 0) return 9;
  return -1;
}

char *num_to_number(int num) {
  switch (num) {
    case 0: return "zero";
    case 1: return "one";
    case 2: return "two";
    case 3: return "three";
    case 4: return "four";
    case 5: return "five";
    case 6: return "six";
    case 7: return "seven";
    case 8: return "eight";
    case 9: return "nine";
    default: return "";
  }
}
// global variables 
int stored_numbers[10];
char * stored_numberstring[10];
int num_count = 0;

void store_number(int num) {
  stored_numbers[num_count++] = num;
}

char * get_stored_numbers() {
  int i;
  char *result = (char *)malloc(100);
  result[0] = '\0';
  for (i = 0; i < num_count; i++) {
    char buf[100];
    sprintf(buf, "%s\n ", num_to_number(stored_numbers[i]));
    strcat(result, buf);
  }
  return result;
}

int stored_value_int;

void store_value_int(int value_int) {
  stored_value_int = value_int;
}

int recall_value_int() {
  return stored_value_int;
}

char  stored_value_char;

void store_value_char(char value_char) {
  stored_value_char = value_char;
}

char recall_value_char() {
  return stored_value_char;
}


int main() 
{
  char buf[100];
  int fd;
  int num;
  int num1;
  char *numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};


// this function call converts a int number in toa string number.
  mkfifo(FIFO_NAME, 0666);
  printf("Waiting for a client...\n");
  fd = open(FIFO_NAME, O_RDONLY);

// while (1) {
//     read(fd, buf, 100);
//     if (strcmp(buf, "get") == 0) {
//       char *result = get_stored_numbers();
//       write(fd, result, strlen(result) + 1);
//       free(result);
//     } else {

  read(fd, buf, 100);
  num = number_to_num(buf);
  printf("User1: %d\n", num);
  sprintf(buf, "%d", num);
  write(fd, buf, strlen(buf) + 1);
// this function call converts a String number in to a int number
  fd = open(FIFO_NAME, O_RDONLY);
  read(fd,buf,100);
  num = number_to_num(buf);
  printf("User1: %d\n", num);
  store_value_int(num);
  store_number(num);
  sprintf(buf, "%d", num);
  write(fd, buf, strlen(buf) + 1);
    
    printf("First conversion recall: %d\n", recall_value_char());
    
    printf("second conversion recall: %d\n", recall_value_int());



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