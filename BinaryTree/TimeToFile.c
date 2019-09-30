#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "binaryTree.h"

int main(){
	int i,*ptrA,n=10,nthreads;
	double startTime, normalTime, parallelTime;
	FILE *fPtr;
	Node* root;
	fPtr=fopen("statistics.txt","w");
		if(fPtr == NULL){
			printf("File cannot be created");
			exit(0);
		}
	while(n<=150001){
		printf("Size: %d\t",n-1);

		ptrA = (int*)calloc(n,sizeof(int));
		if (ptrA == NULL)
		{
			printf("Error 401. Memory not available");
			exit(0);
		}


		for (i=0;i<n;i++){
			ptrA[i]=i+1;
		}
		root=convertToBTS(ptrA,n);

		startTime=omp_get_wtime();
		infija(root);
		normalTime=omp_get_wtime()-startTime;
		printf("Normal final Time: %f\t",normalTime);

		startTime=omp_get_wtime();
		#pragma omp parallel
		{
			#pragma omp single
			{
				infijaParallel(root,n);
			}
		}
		//#pragma omp taskwait
		parallelTime=omp_get_wtime()-startTime;
		printf("Parallel final Time: %f\n",parallelTime);
		
		free(ptrA);

		fprintf(fPtr,"%d::%f::%f::\n",n,parallelTime,normalTime);

		n+=500;
	}
	fclose(fPtr);
	return 0;
}