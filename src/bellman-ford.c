#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "dijkstra.h"

#define MAX_V 1000  // 最大顶点数

typedef struct Edge {
    int to;
    int weight;
    struct Edge *next;
} Edge;

typedef struct {
    Edge *head[MAX_V];
} Graph;

// 初始化图
void initGraph(Graph *graph) {
    for (int i = 0; i < MAX_V; i++) {
        graph->head[i] = NULL;
    }
}

// 添加边
void addEdge(Graph *graph, int u, int v, int weight) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->to = v;
    e->weight = weight;
    e->next = graph->head[u];
    graph->head[u] = e;
}

// Bellman-Ford算法
int bellmanFord(Graph *graph, int V, int start, int dist[], int parent[]) {
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[start] = 0;

    // 进行 V-1 次松弛操作
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (Edge *e = graph->head[u]; e != NULL; e = e->next) {
                int v = e->to;
                int weight = e->weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    // 检测负权重环
    for (int u = 0; u < V; u++) {
        for (Edge *e = graph->head[u]; e != NULL; e = e->next) {
            int v = e->to;
            int weight = e->weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                return -1;  // 存在负权重环
            }
        }
    }

    return 0;
}

int bellman_ford_test(void) {
    int V = 5;  // 顶点数
    int start = 0;  // 起点
    Graph graph;
    initGraph(&graph);

    // 添加边
    addEdge(&graph, 0, 1, 5);
    addEdge(&graph, 0, 2, 4);
    addEdge(&graph, 1, 2, -2);
    addEdge(&graph, 1, 3, 1);
    addEdge(&graph, 2, 3, 2);
    addEdge(&graph, 3, 4, 3);
    addEdge(&graph, 4, 1, -3);

    int dist[MAX_V];
    int parent[MAX_V];

    if (bellmanFord(&graph, V, start, dist, parent) == -1) {
        printf("Graph contains a negative-weight cycle\n");
    } else {
        printf("Shortest distances from vertex %d:\n", start);
        for (int i = 0; i < V; i++) {
            printf("Vertex %d: %d\n", i, dist[i]);
        }
    }

    // 清理内存
    for (int i = 0; i < V; i++) {
        Edge *e = graph.head[i];
        while (e != NULL) {
            Edge *temp = e;
            e = e->next;
            free(temp);
        }
    }

    return 0;
} 
