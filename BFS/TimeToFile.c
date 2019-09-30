#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include "graph.h"
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
	while(n<=10000){
		printf("\nTamaño: %d\t",n);

		Graph* graph = createGraph(n);
	    Graph* graph2 = createGraph(n);
	    int *ptrA = (int*)calloc(2*n,sizeof(int));

		randomizeArray(ptrA,n*2,n);

	    for(i=0;i<2*n;i+=2){
	        addEdge(graph, ptrA[i],ptrA[i+1]);
	        addEdge(graph2, ptrA[i],ptrA[i+1]);
	    }
	    startTime=omp_get_wtime();
		bfs(graph2, 0);
		normalTime=omp_get_wtime()-startTime;
		printf("Normal final Time: %f\t",normalTime);

		startTime=omp_get_wtime();
		bfsParallel(graph2, 0);
		parallelTime=omp_get_wtime()-startTime;
		printf("Parallel final Time: %f\n",parallelTime);

		
		free(ptrA);
    	free(graph);
    	free(graph2);

		fprintf(fPtr,"%d::%f::%f::\n",n,parallelTime,normalTime);

		n+=100;
	}
	fclose(fPtr);
	return 0;
}
