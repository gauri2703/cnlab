#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORTNO 10201

int main(){
	int socket_id = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("127.0.1.1");
	serveraddress.sin_port = htons(PORTNO);
	
	bind(socket_id, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
	
	while(1){
		struct sockaddr_in clientaddress;
		socklen_t client = sizeof(clientaddress);
		int rows = 0;
		int columns = 0;
		
		recvfrom(socket_id, &rows, sizeof(rows), 0, (struct sockaddr*)&clientaddress, &client);
		recvfrom(socket_id, &columns, sizeof(columns), 0, (struct sockaddr*)&clientaddress, &client);
		
		int matrix[rows][columns];
		
		for(int i = 0; i < rows; i++){
			int matrix_row[columns];
			recvfrom(socket_id, matrix_row, sizeof(matrix_row), 0, (struct sockaddr*)&clientaddress, &client);
			for(int j = 0; j < columns; j++){
				matrix[i][j] = matrix_row[j];
			}
		}
		
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < columns; j++){
				printf("  %d", matrix[i][j]);
			}
			printf("\n");
		}
	}
	close(socket_id);
	return 0;
}