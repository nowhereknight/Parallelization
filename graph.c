#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define SIZE 40

typedef struct queue {
    int items[SIZE];
    int front;
    int rear;
} Queue;

typedef struct Graph
{
    int numVertices;
    struct node** adjLists;
    int* visited;
} Graph;

typedef struct node
{
    int vertex;
    struct node* next;
} Node;

Queue* createQueue();
Node* createNode(int);
Graph* createGraph(int vertices);
void enqueue(Queue* q, int);
int dequeue(Queue* q);
void display(Queue* q);
int isEmpty(Queue* q);
void printQueue(Queue* q);

void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void bfs(Graph* graph, int startVertex);
void bfsParallel(Graph* graph, int startVertex);

int main()
{
    int i,from,to,n=20;
    double startTime=0, totalTime=0;
    Graph* graph = createGraph(n);
    srand(time(NULL));
    for(i=0;i<n;i++){
        from=rand()%n;
        to=rand()%n;
        addEdge(graph, from, to);
    }

    startTime=omp_get_wtime();
    bfs(graph, 0);
    totalTime=omp_get_wtime()-startTime;
    printf("\nNormal final Time: %f\n",totalTime);
    free(graph);

    graph = createGraph(n);
    for(i=0;i<n;i++){
        from=rand()%n;
        to=rand()%n;
        addEdge(graph, from, to);
    }
    startTime=omp_get_wtime();
    bfsParallel(graph, 0);
    totalTime=omp_get_wtime()-startTime;
    printf("\nParallel final Time: %f\n",totalTime);

    free(graph);

    return 0;
}    

Graph* createGraph(int vertices)
{
    int i;
    Graph* graph = malloc(sizeof(Graph));

    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));
    
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
 
    return graph;
}

void bfs(Graph* graph, int startVertex) {

    Queue* q = createQueue();
    
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    
    while(!isEmpty(q)){
        //printQueue(q);
        int currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);
    
       Node* temp = graph->adjLists[currentVertex];
    
       while(temp) {
            int adjVertex = temp->vertex;

            if(graph->visited[adjVertex] == 0){
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
       }
    }
}

void bfsParallel(Graph* graph, int startVertex) {

    Queue* q = createQueue();
    
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    
    while(!isEmpty(q)){
        //printQueue(q);
        int currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);
    
       Node* temp = graph->adjLists[currentVertex];
    
       while(temp) {
            int adjVertex = temp->vertex;

            if(graph->visited[adjVertex] == 0){
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
       }
    }
}

 
struct node* createNode(int v)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}
 
void addEdge(Graph* graph, int from, int to)
{
    Node* newNode = createNode(to);
    newNode->next = graph->adjLists[from];
    graph->adjLists[from] = newNode;
 
    newNode = createNode(from);
    newNode->next = graph->adjLists[to];
    graph->adjLists[to] = newNode;
}

Queue* createQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(Queue* q) {
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}

void enqueue(Queue* q, int value){
    if(q->rear == SIZE-1)
        printf("\nQueue is Full!!");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q){
    int item;
    if(isEmpty(q)){
        printf("Queue is empty");
        item = -1;
    }
    else{
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            printf("\nResetting queue\n");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue *q) {
    int i = q->front;

    if(isEmpty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->items[i]);
        }
    }    
}










/*

void bfsParallel(Node* head){
  queue<node*> q;
  q.push(head);
  while (!q.empty()) {
    qSize = q.size();
    #pragma omp parallel for
    for (int i = 0; i < qSize; i++) {
      node* currNode;
      #pragma omp critical
      {
        currNode = q.front();
        q.pop();
      }
      doStuff(currNode);
      #pragma omp critical
      q.push(currNode);
    }
  }*/