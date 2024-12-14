#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "dijkstra.h"

#define MAX_V 100  // 最大顶点数

typedef struct {
    int v;    // 顶点
    int dist; // 距离
} Node;

typedef struct {
    Node data[MAX_V];
    int size;
} MinHeap;

// 初始化最小堆
void initHeap(MinHeap *heap) {
    heap->size = 0;
}

// 插入节点到最小堆
void insertHeap(MinHeap *heap, int v, int dist) {
    heap->data[heap->size].v = v;
    heap->data[heap->size].dist = dist;
    int i = heap->size++;
    while (i > 0 && heap->data[(i - 1) / 2].dist > heap->data[i].dist) {
        Node temp = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = heap->data[i];
        heap->data[i] = temp;
        i = (i - 1) / 2;
    }
}

// 删除最小堆的根节点
Node deleteMin(MinHeap *heap) {
    Node min = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    int i = 0;
    while (2 * i + 1 < heap->size) {
        int child = 2 * i + 1;
        if (child + 1 < heap->size && heap->data[child + 1].dist < heap->data[child].dist) {
            child++;
        }
        if (heap->data[i].dist <= heap->data[child].dist) break;
        Node temp = heap->data[i];
        heap->data[i] = heap->data[child];
        heap->data[child] = temp;
        i = child;
    }
    return min;
}

// 更新最小堆中的节点
void updateHeap(MinHeap *heap, int v, int newDist, int *pos) {
    int i = pos[v];
    if (i == -1) {
        insertHeap(heap, v, newDist);
        pos[v] = heap->size - 1;
    } else {
        heap->data[i].dist = newDist;
        while (i > 0 && heap->data[(i - 1) / 2].dist > heap->data[i].dist) {
            Node temp = heap->data[(i - 1) / 2];
            heap->data[(i - 1) / 2] = heap->data[i];
            heap->data[i] = temp;
            pos[heap->data[i].v] = i;
            pos[heap->data[(i - 1) / 2].v] = (i - 1) / 2;
            i = (i - 1) / 2;
        }
    }
}

// Dijkstra算法
void dijkstra(int graph[MAX_V][MAX_V], int n, int start, int dist[]) {
    MinHeap heap;
    int visited[MAX_V] = {0};
    int pos[MAX_V] = {-1}; // 用于记录每个顶点在堆中的位置

    initHeap(&heap);
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;
    insertHeap(&heap, start, 0);
    pos[start] = 0;

    while (heap.size > 0) {
        Node current = deleteMin(&heap);
        int u = current.v;
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && !visited[v]) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    updateHeap(&heap, v, newDist, pos);
                }
            }
        }
    }
}

int dijkstra_test(void) {
    int n = 5;  // 顶点数
    int start = 0;  // 起点
    int graph[MAX_V][MAX_V] = {
        {0, 10, 0, 5, 0},
        {0, 0, 1, 2, 0},
        {0, 0, 0, 0, 4},
        {0, 3, 9, 0, 2},
        {7, 0, 6, 0, 0}
    };

    int dist[MAX_V];
    dijkstra(graph, n, start, dist);

    printf("Shortest distances from vertex %d:\n", start);
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: %d\n", i, dist[i]);
    }

    return 0;
}