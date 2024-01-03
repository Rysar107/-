#include <stdio.h>
#include <stdlib.h>

#define INF 999999

// 边的结构体
struct Edge {
	int source, destination, weight;
};

// Bellman-Ford算法实现
void bellmanFord(int V, int E, struct Edge edges[], int source) {
	int distance[V];
	
	// 初始化距离数组
	for (int i = 0; i < V; i++) {
		distance[i] = INF;
	}
	distance[source - 1] = 0;
	
	// 进行V-1次松弛操作
	for (int i = 0; i < V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = edges[j].source - 1;
			int v = edges[j].destination - 1;
			int w = edges[j].weight;
			
			if (distance[u] != INF && distance[u] + w < distance[v]) {
				distance[v] = distance[u] + w;
			}
		}
	}
	
	// 输出结果
	for (int i = 0; i < V; i++) {
		if (distance[i] == INF) {
			printf("INF\n");
		} else {
			printf("%d\n", distance[i]);
		}
	}
}

int main() {
	int V, E;
	scanf("%d %d", &V, &E);
	
	// 读取边的信息
	struct Edge edges[E];
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &edges[i].source, &edges[i].destination, &edges[i].weight);
	}
	
	int source;
	scanf("%d", &source);
	
	// 运行Bellman-Ford算法
	bellmanFord(V, E, edges, source);
	
	return 0;
}
