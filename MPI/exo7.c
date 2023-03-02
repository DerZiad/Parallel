#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

void printTable(int* table,int n){
	for(int i =0;i<n;i++){
		printf("%d",table[i]);
	}
}

void fill(int *table,int length){
	for(int i =0 ;i<length;i++){
		table[i] = i + 1;
	}
}

int main(int argc,char* argv[]){
	int procCount,procRank,length=9;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&procCount);
	MPI_Comm_rank(MPI_COMM_WORLD,&procRank);
	
	int buf[length];

	if(procRank == 0){
		fill(buf,length);
		MPI_Bcast(buf,length,MPI_INT,0,MPI_COMM_WORLD);
	}else{
		printf("Process %d : ",procRank);
		printTable(buf,length);
		printf("\n");
	}

	


	MPI_Finalize();
	return 0;
}
