#include<stdlib.h>
#include<stdio.h>
#include "mpi.h"


int main(int argc,char* argv[]){
	int procRank,procCount,error;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&procCount);

	error = MPI_Comm_rank(MPI_COMM_WORLD,&procRank);

	printf("Hello World from process %d / %d",procRank,procCount);
		
	MPI_Finalize();

	return 0;
}
