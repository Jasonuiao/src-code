#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "dijkstra.h"

#define MAX_V 100  // 最大顶点数
#define INF INT_MAX

// Floyd-Warshall算法
void floydWarshall(int graph[MAX_V][MAX_V], int V, int dist[MAX_V][MAX_V], int next[MAX_V][MAX_V]) {
    // 初始化
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = (graph[i][j] == 0 && i != j) ? INF : graph[i][j];
            next[i][j] = (graph[i][j] != 0 && i != j) ? j : -1;
        }
    }

    // 动态规划
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // 检测负权重环
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("Graph contains a negative-weight cycle\n");
            exit(1);
        }
    }
}

// 打印最短路径
void printPath(int i, int j, int next[MAX_V][MAX_V]) {
    if (i == j) {
        printf("%d", i);
    } else if (next[i][j] == -1) {
        printf("No path from %d to %d\n", i, j);
    } else {
        printPath(i, next[i][j], next);
        printf(" -> %d", j);
    }
}

int floyd_test(void) {
    int V = 4;  // 顶点数
    int graph[MAX_V][MAX_V] = {
        {0, 3, INF, 7},
        {8, 0, 2, INF},
        {5, INF, 0, 1},
        {2, INF, INF, 0}
    };

    int dist[MAX_V][MAX_V];
    int next[MAX_V][MAX_V];

    floydWarshall(graph, V, dist, next);

    printf("Shortest distances and paths:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                printf("No path from %d to %d\n", i, j);
            } else {
                printf("From %d to %d: distance = %d, path = ", i, j, dist[i][j]);
                printPath(i, j, next);
                printf("\n");
            }
        }
    }

    return 0;
}