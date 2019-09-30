#include <omp.h>
#include <stdio.h>
#include "graph.h"
#include "randomizeArray.h"

int main()
{
    int i,n=10;
    double startTime, totalTime;
    Graph* graph = createGraph(n);
    Graph* graph2 = createGraph(n);
    int *ptrA = (int*)calloc(2*n,sizeof(int));

    randomizeArray(ptrA,n*2,n);

    for(i=0;i<2*n;i+=2){
        addEdge(graph, ptrA[i],ptrA[i+1]);
        addEdge(graph2, ptrA[i],ptrA[i+1]);
    }

    startTime=omp_get_wtime();
    bfsParallel(graph2, 0);
    totalTime=omp_get_wtime()-startTime;
    printf("\nParallel final Time: %f\n",totalTime);

    startTime=omp_get_wtime();
    bfs(graph, 0);
    totalTime=omp_get_wtime()-startTime;
    printf("\nNormal final Time: %f\n",totalTime);

    

    
    free(ptrA);
    free(graph);
    free(graph2);
    

    return 0;
}  

/*


void mergeSortParallel(int *arr, int size);
void mergeSort(int *arr, int size);
void merge(int *arr, int size1, int size2);

void merge(int *arr, int p, int q) {
    int temp[p+q];
    int ptr1=0, ptr2=0;

    while (ptr1+ptr2 < p+q) {
        if (ptr1 < p && arr[ptr1] <= arr[p+ptr2] || ptr1 < p && ptr2 >= q)
            temp[ptr1+ptr2] = arr[ptr1++];

        if (ptr2 < q && arr[p+ptr2] < arr[ptr1] || ptr2 < q && ptr1 >= p)
            temp[ptr1+ptr2] = arr[p+ptr2++];
        
    }

    for (int i=0; i < p+q; i++)
        arr[i] = temp[i];
}

void mergeSortParallel(int *arr, int size) {
    if (size == 1)
        return;  
    #pragma omp parallel
    {
	    int p = size/2, q = size-p;
	    //left half
	  	#pragma omp task shared(p,q)
	    mergeSort(arr , p);
	    //rigth half
	    #pragma omp task shared (p,q)
	    mergeSort(arr + p , q);
    	#pragma omp taskwait

    merge(arr , p , q);
	}
}

void mergeSort(int *arr, int size) {
    if (size == 1)
        return;  

	int p = size/2, q = size-p;
	//left half
	mergeSort(arr , p);
	//rigth half
	mergeSort(arr + p , q);

    merge(arr , p , q);
	
}
*/