#include <stdlib.h>
#include <stdio.h>

struct listNode {
    int nodeID;
    struct listNode *next;
};

struct listNode **createGraph1(int *numNodes, int *s, int *t);

struct listNode **createGraph2(int *numNodes, int *s, int *t);

void displayGraph(int numNodes, struct listNode **adj, int s, int t);

void destroyGraph(int numNodes, struct listNode **adj);

int numSP(int numNodes, struct listNode **adj, int s, int t);

int main() {
    int numNodes;  // Numbere of nodes in the graph
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

int numSP(int numNodes, struct listNode **adj, int s, int t) {
    return 0;
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


