#include "graph.h"


int main() {
    struct Graph graph;
    
    String8 filename;
    String8 startVertex;

    printf("Enter input filename (e.g., G.TXT): ");
    scanf("%s", filename);

    if(readGraphFromFile(&graph, filename)){
        set(graph,filename);
        degree(graph, filename);
        list(graph, filename);
        matrix(graph,filename);
        
        printf("Enter input Start Vertex (e.g., Clark): ");
        scanf("%s", startVertex);
        BFS(graph,startVertex,filename);
        DFS(graph, startVertex, filename);
        
    }

  return 0;
}

