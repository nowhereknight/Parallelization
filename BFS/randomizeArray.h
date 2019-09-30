 #include <stdlib.h>
#include <time.h>
int randomizeArray(int *arr, int size,int n){
	int i;
	srand(time(NULL));
	for(i=0;i<size;i++){
		arr[i]=rand()%n;
	}
}