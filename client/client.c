#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MESSAGE_SIZE 256

int main(int argc, char** argv)
{
	int sock_fd;
	struct sockaddr_in sock_server_addr;
	char* client_message = (char*)malloc(sizeof(char)*MESSAGE_SIZE);
	char* server_reply = (char*)malloc(sizeof(char)*MESSAGE_SIZE);

	sock_server_addr.sin_family = AF_INET;
	sock_server_addr.sin_addr.s_addr = inet_addr("62.109.13.188");
	sock_server_addr.sin_port = htons(8888);	

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(sock_fd < 0)
	{
		printf("socket error!\n");
		return -1;
	}	

	if(connect(sock_fd,(struct sockaddr*)&sock_server_addr, sizeof(sock_server_addr)) < 0)
	{
		printf("Error connect!\n");
		return -1;
	} 	
	
	while(1)
	{
		scanf("%s", client_message);
		printf("send: %s\n", client_message);
		if(send(sock_fd, client_message, strlen(client_message), 0) < 0)
		{
			printf("error sending message: %s\n", client_message);
			close(sock_fd);
			return -1;
		}	
		
		bzero(server_reply, MESSAGE_SIZE);
		if( recv(sock_fd, server_reply, MESSAGE_SIZE, 0) < 0)
		{
			printf("error recv message");
                        close(sock_fd);
                        return -1;
		}
		printf("recv: %s\n", server_reply);
	}
	close(sock_fd);
        return 0;
}
