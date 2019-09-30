#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include "mergeSortParallel.h"
#include "mergeSort.h"
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
	while(n<=150001){
		printf("\nTamaño: %d\t",n-1);

		ptrA = (int*)calloc(n,sizeof(int));
		if (ptrA == NULL)
		{
			printf("Error 401. Memory not available");
			exit(0);
		}


		randomizeArray(ptrA,n);

		startTime=omp_get_wtime();
		mergeSort(ptrA,n);
		normalTime=omp_get_wtime()-startTime;
		printf("Normal final Time: %f\t",normalTime);

		randomizeArray(ptrA,n);
		startTime=omp_get_wtime();
		#pragma omp parallel num_threads(2)
		{
			#pragma omp single
			{
			mergeSortParallel(ptrA,n);		
			}
		}
		parallelTime=omp_get_wtime()-startTime;
		printf("Parallel final Time: %f\n",parallelTime);

		
		
		free(ptrA);

		fprintf(fPtr,"%d::%f::%f::\n",n,parallelTime,normalTime);

		n+=500;
	}
	fclose(fPtr);
	return 0;
}