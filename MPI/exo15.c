#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc,char* argv[]){

	int procRank,procSize;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,procSize);
	MPI_Comm_rank(MPI_COMM_WORLD,procRank);

	if(0 == procRank){
		int message = 42;
		MPI_Request request*;
		MPI_Isend(&message,1,MPI_INT,1,1,MPI_COMM_WORLD,request);
	}else{
		int message;
		MPI_Request request*;
		MPI_Status status*;
		MPI_Irecv(&message,1,MPI_INT,0,1,MPI_COMM_WORLD,request);


		int flag = 0;
		int counter = 0;

		while(1){
			counter++;
			MPI_Test(request,&flag,MPI_STATUS_IGNORE);
		}

		printf("I waited for %d for the message and his value is %d",counter,message);
	}

	MPI_Finalize();

	return 0;
}