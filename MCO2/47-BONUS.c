/**
 * Programmer: Lu Qinpei, 
 * Code Tester: Agunanne Henry, Lu Qinpei
 * 
 * Description: Implements the subgraph checking algorithm and file output. Compares all vertices and edges
 * of a candidate subgraph against a main graph, and prints verification results to a summary file.
 */


/**
 * @file 47-BONUS.c
 * @brief Implements the function to check if one graph is a subgraph of another and outputs the result.
 */

#include "graph.h"

/**
 * @brief Checks if graph2 is a subgraph of graph1 and outputs the result to a file.
 * 
 * The function compares vertices and edges of graph2 against those in graph1.
 * It writes the result to a file named "<file1>-<file2>-SUBGRAPH.TXT".
 * Each vertex and edge from graph2 is checked and annotated with '+' (present) or '-' (missing).
 * At the end, a summary line indicates whether graph2 is a subgraph of graph1.
 *
 * @param graph1 The main graph.
 * @param graph2 The candidate subgraph.
 * @param file1 Filename of the first input graph.
 * @param file2 Filename of the second input graph.
 */
void bonus(struct Graph graph1, struct Graph graph2, String8 file1, String8 file2) {
    int i, j;

    // --- Prepare output filename ---
    char outFile[100];
    strcpy(outFile, file1);
    strcat(outFile, "-");
    strcat(outFile, file2);
    strcat(outFile, "-SUBGRAPH.TXT");

    FILE *file = fopen(outFile, "w");
    if (!file) {
        printf("Error: Could not create %s\n", outFile);
    }
    else {
        // --- Sort vertices of graph2 alphabetically ---
        String8 sortedVertices[MAX_VERTICES];
        for (i = 0; i < graph2.vertexCount; i++) {
            strcpy(sortedVertices[i], graph2.names[i]);
        }
        for (i = 0; i < graph2.vertexCount - 1; i++) {
            for (j = 0; j < graph2.vertexCount - i - 1; j++) {
                if (strcmp(sortedVertices[j], sortedVertices[j + 1]) > 0) {
                    String8 temp;
                    strcpy(temp, sortedVertices[j]);
                    strcpy(sortedVertices[j], sortedVertices[j + 1]);
                    strcpy(sortedVertices[j + 1], temp);
                }
            }
        }

        // --- Check and print vertices ---
        int allVerticesMatch = 1;
        for (i = 0; i < graph2.vertexCount; i++) {
            int found = 0;
            for (j = 0; j < graph1.vertexCount; j++) {
                if (strcmp(sortedVertices[i], graph1.names[j]) == 0) {
                    found = 1;
                }
            }

            if (found == 1) {
                fprintf(file, "%s +\n", sortedVertices[i]);
            } else {
                fprintf(file, "%s -\n", sortedVertices[i]);
                allVerticesMatch = 0;
            }
        }

        // --- Collect edges from graph2 ---
        struct Edge edges[MAX_VERTICES * (MAX_VERTICES - 1) / 2];
        int edgeCount = 0;
        for (i = 0; i < graph2.vertexCount; i++) {
            for (j = i + 1; j < graph2.vertexCount; j++) {
                if (graph2.adjMatrix[i][j] == 1) {
                    // Store edge with sorted vertices (u < v)
                    if (strcmp(graph2.names[i], graph2.names[j]) < 0) {
                        strcpy(edges[edgeCount].u, graph2.names[i]);
                        strcpy(edges[edgeCount].v, graph2.names[j]);
                    } else {
                        strcpy(edges[edgeCount].u, graph2.names[j]);
                        strcpy(edges[edgeCount].v, graph2.names[i]);
                    }
                    edgeCount++;
                }
            }
        }

        // --- Sort edges alphabetically (by u then v) ---
        for (i = 0; i < edgeCount - 1; i++) {
            for (j = 0; j < edgeCount - i - 1; j++) {
                if (strcmp(edges[j].u, edges[j + 1].u) > 0 ||
                   (strcmp(edges[j].u, edges[j + 1].u) == 0 &&
                    strcmp(edges[j].v, edges[j + 1].v) > 0)) {
                    struct Edge tmp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = tmp;
                }
            }
        }

        // --- Check and print edges ---
        int allEdgesMatch = 1;
        for (i = 0; i < edgeCount; i++) {
            int found = 0;
            int idx1 = -1, idx2 = -1;

            // Find indices in graph1 for u and v
            for (j = 0; j < graph1.vertexCount; j++) {
                if (strcmp(graph1.names[j], edges[i].u) == 0) idx1 = j;
                if (strcmp(graph1.names[j], edges[i].v) == 0) idx2 = j;
            }

            // Check if edge exists in graph1
            if (idx1 != -1 && idx2 != -1 && graph1.adjMatrix[idx1][idx2] == 1) {
                found = 1;
            }

            if (found == 1) {
                fprintf(file, "(%s,%s) +\n", edges[i].u, edges[i].v);
            } else {
                fprintf(file, "(%s,%s) -\n", edges[i].u, edges[i].v);
                allEdgesMatch = 0;
            }
        }

        // --- Final result ---
        if (allVerticesMatch == 1 && allEdgesMatch == 1) {
            fprintf(file, "%s is a subgraph of %s.\n", file2, file1);
        } else {
            fprintf(file, "%s is NOT a subgraph of %s.\n", file2, file1);
        }
    }

    fclose(file);
}