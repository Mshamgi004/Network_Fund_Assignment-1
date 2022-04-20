// Assignment - 1 //
// Network Fundamentals //
// Q.1 //
/*Write a udp client server program,client writing messages to server program and server
return back the same toggled msg to client. */
// MAHADEV G I //

//******** Server code *******//



#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 8000

int main()
{
	int sockfd, retval;                                              // initializing the sockfd, retvalues

	struct sockaddr_in servaddr;                                    

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);                         //sockfd function using the UDP
	if(sockfd < 0)
	{
		perror("socket: ");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);



	retval = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));             // returning value function to connect the server address
	if(retval < 0)
	{
		perror("connect: ");
		exit(2);
	}
	printf(".............Client connecting to server............\n");

	while(1)
	{
		char buff[100];
		int n;
		
		
		memset(buff, 0, sizeof(buff));                                      // memeset function to set the pointer to access the size of the buffer
		printf("\nEnter message to send to server: \n");
		gets(buff);

	
		send(sockfd, buff, strlen(buff), 0);                               // send the function to sockfd 

		n = recv(sockfd, buff, sizeof(buff), 0);                            // recieving the sockfd to establish the server client.
		if(n < 0)
		{
			perror("recv: ");
			exit(4);
		}
		printf("Recieved data from server : %s\n", buff);		
	}	

	close(sockfd);
	return 0;
}