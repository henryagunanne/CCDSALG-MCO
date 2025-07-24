/**
 * Programmer: Lu Qinpei
 * Code Tester: Agunanne Henry, Lu Qinpei
 * 
 * Description: Main program to read a graph from a file, output its representations
 * (set, degree, adjacency list, matrix), and perform BFS and DFS traversals from a chosen start vertex.
 */



/**
 * @file main.c
 * @brief Main program for reading a graph file, outputting its representations, and performing traversals.
 */

#include "graph.h"

/**
 * @brief Main entry point for the program.
 * Prompts for input file, reads graph, outputs representations, and performs BFS/DFS.
 * @return 0 on success, non-zero on failure.
 */
int main() {
    struct Graph graph;
    int i, startIndex = -1;
    int lineCount;
    struct Line lines[MAX_VERTICES]; /**< Stores input file lines for adjacency list output */

    String8 filename;
    String8 startVertex;

    printf("Enter input filename (e.g., G.TXT): ");
    scanf("%s", filename);

    /* Read the graph from file and fill lines[] array */
    lineCount = readGraphFromFile(&graph, filename, lines);
    if (lineCount) {
        set(graph, filename);               /**< Output set representation */
        degree(graph, filename);            /**< Output vertex degrees */
        list(graph, filename, lines, lineCount); /**< Output adjacency list (input order) */
        matrix(graph, filename);            /**< Output adjacency matrix */
        
        printf("Enter input Start Vertex (e.g., Clark): ");
        scanf("%s", startVertex);

        /* Find index of the starting vertex (just for error reporting) */
        for (i = 0; i < graph.vertexCount; i++) {
            if (strcmp(graph.names[i], startVertex) == 0) {
                startIndex = i;
            }
        }

        if (startIndex == -1) {
            printf("Vertex %s not found in the graph.\n", startVertex);
        } else {
            BFS(graph, startVertex, filename); /**< Perform BFS and output */
            DFS(graph, startVertex, filename); /**< Perform DFS and output */
        }
    } else {
        printf("File %s not found", filename);
    }
    return 0;
}