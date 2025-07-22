#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTICES 20
#define MAX_NAME_LEN 9
#define MAX_LINE_LEN 256

typedef char String8[MAX_NAME_LEN];

struct Graph {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    String8 names[MAX_VERTICES];
    int vertexCount;
};
struct Graph initGraph(); //DONE
int getVertexIndex(struct Graph* g, String8 name, int* indexOut); //DONE
void addEdge(struct Graph* g, String8 name1, String8 name2); //DONE
void readGraphFromFile(struct Graph* g, String8 filename); //DONE
void list(struct Graph g, String8 filename); // !!! NEED EDIT
void matrix(struct Graph g, String8 filename); //DONE
void degree (struct Graph g, String8 filename); //DONE
void BFS(struct Graph g, String8 startVertex,String8 filename); //DONE
void DFS(struct Graph g, String8 startVertex,String8 filename); //DONE
