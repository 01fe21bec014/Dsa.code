#include <stdio.h>
#define MAX_SIZE 100

// Adjacency Matrix structure
struct Graph {
    int vertices;
    int matrix[MAX_SIZE][MAX_SIZE];
};

// Function to initialize the graph
void initGraph(struct Graph* graph, int vertices) {
    graph->vertices = vertices;

    // Initialize all matrix cells to 0
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }
}

// Function to add an edge between two vertices
void addEdge(struct Graph* graph, int src, int dest) {
    // Check if vertices are within the range
    if (src >= 0 && src < graph->vertices && dest >= 0 && dest < graph->vertices) {
        graph->matrix[src][dest] = 1;
        graph->matrix[dest][src] = 1; // Remove this line for directed graphs
    }
}

// Function to print the adjacency matrix
void printGraph(struct Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct Graph graph;
    int numVertices, numEdges;
    int src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    // Initialize the graph
    initGraph(&graph, numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    // Add edges to the graph
    for (int i = 0; i < numEdges; i++) {
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(&graph, src, dest);
    }

    // Print the adjacency matrix
    printGraph(&graph);

    return 0;
}

