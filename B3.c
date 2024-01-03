#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100

// 队列的节点
typedef struct {
	int x, y, steps;
} Node;

// 队列
typedef struct {
	Node data[MAX_N * MAX_M];
	int front, rear;
} Queue;

// 初始化队列
void initQueue(Queue *q) {
	q->front = q->rear = 0;
}

// 入队列
void enqueue(Queue *q, int x, int y, int steps) {
	q->data[q->rear].x = x;
	q->data[q->rear].y = y;
	q->data[q->rear].steps = steps;
	q->rear++;
}

// 出队列
Node dequeue(Queue *q) {
	return q->data[q->front++];
}

// 是否可以走
int canMove(int x, int y, int N, int M, int maze[MAX_N][MAX_M]) {
	return (x >= 0 && x < N && y >= 0 && y < M && maze[x][y] == 0);
}

// 递归算法
void findShortestPathRecursive(int x, int y, int endX, int endY, int steps, int N, int M, int maze[MAX_N][MAX_M], int *minSteps) {
	if (x == endX && y == endY) {
		if (steps < *minSteps) {
			*minSteps = steps;
		}
		return;
	}
	
	maze[x][y] = 1;  // 标记为已访问
	
	// 上下左右四个方向
	int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	for (int i = 0; i < 4; ++i) {
		int newX = x + directions[i][0];
		int newY = y + directions[i][1];
		
		if (canMove(newX, newY, N, M, maze)) {
			findShortestPathRecursive(newX, newY, endX, endY, steps + 1, N, M, maze, minSteps);
		}
	}
	
	maze[x][y] = 0;  // 恢复为未访问状态
}

// BFS算法
void findShortestPathBFS(int startX, int startY, int endX, int endY, int N, int M, int maze[MAX_N][MAX_M], int *minSteps) {
	Queue q;
	initQueue(&q);
	
	enqueue(&q, startX, startY, 0);
	maze[startX][startY] = 1;  // 标记为已访问
	
	while (q.front < q.rear) {
		Node current = dequeue(&q);
		
		if (current.x == endX && current.y == endY) {
			*minSteps = current.steps;
			return;
		}
		
		// 上下左右四个方向
		int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
		for (int i = 0; i < 4; ++i) {
			int newX = current.x + directions[i][0];
			int newY = current.y + directions[i][1];
			
			if (canMove(newX, newY, N, M, maze)) {
				enqueue(&q, newX, newY, current.steps + 1);
				maze[newX][newY] = 1;  // 标记为已访问
			}
		}
	}
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	
	int maze[MAX_N][MAX_M];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			scanf("%d", &maze[i][j]);
		}
	}
	
	int startX, startY, endX, endY;
	scanf("%d %d %d %d", &startX, &startY, &endX, &endY);
	
	int minStepsRecursive = MAX_N * MAX_M;
	findShortestPathRecursive(startX, startY, endX, endY, 0, N, M, maze, &minStepsRecursive);
	
	int minStepsBFS = MAX_N * MAX_M;
	int mazeCopy[MAX_N][MAX_M];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			mazeCopy[i][j] = maze[i][j];
		}
	}
	findShortestPathBFS(startX, startY, endX, endY, N, M, mazeCopy, &minStepsBFS);
	
	printf("递归算法最短路径步数：%d\n", minStepsRecursive);
	printf("BFS算法最短路径步数：%d\n", minStepsBFS);
	
	return 0;
}

