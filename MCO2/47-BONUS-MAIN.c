/**
 * Programmer: Lu Qinpei, Chazwick Innocencio
 * Code Tester: Agunanne Henry, Lu Qinpei, Chazwick Inocencio
 * 
 * Description: Main program to read a graph from a file, output its representations
 * (set, degree, adjacency list, matrix), and perform BFS and DFS traversals from a chosen start vertex.
 */



/**
 * @file 47-BONUS-MAIN.c
 * @brief Main program for checking if one graph is a subgraph of another using the bonus function.
 */

#include "47-BONUS.c"

/**
 * @brief Main entry point for the subgraph checking program.
 * 
 * Prompts for two input graph files, reads both graphs, and checks if the second graph is a subgraph of the first.
 * The result is output to a file using the bonus() function.
 *
 * @return 0 on success, non-zero on failure.
 */
int main() {
    struct Graph graph1;             /**< First graph (main graph) */
    struct Graph graph2;             /**< Second graph (candidate subgraph) */
    struct Line lines1[MAX_VERTICES];/**< Lines for first graph */
    struct Line lines2[MAX_VERTICES];/**< Lines for second graph */
    
    String8 filename1;
    String8 filename2;

    printf("Enter input filename 1 (e.g., G.TXT): ");
    scanf("%s", filename1);

    if (readGraphFromFile(&graph1, filename1, lines1)){
        printf("Enter input filename 2 (e.g., G.TXT): ");
        scanf("%s", filename2);

        if (readGraphFromFile(&graph2, filename2, lines2)) {
            bonus(graph1, graph2, filename1, filename2);
        } else {
            printf("File %s not found", filename2);
        }
    } else {
        printf("File %s not found", filename1);
    }

    return 0;
}
