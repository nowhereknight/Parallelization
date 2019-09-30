void swap(int* a,int* b);

typedef struct node { 
    int val; 
    int index; 
} Node;

#pragma omp declare reduction(maximum : Node : omp_out = omp_in.val > omp_out.val ? omp_in : omp_out)

void selectionSort(int* A, int n){
    int temp;
    for(int i=0; i < n; i++){
        int maxpos = i;
        for(int j=i+1; j < n; j++){
            if(A[j] < A[maxpos]){
                maxpos = j;
            }
        }
        swap(&A[i], &A[maxpos]);
    }
}

void selectionSortParallel(int* A, int n){
    Node max;
    int temp,j,i;
    for(j =0; j < n; j++){
        max.val = A[j];
        max.index = j;

        #pragma omp parallel for num_threads(2) reduction(maximum:max)
        for(i=j+1; i< n; ++i){
            if(A[i] > max.val){
                max.val = A[i];
                max.index = i;
            }
        }
        temp = A[j];
        A[j] = A[max.index];
        A[max.index] = temp;
    }
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}