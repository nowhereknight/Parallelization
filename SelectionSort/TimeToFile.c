#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include "selectionSort.h"
#include "randomizeArray.h"
#define N 10

int main(){
	int i,*ptrA,n=10;
	double startTime, normalTime, parallelTime;
	FILE *fPtr;

	fPtr=fopen("statistics.txt","w");
		if(fPtr == NULL){
			printf("File cannot be created");
			exit(0);
		}
	while(n<=10010){
		printf("Tamaño: %d\t",n-1);

		ptrA = (int*)calloc(n,sizeof(int));
		if (ptrA == NULL)
		{
			printf("Error 401. Memory not available");
			exit(0);
		}


		randomizeArray(ptrA,n);

		startTime=omp_get_wtime();
		selectionSort(ptrA,n);
		normalTime=omp_get_wtime()-startTime;
		printf("Normal final Time: %f\t",normalTime);

		startTime=omp_get_wtime();
		selectionSortParallel(ptrA,n);
		parallelTime=omp_get_wtime()-startTime;
		printf("Parallel final Time: %f\n",parallelTime);

		randomizeArray(ptrA,n);

		
		free(ptrA);

		fprintf(fPtr,"%d::%f::%f::\n",n,normalTime,parallelTime);

		n+=100;
	}
	fclose(fPtr);
	return 0;
}