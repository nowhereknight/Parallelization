#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "selectionSort.h"
#include "randomizeArray.h"

#define n 10

int main(){
	int *a=(int*) malloc(n*sizeof(int));
	int *b=(int*) malloc(n*sizeof(int));
	randomizeArray(a,n);
	randomizeArray(b,n);
	double startTime, totalTime;
	for(int i=0;i<n;i++)
		printf(" %d ",a[i]);
	
	startTime=omp_get_wtime();
	selectionSort(b,n);
	totalTime=omp_get_wtime()-startTime;

	printf("\nLista Ordenada\n");
	for(int i=0;i<n;i++)
		printf(" %d ",b[i]);

	printf("\nNormal final Time: %f\n",totalTime);

	startTime=omp_get_wtime();
	selectionSortParallel(a,n);
	totalTime=omp_get_wtime()-startTime;

	
	printf("\nParallel final Time: %f\n",totalTime);

	free(a);
	free(b);

}
