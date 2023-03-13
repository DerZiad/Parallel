#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc,char* argv[]){
	
	int procRank,procSize;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&procSize);
	MPI_Comm_rank(MPI_COMM_WORLD,&procRank);
	
	if(0==procRank){
		printf("Put array :");
		int length=6;
		int buf[length];
		for(int i = 0;i<length;i++){
			scanf("%d",&buf[i]);
		}
	
		MPI_Send(&buf,length, MPI_INT, 1, 1,MPI_COMM_WORLD);
	}else{
		MPI_Status status;

		MPI_Probe(0,1,MPI_COMM_WORLD,&status);
		int count;


		MPI_Get_count(&status,MPI_INT,&count);

		MPI_Status status1;
		int buf[count];
		MPI_Recv(&buf,count,MPI_INT,0,1,MPI_COMM_WORLD,&status1);

		int countZeros = 0;

		for(int i=0;i<count;i++){
			if(buf[i] == 0)
				countZeros++;
		}

		printf("Count is %d",countZeros);

	}

	MPI_Finalize();

	return 0;
}

