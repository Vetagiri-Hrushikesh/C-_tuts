// Client side C/C++ program to demonstrate Socket

// programming

#include <arpa/inet.h>

#include <stdio.h>

#include <string.h>

#include <sys/socket.h>

#include <unistd.h>

#define PORT 9999



int main(int argc, char const* argv[])

{



char buf[100];

int sock = 0, valread;

	struct sockaddr_in serv_addr;

	char* hello = "1234";

	char buffer[1024] = { 0 };

	

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {

		printf("\n Socket creation error \n");

		return -1;

	}



	serv_addr.sin_family = AF_INET;

	serv_addr.sin_port = htons(PORT);



	// Convert IPv4 and IPv6 addresses from text to binary

	// form

	if (inet_pton(AF_INET, "192.168.56.1", &serv_addr.sin_addr)

		<= 0) {

		printf(

			"\nInvalid address/ Address not supported \n");

		return -1;

	}



	if (connect(sock, (struct sockaddr*)&serv_addr,

				sizeof(serv_addr))

		< 0) {

		printf("\nConnection Failed \n");

		return -1;

	}

	

	valread = read(sock, buffer, 1024);

	printf("%s\n", buffer);

    FILE *file = fopen("info.txt", "r");

    // Checks if the file was opened successfully

    if (file == NULL)

    {

        fputs("Failed to open the file\n", stderr);

        return -1;

    }

    

    // fgets here reads an entire line or 99 characters (+1 for \0) at a time, whichever comes first

    while (fgets(buf, sizeof(buf), file) != NULL)

    {

        //printf("Line read = %s\n", buf);

        send(sock, buf, 100, 0);

    }



    fclose(file);

	return 0;

}

