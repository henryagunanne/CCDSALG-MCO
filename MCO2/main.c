#include "graph.h"


int main() {
    struct Graph graph = initGraph();
    
    String8 filename;

    printf("Enter input filename (e.g., G.TXT): ");
    scanf("%s", filename);

    readGraphFromFile(&graph, filename);
    
    matrix(graph,filename);
    degree(graph, filename);
    list(graph, filename);
    BFS(graph,"Clark",filename);
    DFS(graph, "Clark", filename);
    

  return 0;
}
