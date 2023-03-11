#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
    char pid[10];
    int pid_int;
    int i = 0;
//-----------------------------------------------------------------
    /* Create the FIFO file if it does not exist */
    mkfifo(FIFO_NAME_1, 0666);
    mkfifo(FIFO_NAME_2, 0666);

//while(counter != 5){
//-------------------------------------------------------
/* Open the FIFO files */

    server_to_client_fifo = open(FIFO_NAME_1, O_RDONLY);
    client_to_server_fifo = open(FIFO_NAME_2, O_WRONLY);


while(counter == 0){

    //Request a simulated process ID from the server
    write(client_to_server_fifo, "PID_REQUEST", 11);
    read(server_to_client_fifo, pid, 10);
    pid[10] = '\0';
    pid_int = atoi(pid);

    printf("Client PID: %d\n", pid_int);


     // Send an integer to the server
    number = 42;
    write(client_to_server_fifo, &number, sizeof(number));
    read(server_to_client_fifo, buffer, sizeof(buffer));
    printf("Server sent back: %s\n", buffer);

    // Send a string to the server
    strcpy(buffer, "Hello, server!");
    write(client_to_server_fifo, buffer, sizeof(buffer));
    read(server_to_client_fifo, &number, sizeof(number));
    printf("Server sent back: %d\n", number);

    // Send an integer to the server to be stored as a variable
    number = 123;
    write(client_to_server_fifo, &number, sizeof(number));
    printf("Sent %d to be stored on the server\n", number);





//-------------------------------------------------------------
// sending an integer to the server to be converted to a string
    printf("Enter a number to be converted to a string: ");
    scanf("%d", &number);
    sprintf(buffer, "%d", number);
    write(client_to_server_fifo,&number,sizeof(number));
//---------------------------------------------------------------------
/* Read from the server FIFO */
 // read the string sent from the server and prints that string**
    read(server_to_client_fifo, buffer, sizeof(buffer));
    printf("Received from server: '%s'\n", buffer);
 //***------------------------------------------------------


// we will send the client a string representing a number between 1-9 
//then recieve a integer in return

// sending an integer to the server to be converted to a interger
    printf("Enter a number to be converted to a integer: ");
    scanf("%s", inputstring);
    write(client_to_server_fifo,inputstring,strlen(inputstring));
//---------------------------------------------------------------------
/* Read from the server FIFO */
 // read the string sent from the server and prints that string**
    read(server_to_client_fifo, &number, sizeof(number));
    printf("Received from server: '%d'\n", number);
 //***------------------------------------------------------

//----------------------------Send an integer to be stored in a variable in the server program---------------------------------//
    printf("Input an integer you wanna store in the server: ");
    scanf("%d",&inputint);
    write(client_to_server_fifo, &inputint,sizeof(inputint));
//------------------------------------------------------------//

    printf("do you want that value back?(1(yes) or 0(no)) or 2(exit)/null: ");
    int recall;
    scanf("%d",&recall);
    write(client_to_server_fifo,&recall,sizeof(recall));
    if(recall == 1){
        read(server_to_client_fifo,&number,sizeof(number));
        printf("your store value was returned: '%d'\n",number);
    }else if(recall == 0){
        printf("The value was not recalled\n");
    }else if (recall == 2){
        counter++;
    }else{counter = 0;}
}
    close(server_to_client_fifo);
    close(client_to_server_fifo);
//------------------------------------------------
/* Remove the FIFO files */
    unlink(FIFO_NAME_1);
    unlink(FIFO_NAME_2);

    return 0;}
