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
    char buffer[100];
    int temp;
    int number;
    int counter = 0;
    char *numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    /* Create the FIFO file if it does not exist */
    mkfifo(FIFO_NAME_1, 0666);
    mkfifo(FIFO_NAME_2, 0666);

    int simulated_pid_counter = 1;
    int client_return_fifo[10]; // array to store return FIFO file descriptors, assuming max 10 clients

    server_to_client_fifo = open(FIFO_NAME_1, O_WRONLY);
    client_to_server_fifo = open(FIFO_NAME_2, O_RDONLY);

    while (counter == 0)
    {
        /* ---------------------------Open the FIFO files ------------------------------*/

        // Wait for client connection request
        int new_client_fd = accept(server_fd, NULL, NULL);

        // Increment simulated process ID counter
        int pid = simulated_pid_counter++;

        // Save return FIFO file descriptor for this client
        client_return_fifo[pid-1] = open(client_fifo_name, O_WRONLY);

        // Send simulated process ID back to client
        write(client_return_fifo[pid-1], &pid, sizeof(pid));
        // ...
        /* ----------------------Read from the client FIFO----------------------------- */
        // this is the clents input(int) ------------------------

        read(client_to_server_fifo, &number, sizeof(number));
        printf("Received from client: %d\n", number);

        //---------------------------------------------------
        // convert the given number to a string and sends it to the client(string)
        char *ConvertNum = num_to_word(number);
        printf("%s\n", ConvertNum);
        write(server_to_client_fifo, ConvertNum, sizeof(ConvertNum));

        //---------------------------------------------

        // We will convert the string sent from the client to an integer
        // and send the converted integer in return
        /* ----------------------Read from the client FIFO----------------------------- */
        // this is the clents input(int) ------------------------
        read(client_to_server_fifo, buffer, sizeof(buffer));
        printf("Received from client: %s\n", buffer);

        //---------------------------------------------------
        // convert the given number to a string and sends it to the client(string)
        int Convertstring = string_to_num(buffer);
        printf("%d\n", Convertstring);
        write(server_to_client_fifo, &Convertstring, sizeof(Convertstring));
        //---------------------------------------------

        //------------------collects an integer from the client to be stored as a variable in the server program.---------------------------//
        read(client_to_server_fifo, &number, sizeof(number));
        printf("The Client sent: %d to be stored\n", number);
        store_value(number);
        printf("%d has been stored in a variable\n", number);
        //--------------------------------------------------//
        int answer = read(client_to_server_fifo, &answer, sizeof(answer));
        ;

        if (answer == 1)
        {
            write(server_to_client_fifo, &stored_value, sizeof(stored_value));
            printf("The client requested the stored value back.");
        }
        else if (answer == 0)
        {
            printf("The client declined the recall question.");
        }
        else if (answer == 2)
        {
            counter++;
        }
        else
        {
            counter = 0;
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
