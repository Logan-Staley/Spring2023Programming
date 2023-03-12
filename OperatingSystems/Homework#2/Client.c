#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO_NAME_1 "server_to_client_fifo"
#define FIFO_NAME_2 "client_to_server_fifo"

int main()
{
    int server_to_client_fifo, client_to_server_fifo;
    char buffer[1000];
    int number;
    char * serverinput[1000];
    int counter = 0;
    char inputstring[1000];
    int inputint;
//-----------------------------------------------------------------
    /* Create the FIFO file if it does not exist */
    mkfifo(FIFO_NAME_1, 0666);
    mkfifo(FIFO_NAME_2, 0666);

//while(counter != 5){
//-------------------------------------------------------
/* Open the FIFO files */

while(counter == 0){

    server_to_client_fifo = open(FIFO_NAME_1, O_RDONLY);
    client_to_server_fifo = open(FIFO_NAME_2, O_WRONLY);


//-------------------------------------------
//get the PID of the client and send it to the server

char pid_str[16];
pid_t pid = getpid();
sprintf(pid_str, "%d",pid);
printf("client PID is %d\n",pid);
write(client_to_server_fifo, pid_str,sizeof(pid_str));


char pid_str_server[16];
read(server_to_client_fifo,pid_str_server,sizeof(pid_str_server));
pid_t server_pid = atoi(pid_str_server);
printf("Server Pid is %d\n",server_pid);
//-----------------------

int choice;
        printf("Choose a method to use:\n");
        printf("1. Convert integer to string\n");
        printf("2. Convert string to integer\n");
        printf("3. Store integer in server and recall it\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    write(client_to_server_fifo,&choice,sizeof(choice));
switch(choice){

//-------------------------------------------------------------
// sending an integer to the server to be converted to a string
    case 1:
        printf("Enter a number to be converted to a string: ");
        scanf("%d", &number);
        sprintf(buffer, "%d", number);
        write(client_to_server_fifo,&number,sizeof(number));
//---------------------------------------------------------------------
/* Read from the server FIFO */
 // read the string sent from the server and prints that string**
        read(server_to_client_fifo, buffer, sizeof(buffer));
        printf("Received from server: '%s'\n", buffer);
        break;
 //***------------------------------------------------------
// we will send the client a string representing a number between 1-9 
//then recieve a integer in return
// sending an integer to the server to be converted to a interger
    case 2:
        printf("Enter a number to be converted to a integer: ");
        scanf("%s", inputstring);
        write(client_to_server_fifo,inputstring,strlen(inputstring));
//---------------------------------------------------------------------
/* Read from the server FIFO */
 // read the string sent from the server and prints that string**
        read(server_to_client_fifo, &number, sizeof(number));
        printf("Received from server: '%d'\n", number);
        break;
 //***------------------------------------------------------
    case 3:
//----------------------------Send an integer to be stored in a variable in the server program---------------------------------//
        printf("Input an integer you wanna store in the server: ");
        scanf("%d",&inputint);
        write(client_to_server_fifo, &inputint,sizeof(inputint));
//------------------------------------------------------------//
        printf("do you want that value back?(1(yes) or 0(no)): ");
        int recall;
        scanf("%d",&recall);
        write(client_to_server_fifo,&recall,sizeof(recall));
        if(recall == 1){
            read(server_to_client_fifo,&number,sizeof(number));
            printf("your store value was returned: '%d'\n",number);
        }else if(recall == 0){
            printf("The value was not recalled\n");
        }
        break;
    case 4:
        counter++;
        break;
}
}
    close(server_to_client_fifo);
    close(client_to_server_fifo);
//------------------------------------------------
/* Remove the FIFO files */
    unlink(FIFO_NAME_1);
    unlink(FIFO_NAME_2);

    return 0;}

    /* Write to the client FIFO */
    // strcpy(buffer, "Hello from the client!");
    // write(client_to_server_fifo, buffer, strlen(buffer) + 1);