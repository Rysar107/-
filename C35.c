#include <stdio.h>
#include <stdlib.h>

// 定义邻接表的结点
typedef struct Node {
	int vertex;
	struct Node* next;
} Node;

// 定义邻接表
typedef struct {
	int numVertices;
	Node** array;
} AdjList;

// 创建新的邻接表结点
Node* createNode(int vertex) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->vertex = vertex;
	newNode->next = NULL;
	return newNode;
}

// 创建图的邻接表
AdjList* createAdjList(int numVertices) {
	int i;
	AdjList* adjList = (AdjList*)malloc(sizeof(AdjList));
	adjList->numVertices = numVertices;
	
	// 分配存储空间
	adjList->array = (Node**)malloc(numVertices * sizeof(Node*));
	
	// 初始化每个链表为空
	for (i = 0; i < numVertices; ++i)
		adjList->array[i] = NULL;
	
	return adjList;
}

// 添加边到邻接表
void addEdge(AdjList* adjList, int src, int dest) {
	// 添加边从src到dest
	Node* newNode = createNode(dest);
	newNode->next = adjList->array[src];
	adjList->array[src] = newNode;
	
	// 由于是无向图，也要添加从dest到src的边
	newNode = createNode(src);
	newNode->next = adjList->array[dest];
	adjList->array[dest] = newNode;
}

// 打印邻接表
void printAdjList(AdjList* adjList) {
	int i;
	for (i = 0; i < adjList->numVertices; ++i) {
		Node* temp = adjList->array[i];
		printf("顶点 %d 的邻接表：", i);
		while (temp) {
			printf(" -> %d", temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}
}

// 创建图的邻接矩阵
int** createAdjMatrix(int numVertices) {
	int i, j;
	int** adjMatrix = (int**)malloc(numVertices * sizeof(int*));
	for (i = 0; i < numVertices; ++i) {
		adjMatrix[i] = (int*)malloc(numVertices * sizeof(int));
		for (j = 0; j < numVertices; ++j)
			adjMatrix[i][j] = 0;
	}
	return adjMatrix;
}

// 添加边到邻接矩阵
void addEdgeToMatrix(int** adjMatrix, int src, int dest) {
	adjMatrix[src][dest] = 1;
	adjMatrix[dest][src] = 1;
}

// 打印邻接矩阵
void printAdjMatrix(int** adjMatrix, int numVertices) {
	int i, j;
	printf("邻接矩阵：\n");
	for (i = 0; i < numVertices; ++i) {
		for (j = 0; j < numVertices; ++j)
			printf("%d ", adjMatrix[i][j]);
		printf("\n");
	}
}

// 邻接表转换为邻接矩阵
int** convertListToMatrix(AdjList* adjList) {
	int i, j;
	int numVertices = adjList->numVertices;
	int** adjMatrix = createAdjMatrix(numVertices);
	
	for (i = 0; i < numVertices; ++i) {
		Node* temp = adjList->array[i];
		while (temp) {
			adjMatrix[i][temp->vertex] = 1;
			temp = temp->next;
		}
	}
	
	return adjMatrix;
}

// 邻接矩阵转换为邻接表
AdjList* convertMatrixToList(int** adjMatrix, int numVertices) {
	int i, j;
	AdjList* adjList = createAdjList(numVertices);
	
	for (i = 0; i < numVertices; ++i) {
		for (j = 0; j < numVertices; ++j) {
			if (adjMatrix[i][j] == 1)
				addEdge(adjList, i, j);
		}
	}
	
	return adjList;
}

// 释放邻接表的内存
void freeAdjList(AdjList* adjList) {
	int i;
	for (i = 0; i < adjList->numVertices; ++i) {
		Node* temp = adjList->array[i];
		while (temp) {
			Node* toFree = temp;
			temp = temp->next;
			free(toFree);
		}
	}
	free(adjList->array);
	free(adjList);
}

// 释放邻接矩阵的内存
void freeAdjMatrix(int** adjMatrix, int numVertices) {
	int i;
	for (i = 0; i < numVertices; ++i)
		free(adjMatrix[i]);
	free(adjMatrix);
}

int main() {
	int numVertices, i, j;
	printf("输入图的顶点数: ");
	scanf("%d", &numVertices);
	
	// 创建邻接表
	AdjList* adjList = createAdjList(numVertices);
	
	// 读入邻接矩阵
	printf("输入邻接矩阵：\n");
	int** adjMatrix = createAdjMatrix(numVertices);
	for (i = 0; i < numVertices; ++i)
		for (j = 0; j < numVertices; ++j)
			scanf("%d", &adjMatrix[i][j]);
	
	// 邻接矩阵转换为邻接表
	adjList = convertMatrixToList(adjMatrix, numVertices);
	
	// 打印邻接表
	printAdjList(adjList);
	
	// 邻接表转换为邻接矩阵
	int** convertedMatrix = convertListToMatrix(adjList);
	
	// 打印邻接矩阵
	printAdjMatrix(convertedMatrix, numVertices);
	
	// 释放内存
	freeAdjList(adjList);
	freeAdjMatrix(adjMatrix, numVertices);
	freeAdjMatrix(convertedMatrix, numVertices);
	
	return 0;
}

