#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
#define MAX_EDGES 100

typedef struct {
	int start;
	int end;
	int weight;
} Edge;

typedef struct {
	Edge edges[MAX_EDGES];
	int numNodes;
	int numEdges;
} AOEGraph;

typedef struct {
	int* earliestStart;
	int* latestStart;
} CriticalPath;

void initAOEGraph(AOEGraph* graph) {
	graph->numNodes = 0;
	graph->numEdges = 0;
}

void readAOEGraph(AOEGraph* graph) {
	printf("请输入AOE网的节点数和边数：");
	scanf("%d %d", &graph->numNodes, &graph->numEdges);
	
	printf("请输入AOE网的边信息（起点 终点 权重）：\n");
	for (int i = 0; i < graph->numEdges; ++i) {
		scanf("%d %d %d", &graph->edges[i].start, &graph->edges[i].end, &graph->edges[i].weight);
	}
}

void topologicalSortUtil(AOEGraph* graph, int node, int visited[], int stack[], int* stackIndex) {
	visited[node] = 1;
	
	for (int i = 0; i < graph->numEdges; ++i) {
		if (graph->edges[i].start == node && !visited[graph->edges[i].end]) {
			topologicalSortUtil(graph, graph->edges[i].end, visited, stack, stackIndex);
		}
	}
	
	stack[(*stackIndex)++] = node;
}

void topologicalSort(AOEGraph* graph, int sortedNodes[]) {
	int visited[MAX_NODES] = {0};
	int stack[MAX_NODES];
	int stackIndex = 0;
	
	for (int i = 0; i < graph->numNodes; ++i) {
		if (!visited[i]) {
			topologicalSortUtil(graph, i, visited, stack, &stackIndex);
		}
	}
	
	for (int i = 0; i < graph->numNodes; ++i) {
		sortedNodes[i] = stack[graph->numNodes - i - 1];
	}
}

int calculateCriticalPathCount(AOEGraph* graph) {
	int sortedNodes[MAX_NODES];
	topologicalSort(graph, sortedNodes);
	
	int earliestStart[MAX_NODES] = {0};
	int latestStart[MAX_NODES] = {0};
	
	for (int i = 0; i < graph->numNodes; ++i) {
		int node = sortedNodes[i];
		
		for (int j = 0; j < graph->numEdges; ++j) {
			if (graph->edges[j].end == node) {
				// 计算最早开始时间
				int tempES = earliestStart[graph->edges[j].start] + graph->edges[j].weight;
				earliestStart[node] = (tempES > earliestStart[node]) ? tempES : earliestStart[node];
			}
		}
	}

	return 0; 
}

int main() {
	AOEGraph graph;
	initAOEGraph(&graph);
	
	readAOEGraph(&graph);
	
	int criticalPathCount = calculateCriticalPathCount(&graph);
	
	printf("关键路径数量: %d\n", criticalPathCount);
	
	return 0;
}

