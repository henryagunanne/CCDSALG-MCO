#include "graph.c"


int main() {
    struct Graph graph;
    int i, startIndex = -1;
    
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

      // Find index of the starting vertex
      for (i = 0; i < graph.vertexCount; i++) {
        if (strcmp(graph.names[i], startVertex) == 0) {
            startIndex = i;
        }
      }

      if (startIndex == -1) {
        printf("Vertex %s not found in the graph.\n", startVertex);
      }else{
        BFS(graph,startVertex,filename);
        DFS(graph, startVertex, filename);
      }
        
    }

  return 0;
}

