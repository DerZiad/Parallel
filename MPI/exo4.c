#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc,char* argv[]){
	
	int procCount,procRank;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&procCount);
	MPI_Comm_rank(MPI_COMM_WORLD,&procRank);

	int length = 5;

	for(int i = 0;i<6;i++){

		if( 0 == procRank){
			char message[] = "Ping";
			MPI_Send(&message,length,MPI_CHAR,1,1,MPI_COMM_WORLD);
			
			MPI_Status status;
			MPI_Probe(1,1,MPI_COMM_WORLD,&status);

			int k;

			MPI_Get_count(&status,MPI_CHAR,&k);

			char* message2 = (char*)malloc(k * sizeof(char));
			MPI_Recv(message2,k,MPI_CHAR,1,1,MPI_COMM_WORLD,&status);
			printf("%s frm thread %d\n",message2,1);
		}
		else{
			MPI_Status status;
			MPI_Probe(0,1,MPI_COMM_WORLD,&status);

			int k;
			MPI_Get_count(&status,MPI_CHAR,&k);

			char* message = (char*)malloc(k * sizeof(char));

			MPI_Recv(message,k,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
			printf("%s frm thread %d\n",message,0);

			char message1[] = "Pong";
			
			MPI_Send(&message1,length,MPI_CHAR,0,1,MPI_COMM_WORLD);
		}
	}
	
	return 0;
}
