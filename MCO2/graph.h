/**
 * Programmer: Agunanne Henry, Lu Qinpei, Chazwick Inocencio
 * Code Tester: Agunanne Henry, Chazwick Inocencio
 * 
 * Description: Header file defining structures and function prototypes for undirected graph representation,
 * input/output operations, and traversal algorithms.
 */


/**
 * @file graph.h
 * @brief Header file for basic graph structures and functions.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @def MAX_VERTICES
 * Maximum number of vertices allowed in the graph.
 */
#define MAX_VERTICES 20

/**
 * @def MAX_NAME_LEN
 * Maximum length for vertex names.
 */
#define MAX_NAME_LEN 9

/**
 * @def MAX_LINE_LEN
 * Maximum length for a line in text files.
 */
#define MAX_LINE_LEN 256

/**
 * @typedef String8
 * Type alias for a string of 8 characters (used for vertex names).
 */
typedef char String8[MAX_NAME_LEN];

/**
 * @struct Graph
 * Represents a simple undirected graph using adjacency matrix.
 */
struct Graph {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];  /**< Adjacency matrix representing edges */
    String8 names[MAX_VERTICES];                /**< Names of the vertices */
    int vertexCount;                            /**< Number of vertices */
};

/**
 * @struct Edge
 * Represents an undirected edge between two vertices.
 */
struct Edge{
    char u[50]; /**< First vertex name */
    char v[50]; /**< Second vertex name */
};

/**
 * @struct Line
 * Stores a line from the input file (source and its neighbors).
 */
struct Line{
    int neighborCount;                   /**< Number of neighbors for this source */
    String8 src;                         /**< Source vertex name */
    String8 neighbors[MAX_VERTICES];     /**< Array of neighbor vertex names */
};


/** Function Prototypes */
struct Graph initGraph(); 
int getVertexIndex(struct Graph* g, String8 name, int* indexOut); 
void addEdge(struct Graph* g, String8 name1, String8 name2); 
int readGraphFromFile(struct Graph* g, String8 filename, struct Line lines[]); 
void set(struct Graph g, String8 filename);
void list(struct Graph g, String8 filename, struct Line lines[], int lineCount); 
void matrix(struct Graph g, String8 filename, struct Line lines[], int lineCount);
void degree (struct Graph g, String8 filename, struct Line lines[], int lineCount);
void BFS(struct Graph g, String8 startVertex,String8 filename); 
void DFS(struct Graph g, String8 startVertex,String8 filename);
void bonus(struct Graph graph1, struct Graph graph2, String8 file1, String8 file2);

#endif // GRAPH_H
