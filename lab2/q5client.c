#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#define PORTNO 10201

int main(){	
	while(1){
		int socket_id = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr("127.0.1.1");
		address.sin_port = htons(PORTNO);
		int res = connect(socket_id, (struct sockaddr*)&address, sizeof(address));
	
		if(res == -1){
			perror("\nClient Error");
			exit(-1);
		}
		char string[256];
		char result[256];
		
		printf("\nEnter String: ");
		scanf("%[^\n]%*c", string);
		
		if(strcmp(string, "Stop") == 0)
			exit(0);
		
		send(socket_id, string, sizeof(string), 0);
		recv(socket_id, result, sizeof(result), 0);
		
		printf("%s", result);
		close(socket_id);				
	}
}