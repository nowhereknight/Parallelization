
int linearSearch(int *arr, int size,int x) {
    for(int i=0;i<size;i++){
        if( arr[i]==x ){
            return i;
        }
    }
    return -1;
	
}
