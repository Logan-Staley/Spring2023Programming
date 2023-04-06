#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO_NAME_1 "server_to_client_fifo"
#define FIFO_NAME_2 "client_to_server_fifo"

void int_to_string(int num, char *str)
{
    sprintf(str, "%d", num);
}

char *num_to_word(int num)
{
    switch (num)
    {
    case 0:
        return "zero";
    case 1:
        return "one";
    case 2:
        return "two";
    case 3:
        return "three";
    case 4:
        return "four";
    case 5:
        return "five";
    case 6:
        return "six";
    case 7:
        return "seven";
    case 8:
        return "eight";
    case 9:
        return "nine";
    default:
        return "";
    }
}

#include <string.h>
int stored_value;
int string_to_num(const char *str)
{
    if (strcmp(str, "one") == 0)
        return 1;
    else if (strcmp(str, "two") == 0)
        return 2;
    else if (strcmp(str, "three") == 0)
        return 3;
    else if (strcmp(str, "four") == 0)
        return 4;
    else if (strcmp(str, "five") == 0)
        return 5;
    else if (strcmp(str, "six") == 0)
        return 6;
    else if (strcmp(str, "seven") == 0)
        return 7;
    else if (strcmp(str, "eight") == 0)
        return 8;
    else if (strcmp(str, "nine") == 0)
        return 9;
    else
    {
        return -1;
    }
}

void store_value(int value)
{
    stored_value = value;
}

int processID_counter = 0;

int main()
{
    int server_to_client_fifo, client_to_server_fifo;
    char buffer[100];
    int temp;
    int number;
    int counter = 0;
    int choice = 0;

// introducing the ProcessID and Pid to the server program
    int server_fifo_fd, client_fifo_fd;
    char server_fifo[] = "server_fifo";
    char client_fifo[64];
    int processID;
    int processID_counter = 0;
    int client_info[2];


    int isQueueCreated = 0;
    char *numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    /* Create the FIFO file if it does not exist */
    mkfifo(FIFO_NAME_1, 0666);
    mkfifo(FIFO_NAME_2, 0666);
    server_to_client_fifo = open(FIFO_NAME_1, O_WRONLY);
    client_to_server_fifo = open(FIFO_NAME_2, O_RDONLY);

    pid_t pid = getpid();
        char pid_str[16];
        sprintf(pid_str, "%d", pid);
        printf("Server PID is %d\n", pid);
        write(server_to_client_fifo, pid_str, sizeof(pid_str));

        char pid_str_client[16];
        read(client_to_server_fifo, pid_str_client, sizeof(pid_str_client));
        pid_t client_pid = atoi(pid_str_client);
        printf("Client Pid is %d\n", client_pid);

        
        client_info[0] = client_pid;
        client_info[1] = client_fifo_fd;

        close(server_to_client_fifo);
        close(client_to_server_fifo);
    while (counter == 0)
    {

        // /* ---------------------------Open the FIFO files ------------------------------*/
         server_to_client_fifo = open(FIFO_NAME_1, O_WRONLY);
         client_to_server_fifo = open(FIFO_NAME_2, O_RDONLY);

        //------------
        processID = processID_counter;
    //    processID_counter++;
        printf("Process id Counter is  %d\n", processID_counter);
        
        // get the pid of the server and send it to the client
        read(client_to_server_fifo,&choice,sizeof(choice));
        switch (choice)
        {

        /* ----------------------Read from the client FIFO----------------------------- */
        // this is the clents input(int) ------------------------
    case 1:
    {
        
        read(client_to_server_fifo, &number, sizeof(number));
        printf("Received from client: %d\n", number);

        //---------------------------------------------------
        // convert the given number to a string and sends it to the client(string)
        char *ConvertNum = num_to_word(number);
        printf("The Integer Converted to a string is: %s\n", ConvertNum);
        write(server_to_client_fifo, ConvertNum, sizeof(ConvertNum));
        processID_counter++;
        break;
    }
        //---------------------------------------------

        // We will convert the string sent from the client to an integer
        // and send the converted integer in return
        /* ----------------------Read from the client FIFO----------------------------- */
        // this is the clents input(int) ------------------------
    case 2:
    {
        read(client_to_server_fifo, buffer, sizeof(buffer));
        printf("Received from client: %s\n", buffer);

        //---------------------------------------------------
        // convert the given number to a string and sends it to the client(string)
        int Convertstring = string_to_num(buffer);
        printf("the string converted to a number is: %d\n", Convertstring);
        write(server_to_client_fifo, &Convertstring, sizeof(Convertstring));
        processID_counter++;
        break;
    }
        //---------------------------------------------

        //------------------collects an integer from the client to be stored as a variable in the server program.---------------------------//

    case 3:
    {
        read(client_to_server_fifo, &number, sizeof(number));
        printf("The Client sent: %d to be stored\n", number);
        store_value(number);
        printf("%d has been stored in a variable\n", number);
        //--------------------------------------------------//
        int answer;
        read(client_to_server_fifo, &answer, sizeof(answer));
        if (answer == 1)
        {
            write(server_to_client_fifo, &stored_value, sizeof(stored_value));
            printf("The client requested the stored value back.");
        }
        else if (answer == 0)
        {
            printf("The client declined the recall question.");
        }
        processID_counter++;
        break;
    }
    case 4:
    {
        processID_counter++;
        choice++;
        counter++;
        break;
    }
        }
    }

    //------------------------------------------------
    /* Remove the FIFO files */
    close(server_to_client_fifo);
    close(client_to_server_fifo);
    unlink(FIFO_NAME_1);
    unlink(FIFO_NAME_2);

    return 0;
}