/**
 * Programmer: Lu Qinpei, Chazwick Inocencio
 * Code Tester: Agunanne Henry, Lu Qinpei, Chazwick Inocencio
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

/**
 * Programmer: Agunanne Henry, Lu Qinpei, Chazwick Innocencio
 * Code Tester: Agunanne Henry, Lu Qinpei
 * 
 * Description: Source file implementing graph initialization, adjacency matrix management,
 * file I/O for adjacency list input, and basic graph algorithms (BFS, DFS, degree, matrix, set, list).
 */


/**
 * @file graph.c
 * @brief Implementation of basic graph functions.
 */

#include "graph.h"


/**
 * @brief Initializes an empty graph and returns it.
 * @return An empty Graph struct.
 */
struct Graph initGraph() {
    struct Graph g;
    int i, j;
    g.vertexCount = 0;
    for (i = 0; i < MAX_VERTICES; i++) {
        for (j = 0; j < MAX_VERTICES; j++) {
            g.adjMatrix[i][j] = 0; /**< No edges initially */
        }
        g.names[i][0] = '\0'; /**< Empty vertex name */
    }
    return g;
}


/**
 * @brief Finds the index of a vertex with the given name in the graph.
 * Adds the vertex if it does not exist and updates indexOut.
 * Returns 1 if found or added, 0 otherwise.
 * @param g Pointer to the graph.
 * @param name Name of the vertex to find or add.
 * @param indexOut Pointer to output index.
 * @return 1 if found or added, 0 otherwise.
 */
int getVertexIndex(struct Graph* g, String8 name, int* indexOut) {
    int i, result = 0;
    if (strcmp(name, "-1") != 0) {
        for (i = 0; i < g->vertexCount; i++) {
            if (strcmp(g->names[i], name) == 0) {
                *indexOut = i;
                result = 1;
            }
        }
        /* If not found, add it */
        if (result == 0 && g->vertexCount < MAX_VERTICES) {
            strcpy(g->names[g->vertexCount], name);
            *indexOut = g->vertexCount;
            g->vertexCount++;
            result = 1;
        }
    }
    return result;
}


/**
 * @brief Adds an undirected edge between name1 and name2 in the graph.
 * @param g Pointer to the graph.
 * @param name1 Name of the first vertex.
 * @param name2 Name of the second vertex.
 */
void addEdge(struct Graph* g, String8 name1, String8 name2) {
    int i = -1, j = -1;
    int ok1 = getVertexIndex(g, name1, &i);
    int ok2 = getVertexIndex(g, name2, &j);

    if (ok1 && ok2) {
        g->adjMatrix[i][j] = 1;
        g->adjMatrix[j][i] = 1;
    }
}


/**
 * @brief Reads the graph from a text file in adjacency list format.
 * Each line is stored in lines[]. Edges are added after all source vertices are recorded.
 * Returns the number of lines (vertices) read.
 * @param g Pointer to the graph to fill.
 * @param filename Name of the input file.
 * @param lines Array of Line structs to fill with vertex/neighbor info.
 * @return Number of lines (vertices) read, or 0 on error.
 */
int readGraphFromFile(struct Graph* g, String8 filename, struct Line lines[]) {
    FILE* file = fopen(filename, "r");
    String8 src, token;
    int i, edgeCount = 0, n;
    struct Edge edges[MAX_VERTICES * (MAX_VERTICES - 1) / 2];

    if (file == NULL) {
        // File not found
        return 0;
    }

    // Read number of vertices (lines)
    fscanf(file, "%d", &n);

    *g = initGraph();  // Reset graph

    // Read each line: add source, store neighbors
    for (i = 0; i < n; i++) {
        fscanf(file, "%s", src);
        strcpy(lines[i].src, src);
        lines[i].neighborCount = 0;

        // Add source vertex now
        int idxSrc;
        getVertexIndex(g, src, &idxSrc);

        // Read neighbors until "-1"
        fscanf(file, "%s", token);
        while (strcmp(token, "-1") != 0) {
            strcpy(lines[i].neighbors[lines[i].neighborCount++], token);

            // Store edge for later addition
            strcpy(edges[edgeCount].u, src);
            strcpy(edges[edgeCount].v, token);
            edgeCount++;
            fscanf(file, "%s", token);
        }
    }

    // Add all edges (neighbors already added as vertices)
    for (i = 0; i < edgeCount; i++) {
        addEdge(g, edges[i].u, edges[i].v);
    }


    int dot;
    for(i = 0; i < strlen(filename); i++){
        if(filename[i] == '.'){
            dot = i;
        }
    }
    filename[dot] = '\0';
    
    fclose(file);
    return n;
}


/**
 * @brief Outputs the set notation of the graph's vertices and edges to a file.
 * @param g The graph to output.
 * @param filename Name of the input file (used to construct output filename).
 */
void set(struct Graph g, String8 filename) {
    int i, j;
    String8 temp;
    char tempFileName[50];
    strcpy(tempFileName, filename);
    strcat(tempFileName, "-SET.TXT");

    FILE* file = fopen(tempFileName, "w");
    if (!file) {
        printf("Error: Could not create %s\n", tempFileName);
    }
    else{
        // Sort vertex names alphabetically
        String8 sortedV[MAX_VERTICES];
        for (i = 0; i < g.vertexCount; i++) {
            strcpy(sortedV[i], g.names[i]);
        }
        for (i = 0; i < g.vertexCount - 1; i++) {
            for (j = 0; j < g.vertexCount - i - 1; j++) {
                if (strcmp(sortedV[j], sortedV[j + 1]) > 0) {
                    strcpy(temp, sortedV[j]);
                    strcpy(sortedV[j], sortedV[j + 1]);
                    strcpy(sortedV[j + 1], temp);
                }
            }
        }
        
        fprintf(file, "V(%s)={",filename);
        for (i = 0; i < g.vertexCount; i++) {
            fprintf(file, "%s", sortedV[i]);
            if (i < g.vertexCount - 1)
                fprintf(file, ",");
        }
        fprintf(file, "}\n");
    }
    
    // Collect unique undirected edges
    struct Edge edges[g.vertexCount * (g.vertexCount -1) / 2];
    int edgeCount = 0;
    for (i = 0; i < g.vertexCount; i++) {
        for (j = i + 1; j < g.vertexCount; j++) {
            if (g.adjMatrix[i][j] == 1) {
                // Store edge with vertices sorted
                if (strcmp(g.names[i], g.names[j]) < 0) {
                    strcpy(edges[edgeCount].u, g.names[i]);
                    strcpy(edges[edgeCount].v, g.names[j]);
                } else {
                    strcpy(edges[edgeCount].u, g.names[j]);
                    strcpy(edges[edgeCount].v, g.names[i]);
                }
                edgeCount++;
            }
        }
    }

    // Sort edges
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

    // Write edges in set notation
    fprintf(file, "E(G)={");
    for (i = 0; i < edgeCount; i++) {
        fprintf(file, "(%s,%s)", edges[i].u, edges[i].v);
        if (i < edgeCount - 1)
            fprintf(file, ",");
    }
    fprintf(file, "}");
    fclose(file);
}


/**
 * @brief Outputs the adjacency list representation of the graph, preserving input file order.
 * Each vertex's neighbors are listed in the order they appeared in the input file.
 * @param g The graph to output.
 * @param filename Name of the input file (used to construct output filename).
 * @param lines Array of Line structs containing input order.
 * @param lineCount Number of lines (vertices).
 */
void list(struct Graph g, String8 filename, struct Line lines[], int lineCount) {
    int i, j;
    char tempFileName[50];
    strcpy(tempFileName, filename);
    strcat(tempFileName, "-LIST.TXT");

    FILE* file = fopen(tempFileName, "w");
    if (!file) {
        printf("Error: Could not create %s\n", tempFileName);
    }
    else{
        // For each vertex (in input order)
        for (i = 0; i < lineCount; i++) {
            fprintf(file, "%s", lines[i].src);

            // List neighbors (in input order)
            for (j = 0; j < lines[i].neighborCount; j++) {
                fprintf(file, "->%s", lines[i].neighbors[j]);
            }

            // End line with backslash as NULL pointer
            fprintf(file, "->\\\n");
        }
    }
    fclose(file);
}


/**
 * @brief Outputs the adjacency matrix representation of the graph to a file.
 * @param g The graph to output.
 * @param filename Name of the input file (used to construct output filename).
 */
void matrix(struct Graph g, String8 filename) {
    int i, j;
    int maxLen = 0;
    FILE* file;
    char tempFileName[50];
    strcpy(tempFileName,filename);
    strcat(tempFileName,"-MATRIX.TXT");
    file = fopen(tempFileName, "w");
    
    if (!file) {
        printf("Error: Could not create %s\n", tempFileName);
    }
    else{
        // Find max length of vertex names for formatting
        for (i = 0; i < g.vertexCount; i++) {
            if (strlen(g.names[i]) > maxLen){
                maxLen = strlen(g.names[i]);
            }
        }
        
        // Print header
        fprintf(file,"      ");
        for (i = 0; i < g.vertexCount; i++) {
            fprintf(file,"%-6s", g.names[i]);
        }
        fprintf(file,"\n");
        
        // Print matrix rows
        for (i = 0; i < g.vertexCount; i++) {
            fprintf(file,"%-6s", g.names[i]);
            for (j = 0; j < g.vertexCount; j++) {
                fprintf(file,"%-6d", g.adjMatrix[i][j]);
            }
            fprintf(file,"\n");
        }
    }
    fclose(file);
}


/**
 * @brief Outputs the degree (number of neighbors) for each vertex in the graph, sorted alphabetically.
 * @param g The graph to output.
 * @param filename Name of the input file (used to construct output filename).
 */
void degree(struct Graph g, String8 filename) {
    int i, j, k;
    String8 temp;
    int idx;
    int degree;
    FILE* file;
    char tempFileName[50];
    strcpy(tempFileName,filename);
    strcat(tempFileName,"-DEGREE.TXT");
    file = fopen(tempFileName, "w");

    // Copy vertex names for sorting
    String8 sorted[MAX_VERTICES];
    for (i = 0; i < g.vertexCount; i++) {
        strcpy(sorted[i], g.names[i]);
    }

    // Bubble sort vertex names alphabetically
    for (i = 0; i < g.vertexCount - 1; i++) {
        for (j = 0; j < g.vertexCount - i - 1; j++) {
            if (strcmp(sorted[j], sorted[j + 1]) > 0) {
                strcpy(temp, sorted[j]);
                strcpy(sorted[j], sorted[j + 1]);
                strcpy(sorted[j + 1], temp);
            }
        }
    }

    // For each sorted vertex, find index and compute degree
    for (i = 0; i < g.vertexCount; i++) {
        idx = -1;
        degree = 0;
        j = 0;
        while (j < g.vertexCount && idx == -1) {
            if (strcmp(sorted[i], g.names[j]) == 0) {
                idx = j;
            }
            j++;
        }
        // Count degree (number of neighbors)
        for (k = 0; k < g.vertexCount; k++) {
            if (g.adjMatrix[idx][k] == 1) {
                degree++;
            }
        }

        // Output to file
        fprintf(file, "%-8s%d\n",sorted[i], degree);
    }
    fclose(file);
}


/**
 * @brief Performs Breadth-First Search from the given start vertex and outputs traversal order to a file.
 * @param g The graph to traverse.
 * @param startVertex Name of the starting vertex.
 * @param filename Name of the input file (used to construct output filename).
 */
void BFS(struct Graph g, String8 startVertex, String8 filename) {
    int i, startIndex = -1;
    FILE* file;
    char tempFileName[50];
    strcpy(tempFileName,filename);
    strcat(tempFileName,"-BFS.txt");
    file = fopen(tempFileName, "w");

    // Find start index for startVertex
    getVertexIndex(&g, startVertex, &startIndex);

    if (startIndex != -1) {
        int visited[MAX_VERTICES] = {0};
        int queue[MAX_VERTICES];
        int front = 0, rear = 0;

        visited[startIndex] = 1;
        queue[rear++] = startIndex;

        while (front < rear) {
            int current = queue[front++];
            fprintf(file,"%s ", g.names[current]);

            // Enqueue all unvisited neighbors
            for (i = 0; i < g.vertexCount; i++) {
                if (g.adjMatrix[current][i] == 1 && visited[i] == 0) {
                    visited[i] = 1;
                    queue[rear++] = i;
                }
            }
        }
    }
    fclose(file);
}


/**
 * @brief Performs Depth-First Search from the given start vertex and outputs traversal order to a file.
 * @param g The graph to traverse.
 * @param startVertex Name of the starting vertex.
 * @param filename Name of the input file (used to construct output filename).
 */
void DFS(struct Graph g, String8 startVertex, String8 filename) {
    int i, startIndex = -1;
    FILE* file;
    char tempFileName[50];
    strcpy(tempFileName,filename);
    strcat(tempFileName,"-DFS.txt");
    file = fopen(tempFileName, "w");

    // Find start index for startVertex
    getVertexIndex(&g, startVertex, &startIndex);

    if (startIndex != -1) {
        int visited[MAX_VERTICES] = {0};
        int stack[MAX_VERTICES];
        int top = -1;

        stack[++top] = startIndex;

        while (top >= 0) {
            int current = stack[top--];

            if (visited[current] == 0) {
                visited[current] = 1;
                fprintf(file,"%s ", g.names[current]);

                // Push neighbors in reverse order for correct traversal
                for (i = g.vertexCount - 1; i >= 0; i--) {
                    if (g.adjMatrix[current][i] == 1 && visited[i] == 0) {
                        stack[++top] = i;
                    }
                }
            }
        }
    }
    fclose(file);
}
