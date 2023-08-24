#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>8
#define PORTNO 10201

int main(){
	int socket_id = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.1.1");
	address.sin_port = htons(PORTNO);
	
	socklen_t server = sizeof(address);
	
	int rows = 0;
	int columns = 0;
	
	printf(" \nEnter number of rows: ");
	scanf("%d", &rows);
	printf(" \nEnter number of elements in one row: ");
	scanf("%d", &columns);
	
	sendto(socket_id, &rows, sizeof(rows), 0, (struct sockaddr*)&address, server);
	sendto(socket_id, &columns, sizeof(columns), 0, (struct sockaddr*)&address, server);
	
	for(int i = 0; i < rows; i++){
		int row[columns];
		printf("\nEnter row number %d:\n", i + 1);
		for(int j = 0; j < columns; j++){
			scanf("%d", &row[j]);
		}
		sendto(socket_id, row, sizeof(row), 0, (struct sockaddr*)&address, server);
	}
	close(socket_id);
	return 0;
}