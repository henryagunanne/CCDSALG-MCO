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

/**
 * @brief Initializes and returns an empty graph.
 * @return An empty Graph struct.
 */
struct Graph initGraph(); //DONE

/**
 * @brief Returns the index of a vertex in graph g with name 'name'.
 * Adds the vertex if not found (unless name is "-1").
 * @param g Pointer to the graph.
 * @param name Name of the vertex to find or add.
 * @param indexOut Pointer to output index.
 * @return 1 if found or added, 0 otherwise.
 */
int getVertexIndex(struct Graph* g, String8 name, int* indexOut); //DONE

/**
 * @brief Adds an undirected edge between name1 and name2 in graph g.
 * @param g Pointer to the graph.
 * @param name1 Name of the first vertex.
 * @param name2 Name of the second vertex.
 */
void addEdge(struct Graph* g, String8 name1, String8 name2); //DONE

/**
 * @brief Reads a graph from the text file 'filename' and fills the lines[] array.
 * @param g Pointer to the graph to fill.
 * @param filename Name of the input file.
 * @param lines Array of Line structs to fill with vertex/neighbor info.
 * @return Number of lines (vertices) read, or 0 on error.
 */
int readGraphFromFile(struct Graph* g, String8 filename, struct Line lines[]); //DONE

/**
 * @brief Outputs the set representation of the graph to a file.
 * @param g The graph to output.
 * @param filename Name of the input file (used to construct output filename).
 */
void set(struct Graph g, String8 filename); //DONE

/**
 * @brief Outputs the adjacency list representation of the graph, preserving input order.
 * @param g The graph to output.
 * @param filename Name of the input file (used to construct output filename).
 * @param lines Array of Line structs containing input order.
 * @param lineCount Number of lines (vertices).
 */
void list(struct Graph g, String8 filename, struct Line lines[], int lineCount); // !!! NEED EDIT

/**
 * @brief Outputs the adjacency matrix representation of the graph to a file.
 * @param g The graph to output.
 * @param filename Name of the input file (used to construct output filename).
 */
void matrix(struct Graph g, String8 filename); //DONE

/**
 * @brief Outputs the degree of each vertex in the graph to a file.
 * @param g The graph to output.
 * @param filename Name of the input file (used to construct output filename).
 */
void degree (struct Graph g, String8 filename); //DONE

/**
 * @brief Performs BFS from the given start vertex and outputs traversal to a file.
 * @param g The graph to traverse.
 * @param startVertex Name of the starting vertex.
 * @param filename Name of the input file (used to construct output filename).
 */
void BFS(struct Graph g, String8 startVertex,String8 filename); //DONE

/**
 * @brief Performs DFS from the given start vertex and outputs traversal to a file.
 * @param g The graph to traverse.
 * @param startVertex Name of the starting vertex.
 * @param filename Name of the input file (used to construct output filename).
 */
void DFS(struct Graph g, String8 startVertex,String8 filename); //DONE

/**
 * @brief Checks if one graph is a subgraph of another and outputs result to a file.
 * @param graph1 The main graph.
 * @param graph2 The subgraph to check.
 * @param file1 Name of the first input file.
 * @param file2 Name of the second input file.
 */
void bonus(struct Graph graph1, struct Graph graph2, String8 file1, String8 file2);

#endif // GRAPH_H