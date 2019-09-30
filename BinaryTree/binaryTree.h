#include <stdlib.h>
//
typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
} Node;


Node* convertToBTS(int* array, int size) {
    if( size == 1)
    	return NULL;
	Node* root= (Node*)malloc(sizeof(Node));
    if(root == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
	root->key=array[size/2-1];
	root->left=convertToBTS(array,size/2);
	root->right=convertToBTS(array+size/2,size-size/2);
	return root;
}

void infijaParallel(Node* root, int n){
  if( root == NULL){
    return;
  }
  #pragma omp task final(n<10000)
    infijaParallel(root->left,n/2);
  //root->key+=1;
  infijaParallel(root->right, n-n/2);
  //#pragma omp taskwait
}

Node* infija(Node* root){
  if( root == NULL){
    return NULL;
  }
  infija(root->left);;
  //root->key+=1;
  infija(root->right);
}

