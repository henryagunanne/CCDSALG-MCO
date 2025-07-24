
#include "graph.h"


int main() {
    struct Graph graph;
    int i, startIndex = -1;
    int lineCount;
    struct Line lines[MAX_VERTICES];
    
    
    String8 filename;
    String8 startVertex;

    printf("Enter input filename (e.g., G.TXT): ");
    scanf("%s", filename);

    lineCount = readGraphFromFile(&graph, filename,lines);
    if(lineCount){
      set(graph,filename);
      degree(graph, filename);
      list(graph, filename,lines,lineCount);
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
        
    }else{
       printf("File %s not found", filename);
    }

  return 0;
}

