
void merge(int *arr, int p, int q);

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

void merge(int *arr, int p, int q){
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