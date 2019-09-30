#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

#define NUM 10


int main(){
	int i,a[NUM];
	double startTime, totalTime;
	for (i=0;i<NUM;i++){
		a[i]=i+1;
	}

	Node *root=convertToBTS(a,NUM);

	startTime=omp_get_wtime();
	infijaParallel(root,NUM	);
	totalTime=omp_get_wtime()-startTime;


	printf("\nParallel final Time: %f\n",totalTime);


	startTime=omp_get_wtime();
	infija(root);
	totalTime=omp_get_wtime()-startTime;
	printf("\nNormal final Time: %f\n",totalTime);
}

