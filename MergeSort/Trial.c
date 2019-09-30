#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mergeSortParallel.h"
#include "mergeSort.h"
#include "randomizeArray.h"

#define n 20

int main(){
	int *a=(int*) calloc(n,sizeof(int));
	int *b=(int*) calloc(n,sizeof(int));
	randomizeArray(a,n);
	randomizeArray(b,n);
	double startTime, totalTime;
	for(int i=0;i<n;i++)
		printf(" %d ",a[i]);
	
	startTime=omp_get_wtime();
	#pragma omp parallel
		{
			#pragma omp sections
			{  
				#pragma omp section
					mergeSortParallel(a,n/2);
				#pragma omp section
					mergeSortParallel(a+n/2,n-n/2);
			}
			
		}
	mergeParallel(a , n/2 , n-n/2);
	totalTime=omp_get_wtime()-startTime;

	printf("\nLista Ordenada\n");
	for(int i=0;i<n;i++)
		printf(" %d ",a[i]);
	printf("\nParallel final Time: %f\n",totalTime);

	startTime=omp_get_wtime();
	mergeSort(b,n);
	totalTime=omp_get_wtime()-startTime;
	printf("\nNormal final Time: %f\n",totalTime);

}
