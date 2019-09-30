#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include "linearSearchParallel.h"
#include "linearSearch.h"
#include "randomizeArray.h"

int main(){
	int i,*ptrA,n=10;
	double startTime, normalTime, parallelTime;
	FILE *fPtr;

	fPtr=fopen("statistics.txt","w");
		if(fPtr == NULL){
			printf("File cannot be created");
			exit(0);
		}
	while(n<=150050){
		printf("\nTamaño: %d\t",n);

		ptrA = (int*)calloc(n,sizeof(int));
		if (ptrA == NULL)
		{
			printf("Error 401. Memory not available");
			exit(0);
		}
		randomizeArray(ptrA,n);

		startTime=omp_get_wtime();
		linearSearchParallel(ptrA,n,-1);
		normalTime=omp_get_wtime()-startTime;
		printf("Parallel final Time: %f\t",normalTime);

		randomizeArray(ptrA,n);

		startTime=omp_get_wtime();
		linearSearch(ptrA,n,-1);
		parallelTime=omp_get_wtime()-startTime;
		printf("Normal final Time: %f",parallelTime);
		free(ptrA);

		fprintf(fPtr,"%d::%f::%f::\n",n,normalTime,parallelTime);

		n+=500;
	}
	fclose(fPtr);
	return 0;
}