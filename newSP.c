#include <stdlib.h>
#include <stdio.h>

#define INFINITE 10000
#define VISITED 1
#define UNVISITED 0

struct listNode {
    int nodeID;
    struct listNode *next;
};

struct Queue {
    int front, rear, size, capacity;
    int *array;
};

struct listNode **createGraph1(int *numNodes, int *s, int *t);

struct listNode **createGraph2(int *numNodes, int *s, int *t);

void displayGraph(int numNodes, struct listNode **adj, int s, int t);

void destroyGraph(int numNodes, struct listNode **adj);

int numSP(int numNodes, struct listNode **adj, int s, int t);

struct Queue *createQueue(int capacity) {
    struct Queue *queue = (struct Queue *) malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int *) malloc(queue->capacity * sizeof(int));
    return queue;
}

int main() {
    int numNodes;  // Number of nodes in the graph
    int s;         // Source node
    int t;         // Destination node
    struct listNode **adj; // Adjacency list of a graph
    int numPaths;

    adj = createGraph1(&numNodes, &s, &t);
    displayGraph(numNodes, adj, s, t);
    numPaths = numSP(numNodes, adj, s, t);
    printf("Number of shortest paths=%d\n", numPaths);
    destroyGraph(numNodes, adj);
    printf("\n");

    adj = createGraph2(&numNodes, &s, &t);
    displayGraph(numNodes, adj, s, t);
    numPaths = numSP(numNodes, adj, s, t);
    printf("Number of shortest paths=%d\n", numPaths);
    destroyGraph(numNodes, adj);

    return 0;
}

void initializeArray(int array[], int numNodes, int setTo) {
    for (int i = 0; i < numNodes; i++) {
        array[i] = setTo;
    }
}

int isFull(struct Queue *queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(struct Queue *queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue *queue, int item) {
    if (isFull(queue)) {
        printf("full queue\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue *queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}


// Return number of shortest paths in from node s to node t
int numSP(int numNodes, struct listNode **adj, int s, int t) {
    //array to hold dist nodes or not
    int dist[numNodes];
    int count[numNodes];
    int visited[numNodes];
    initializeArray(dist, numNodes, INFINITE);
    initializeArray(count, numNodes, 0);
    initializeArray(visited, numNodes, UNVISITED);
    dist[s] = 0;
    count[s] = 1;
    struct Queue *que = createQueue(numNodes * numNodes);
    enqueue(que, adj[s]->nodeID);
    while (!isEmpty(que)) {
        int u = dequeue(que);
        for (struct listNode *p = adj[u]->next; p != NULL; p = p->next) {
            int v = p->nodeID;
            if(visited[v] == UNVISITED) {
                visited[v] = VISITED;
                int newDistance = dist[u] + 1;
                if(dist[v] <= newDistance) {
                    dist[v] = newDistance;
                    count[v] = count[u];
                } else if(dist[v] > newDistance) {
                    dist[v] = newDistance;
                    count[v] = count[u];
                    enqueue(que, v);
                }
            }
        }


    }
    return count[t];
}

void addAdjList(struct listNode **adj, int u, int v) {
    struct listNode *newNode = (struct listNode *) malloc(sizeof(struct listNode));
    newNode->next = adj[u];
    newNode->nodeID = v;
    adj[u] = newNode;
}

struct listNode **createGraph1(int *numNodes, int *s, int *t) {
    *numNodes = 6;
    *s = 0;
    *t = 5;
    struct listNode **adj = (struct listNode **) malloc((*numNodes) * sizeof(struct listNode *));
    addAdjList(adj, 0, 1);
    addAdjList(adj, 0, 2);
    addAdjList(adj, 1, 3);
    addAdjList(adj, 1, 4);
    addAdjList(adj, 2, 3);
    addAdjList(adj, 2, 4);
    addAdjList(adj, 3, 5);
    addAdjList(adj, 4, 5);
    addAdjList(adj, 1, 2);
    addAdjList(adj, 2, 1);
    return adj;
}

struct listNode **createGraph2(int *numNodes, int *s, int *t) {
    *numNodes = 8;
    *s = 0;
    *t = 7;
    struct listNode **adj = (struct listNode **) malloc((*numNodes) * sizeof(struct listNode *));
    addAdjList(adj, 0, 1);
    addAdjList(adj, 0, 2);
    addAdjList(adj, 1, 2);
    addAdjList(adj, 2, 1);
    addAdjList(adj, 1, 3);
    addAdjList(adj, 1, 4);
    addAdjList(adj, 2, 3);
    addAdjList(adj, 2, 4);
    addAdjList(adj, 3, 5);
    addAdjList(adj, 4, 5);
    addAdjList(adj, 4, 6);
    addAdjList(adj, 6, 3);
    addAdjList(adj, 5, 7);
    addAdjList(adj, 6, 7);
    return adj;
}

void displayGraph(int numNodes, struct listNode **adj, int s, int t) {
    printf("Graph: #nodes=%d, source s=%d, destination t=%d\n", numNodes, s, t);
    printf("Adjacency list:\n");
    for (int i = 0; i < numNodes; i++) {
        printf("%d:", i);
        for (struct listNode *p = adj[i]; p != NULL; p = p->next) {
            printf(" ->%d", p->nodeID);
        }
        printf(" ->/\n");
    }
}

void destroyGraph(int numNodes, struct listNode **adj) {
    for (int i = 0; i < numNodes; i++) {
        for (struct listNode *p = adj[i]; p != NULL;) {
            struct listNode *temp = p->next;
            free(p);
            p = temp;
        }
    }
    free(adj);
}


