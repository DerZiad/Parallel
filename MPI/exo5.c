#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc,char* argv[]){
	
	int procCount,procRank;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&procCount);
	MPI_Comm_rank(MPI_COMM_WORLD,&procRank);

	int length = 0,receiveId,sendId,tagMessage = 1;
	int message = procRank + 60;

	for(int i = 0;i<procCount;i++){

		if( i == procRank){
			sendId = i == (procCount - 1)?0:i+1;

			MPI_Send(&message,length,MPI_INT,sendId,tagMessage,MPI_COMM_WORLD);
		
			int receiveId = i == 0? (procCount - 1) : i-1;
			MPI_Status status;
			int* message2 = (int*)malloc(sizeof(int));
			MPI_Recv(message2,k,MPI_INT,receiveId,tagMessage,MPI_COMM_WORLD,&status);
			printf("[ + ] - Message with value %d received from %d",*message,receiveId);
			break;
		}
	}
	
	return 0;
}
