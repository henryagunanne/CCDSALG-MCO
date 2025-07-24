//#include "graph.h"
#include "47-BONUS.c"


int main() {
    struct Graph graph1;
    struct Graph graph2;
    
    
    String8 filename1;
    String8 filename2;

    printf("Enter input filename (e.g., G.TXT): ");
    scanf("%s", filename1);
    
    printf("Enter input filename (e.g., G.TXT): ");
    scanf("%s", filename2);
    

    readGraphFromFile(&graph1, filename1);
    readGraphFromFile(&graph2, filename2);
    
    bonus(graph1,graph2, filename1,filename2);

  return 0;
}
