#include "47-BONUS.c"


int main() {
    struct Graph graph1;
    struct Graph graph2;
    //int lineCount;
    struct Line lines1[MAX_VERTICES];
    struct Line lines2[MAX_VERTICES];
    
    String8 filename1;
    String8 filename2;
    

    printf("Enter input filename 1 (e.g., G.TXT): ");
    scanf("%s", filename1);

    if (readGraphFromFile(&graph1, filename1, lines1)){

        printf("Enter input filename 2 (e.g., G.TXT): ");
        scanf("%s", filename2);

        if (readGraphFromFile(&graph2, filename2, lines2)) {
            bonus(graph1,graph2, filename1,filename2);
        }else{
            printf("File %s not found", filename2);
        }
    }else{
        printf("File %s not found", filename1);
    }

  return 0;
}
