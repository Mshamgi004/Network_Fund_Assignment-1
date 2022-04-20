// Assignment - 1 //
// Network Fundamentals //
// Q.1 //
/*Write a udp client server program,client writing messages to server program and server
return back the same toggled msg to client.*/
// MAHADEV G I //
//********Client code********//





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
	int sockfd, retval;                                            //  initializing the variables

	struct sockaddr_in servaddr, clientaddr;                              //  creating address for the socket address for the client and server
	socklen_t clilen;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);                             // sockfd function using UDP.....
	if(sockfd < 0)
	{
		perror("socket: ");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	retval = bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));             // retval function for binding the server
	if(retval < 0)
	{
		perror("bind: ");
		exit(2);
	}

	listen(sockfd, 5);

	while(1)
	{

	printf("Server Waiting for client connection\n");
	clilen = sizeof(clientaddr);
	accfd = accept(sockfd, (struct sockaddr *) &clientaddr, &clilen);                     // accfd function for accepting the client request
	printf("Client connected\n");

		while(1)
		{
			char buff[100];
			int n;	
			
			printf("........Server before receiving.....\n");
			memset(buff, 0, sizeof(buff));

			n = recv(sockfd, buff, sizeof(buff), 0);
		
			if(n == 0)
			{
				perror("recv: ");
				close(sockfd);
				exit(0);
			}
			printf("Recieved data from client : %s\n", buff);

			for(int i=0; i<=5 ; i++)                                        
			{
			     int i=0;
				if(buff[i] >= 'a' && buff[i] <= 'z')
					buff[i] -= 32;
				else 
					buff[i] += 32;
			}



			send(sockfd, buff, strlen(buff), 0);                                 // send the data to client using send function
			printf("***********Data sended to client************\n\n");
		}	
	
	close(sockfd);                                                    
	return 0;
}