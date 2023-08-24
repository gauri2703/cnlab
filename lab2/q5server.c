#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#define PORTNO 10201

int isDuplicate(char ch, char unique[], int ind){
	for(int i = 0; i < ind; i++){
		if(unique[i] == ch)
			return 1;
	}
	return 0;
}

int main(){
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("127.0.1.1");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(socket_id, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	listen(socket_id, 5);
	
	while(1){
		int pid = fork();
		
		if(pid == 0){
			char string[256];
			char unique[256];
			int ind = 0;
			struct sockaddr_in clientaddress;
			int client = sizeof(clientaddress);
			int new_socket_id = accept(socket_id, (struct sockaddr*)&clientaddress, &client);
			
			recv(new_socket_id, string, sizeof(string), 0);
			if(strcmp(string, "Stop") == 0){
				exit(0);
			}
			for(int i = 0; i < strlen(string); i++){
				if(string[i] == ' ')
					unique[ind++] = ' ';
				else if(!isDuplicate(string[i], unique, ind))
					unique[ind++] = string[i];
			}
			unique[ind] = '\0';
			send(new_socket_id, unique, strlen(unique) * sizeof('c'), 0);
			exit(0);
		}
		
		else{
			wait(NULL);
		}
	}
}