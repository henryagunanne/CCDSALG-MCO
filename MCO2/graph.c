#include "graph.h"

struct Graph initGraph() {
    struct Graph g;
    int i, j;
    g.vertexCount = 0;
    for (i = 0; i < MAX_VERTICES; i++) {
        for (j = 0; j < MAX_VERTICES; j++) {
            g.adjMatrix[i][j] = 0;
        }
        g.names[i][0] = '\0';
    }
    return g;
}

int getVertexIndex(struct Graph* g, String8 name, int* indexOut) {
    int i, result = 0;
    
    if (strcmp(name, "-1") != 0) {
        for (i = 0; i < g->vertexCount; i++) {
            if (strcmp(g->names[i], name) == 0) {
                *indexOut = i;
                result = 1;
            }
        }

        if (result == 0 && g->vertexCount < MAX_VERTICES) {
            strcpy(g->names[g->vertexCount], name);
            *indexOut = g->vertexCount;
            g->vertexCount++;
            result = 1;
        }
        }

    

    return result;
}

void addEdge(struct Graph* g, String8 name1, String8 name2) {
    int i = -1, j = -1;
    int ok1 = getVertexIndex(g, name1, &i);
    int ok2 = getVertexIndex(g, name2, &j);

    if (ok1 && ok2) {
        g->adjMatrix[i][j] = 1;
        g->adjMatrix[j][i] = 1;
    }
}
/*
void readGraphFromFile(struct Graph* g, String8 filename) {
    FILE* f = fopen(filename, "r");
    String8 newFilename;
    String8 src;
    int i, n;
    String8 token;

    // retry until the file opens
    while (f == NULL) {
        printf("File '%s' not found. Try again: ", filename);
        scanf("%s", newFilename);
        f = fopen(newFilename, "r");
        filename = newFilename;
    }
    
    // read number of vertices
    fscanf(f, "%d", &n);

    *g = initGraph();  // reset graph

    for (i = 0; i < n; i++) {
        
        // read the source vertex name
        fscanf(f, "%s", src);

        if (strcmp(src, "-1") != 0) {
            fscanf(f, "%s", token); // Priming read: get the first neighbor token

            // Continue reading until token == "-1"
            while (strcmp(token, "-1") != 0) {
                addEdge(g, src, token); // Add edge src <-> token
                fscanf(f, "%s", token); // Read next token
                   }
               }
    }
    
    filename[1] = '\0';

    fclose(f);
}


void readGraphFromFile(struct Graph* g, String8 filename) {
    FILE* file = fopen(filename, "r");
    String8 newFilename;
    String8 src;
    int i, n;
    String8 token;
    String8 sources[MAX_VERTICES];

    // Retry until the file opens
    if (file == NULL) {
        printf("File '%s' not found", filename);
    }
    
    else{
        // Read number of vertices
        fscanf(file, "%d", &n);

        *g = initGraph();  // Reset graph

        // Pass 1: Collect all source vertices in order
        for (i = 0; i < n; i++) {
            fscanf(file, "%s", sources[i]); // Read source vertex name

            // Skip the rest of the line for now (neighbors)
            do {
                fscanf(file, "%s", token);
            } while (strcmp(token, "-1") != 0);
        }

        // Add all source vertices first (in order)
        for (i = 0; i < n; i++) {
            int idx;
            getVertexIndex(g, sources[i], &idx);  // This will add them in order
        }

        // Rewind file to re-read edges
        rewind(file);
        fscanf(file, "%d", &n); // Skip the vertex count again

        // Pass 2: Actually add edges now
        for (i = 0; i < n; i++) {
            fscanf(file, "%s", src); // Source vertex

            fscanf(file, "%s", token); // First neighbor
            while (strcmp(token, "-1") != 0) {
                addEdge(g, src, token); // Add edge
                fscanf(file, "%s", token);
            }
        }

        filename[1] = '\0';
    }
    fclose(file);
}
*/
int readGraphFromFile(struct Graph* g, String8 filename, struct Line lines[]) {
    FILE* file = fopen(filename, "r");
    String8 src, token;
    int i, edgeCount = 0, n;

    struct Edge edges[MAX_VERTICES * (MAX_VERTICES - 1) / 2];

    if (file == NULL) {
        printf("File '%s' not found\n", filename);
    }
    else{
        // Read number of vertices (lines)
        fscanf(file, "%d", &n);

        *g = initGraph();  // Reset graph

        // Read line by line: add source immediately, store edges
        for (i = 0; i < n; i++) {
            fscanf(file, "%s", src);
            
            // Record this line's source vertex
            strcpy(lines[i].src, src);
            lines[i].neighborCount = 0;

            // Add the source vertex now (preserves order)
            int idxSrc;
            getVertexIndex(g, src, &idxSrc);

            // Now read neighbors, store edges but don't add vertices yet
            fscanf(file, "%s", token);
            while (strcmp(token, "-1") != 0) {
                strcpy(lines[i].neighbors[lines[i].neighborCount++], token);
                
                strcpy(edges[edgeCount].u, src);
                strcpy(edges[edgeCount].v, token);
                edgeCount++;
                fscanf(file, "%s", token);
            }
        }

        // Now add edges and neighbors (neighbors added after sources)
        for (i = 0; i < edgeCount; i++) {
            addEdge(g, edges[i].u, edges[i].v);
        }
        filename[1] = '\0';
    }


    fclose(file);
    return n;
}



void set(struct Graph g, String8 filename){
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
    
    // --- Collect edges (unique, undirected) ---
    struct Edge edges[g.vertexCount * (g.vertexCount -1) / 2];
    int edgeCount = 0;

    // Only look at upper triangle (i < j) to avoid duplicates
    for (i = 0; i < g.vertexCount; i++) {
        for (j = i + 1; j < g.vertexCount; j++) {
            if (g.adjMatrix[i][j] == 1) {
                // Always store edges with vertices sorted (u < v)
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

    // --- Sort edges by start vertex, then end vertex ---
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

    // --- Write edges ---
    fprintf(file, "E(G)={");
    for (i = 0; i < edgeCount; i++) {
        fprintf(file, "(%s,%s)", edges[i].u, edges[i].v);
        if (i < edgeCount - 1)
            fprintf(file, ",");
    }
    fprintf(file, "}");
    
    fclose(file);
}

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
        // For each vertex in the order they were added (g.names[])
        for (i = 0; i < lineCount; i++) {
            fprintf(file, "%s", lines[i].src);

            // List all neighbors (in the order they were added)
            for (j = 0; j < lines[i].neighborCount; j++) {
                fprintf(file, "->%s", lines[i].neighbors[j]);
            }

            // End of list with "\"
            fprintf(file, "->\\\n");
        }
    }

    fclose(file);
}

void matrix(struct Graph g, String8 filename) {
    int i, j;
    int maxLen = 0;
    FILE* file;
    char tempFileName[15];
    strcpy(tempFileName,filename);
    strcat(tempFileName,"-MATRIX.TXT");
    file = fopen(tempFileName, "w");
    
    if (!file) {
        printf("Error: Could not create %s\n", tempFileName);
    }
    
    else{
        for (i = 0; i < g.vertexCount; i++) {
            if (strlen(g.names[i]) > maxLen){
                maxLen = strlen(g.names[i]);
            }
        }
        
        fprintf(file,"      ");
        for (i = 0; i < g.vertexCount; i++) {
            fprintf(file,"%-6s", g.names[i]);
        }
        fprintf(file,"\n");
        
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


void degree(struct Graph g, String8 filename) {
    int i, j, k;
    String8 temp;
    int idx;
    int degree;
    FILE* file;
    char tempFileName[15];
    strcpy(tempFileName,filename);
    strcat(tempFileName,"-DEGREE.TXT");
    file = fopen(tempFileName, "w");

    // Create and copy vertex names for sorting
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

    // For each sorted name, find original index and compute degree
    for (i = 0; i < g.vertexCount; i++) {
        idx = -1;
        degree = 0;

        // Find matching index (without break)
        j = 0;
        while (j < g.vertexCount && idx == -1) {
            if (strcmp(sorted[i], g.names[j]) == 0) {
                idx = j;
            }
            j++;
        }

        // Count degree
        for (k = 0; k < g.vertexCount; k++) {
            if (g.adjMatrix[idx][k] == 1) {
                degree++;
            }
        }
        

        // Output
       // printf("%-6s%d\n", sorted[i], degree);
        fprintf(file, "%-8s%d\n",sorted[i], degree);
    }
    fclose(file);
}

void BFS(struct Graph g, String8 startVertex, String8 filename) {
    int i, startIndex = -1;
    FILE* file;
    char tempFileName[15];
    strcpy(tempFileName,filename);
    strcat(tempFileName,"-BFS.TXT");
    file = fopen(tempFileName, "w");

    // Find index of the starting vertex
    for (i = 0; i < g.vertexCount; i++) {
        if (strcmp(g.names[i], startVertex) == 0) {
            startIndex = i;
        }
    }

    if (startIndex == -1) {
        printf("Vertex %s not found.\n", startVertex);
    }
    else {
        // Initialize visited array and queue
        int visited[MAX_VERTICES];
        for (i = 0; i < MAX_VERTICES; i++) {
            visited[i] = 0;
        }
        int queue[MAX_VERTICES];
        int front = 0, rear = 0;

        // Start BFS from startIndex
        visited[startIndex] = 1;
        queue[rear++] = startIndex;

        //printf("BFS starting from %s: ", startVertex);

        while (front < rear) {
            int current = queue[front++];
            fprintf(file,"%s ", g.names[current]);

            // Explore neighbors
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

void DFS(struct Graph g, String8 startVertex, String8 filename) {
    int i, startIndex = -1;
    FILE* file;
    char tempFileName[15];
    strcpy(tempFileName,filename);
    strcat(tempFileName,"-DFS.TXT");
    file = fopen(tempFileName, "w");

    // Find index of the starting vertex
    for (i = 0; i < g.vertexCount; i++) {
        if (strcmp(g.names[i], startVertex) == 0) {
            startIndex = i;
        }
    }

    if (startIndex == -1) {
        printf("Vertex %s not found.\n", startVertex);
    }
    
    else{
        // Initialize visited array and stack
        int visited[MAX_VERTICES];
        for (i = 0; i < MAX_VERTICES; i++) {
            visited[i] = 0;
        }
        int stack[MAX_VERTICES];
        int top = -1;

        // Start DFS from startIndex
        stack[++top] = startIndex;

        while (top >= 0) {
            int current = stack[top--];

            if (visited[current] == 0) {
                visited[current] = 1;
                fprintf(file,"%s ", g.names[current]);

                // Push neighbors (in reverse order for consistent traversal)
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
    
    else{
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

            // Find indces in graph1 for u and v
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

