#include <stdio.h>
#include <stdlib.h>

// 结点的最大数量
#define MAX_NODES 100

// 结点结构体
typedef struct {
	int id;
	int earliest_start;
	int latest_start;
} Node;

// 箭头结构体
typedef struct {
	int start_node;
	int end_node;
	int duration;
} Arrow;

// 初始化结点数组
void initializeNodes(Node nodes[], int n) {
	for (int i = 0; i < n; i++) {
		nodes[i].id = i;
		nodes[i].earliest_start = -1;
		nodes[i].latest_start = -1;
	}
}

// 计算最早开始时间
int calculateEarliestStart(Node nodes[], Arrow arrows[], int m, int start_node) {
	int max_earliest_start = 0;
	
	for (int i = 0; i < m; i++) {
		if (arrows[i].start_node == start_node) {
			int end_node = arrows[i].end_node;
			int earliest_start = calculateEarliestStart(nodes, arrows, m, end_node) + arrows[i].duration;
			
			if (earliest_start > nodes[start_node].earliest_start) {
				nodes[start_node].earliest_start = earliest_start;
			}
			
			if (earliest_start > max_earliest_start) {
				max_earliest_start = earliest_start;
			}
		}
	}
	
	return max_earliest_start;
}

// 计算最晚开始时间
void calculateLatestStart(Node nodes[], Arrow arrows[], int m, int end_node, int max_earliest_start) {
	for (int i = 0; i < m; i++) {
		if (arrows[i].end_node == end_node) {
			int start_node = arrows[i].start_node;
			int latest_start = nodes[end_node].latest_start - arrows[i].duration;
			
			if (latest_start < nodes[start_node].latest_start || nodes[start_node].latest_start == -1) {
				nodes[start_node].latest_start = latest_start;
			}
			
			calculateLatestStart(nodes, arrows, m, start_node, max_earliest_start);
		}
	}
}

// 输出关键路径
void printCriticalPath(Node nodes[], Arrow arrows[], int m, int start_node, int end_node) {
	printf("%d ", start_node);
	
	for (int i = 0; i < m; i++) {
		if (arrows[i].start_node == start_node && arrows[i].end_node == end_node) {
			printf("%d\n", end_node);
			return;
		}
	}
	
	for (int i = 0; i < m; i++) {
		if (arrows[i].start_node == start_node) {
			printCriticalPath(nodes, arrows, m, arrows[i].end_node, end_node);
		}
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	Node nodes[MAX_NODES];
	initializeNodes(nodes, n);
	
	Arrow arrows[MAX_NODES];
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &arrows[i].start_node, &arrows[i].end_node, &arrows[i].duration);
	}
	
	// 计算每个结点的最早开始时间
	for (int i = 0; i < n; i++) {
		if (nodes[i].earliest_start == -1) {
			calculateEarliestStart(nodes, arrows, m, i);
		}
	}
	
	// 设置结束结点的最晚开始时间为其最早开始时间
	nodes[n - 1].latest_start = nodes[n - 1].earliest_start;
	
	// 计算每个结点的最晚开始时间
	for (int i = n - 2; i >= 0; i--) {
		calculateLatestStart(nodes, arrows, m, i, nodes[i + 1].earliest_start);
	}
	
	// 输出关键路径
	printf("关键路径:\n");
	printCriticalPath(nodes, arrows, m, 0, n - 1);
	
	return 0;
}

