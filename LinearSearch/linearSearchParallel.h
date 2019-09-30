
int linearSearchParallel(int *arr, int size,int x) {
    int index=-1;
    #pragma omp parallel for num_threads(4) schedule(static) firstprivate(index) 
	    for(int i=0;i<size/2;i++){
		    if( arr[i]==x ){
		        index = i;
		    }
		}
    return index;
	
}
