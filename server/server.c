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
	int sock_fd, sock_client_fd, c, read_size;
	struct sockaddr_in sock_addr;
	struct sockaddr_in sock_client_addr;
	char* client_message = (char*)malloc(sizeof(char)*MESSAGE_SIZE); 	

	sock_addr.sin_family = AF_INET;
    	sock_addr.sin_addr.s_addr = htons(INADDR_ANY);
   	sock_addr.sin_port = htons(8888);

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (sock_fd < 0)
		printf("socket error!\n");

	if(bind(sock_fd,(struct sockaddr*)&sock_addr, sizeof(sock_addr) < 0))
	{
		printf("Error bind\n");
		return -1;
	}
	
	printf("binded\n");
	listen(sock_fd, 3);
		printf("listened\n");
	c = sizeof(struct sockaddr_in);

   
   	sock_client_fd = accept(sock_fd, (struct sockaddr *)&sock_client_addr, (socklen_t*)&c);
   	if (sock_client_fd < 0)
   	{
       		printf("accept failed");
       		return -1;
   	}
	
	while( (read_size = recv(sock_client_fd , client_message , MESSAGE_SIZE , 0)) > 0 )
   	{
		printf("%s", client_message);
		write(sock_client_fd , client_message , strlen(client_message));
	}

	if(read_size == 0)
	{
		printf("Finish");
	}	

	return 0;
}
