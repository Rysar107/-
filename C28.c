#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 二叉树结点定义
typedef struct TreeNode {
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

// 队列结点定义
typedef struct QueueNode {
	TreeNode *data;
	struct QueueNode *next;
} QueueNode;

// 队列定义
typedef struct {
	QueueNode *front;
	QueueNode *rear;
} Queue;

// 初始化队列
void initQueue(Queue *queue) {
	queue->front = queue->rear = NULL;
}

// 入队列
void enqueue(Queue *queue, TreeNode *data) {
	QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
	newNode->data = data;
	newNode->next = NULL;
	
	if (queue->rear == NULL) {
		queue->front = queue->rear = newNode;
	} else {
		queue->rear->next = newNode;
		queue->rear = newNode;
	}
}

// 出队列
TreeNode *dequeue(Queue *queue) {
	if (queue->front == NULL) {
		return NULL; // 空队列
	}
	
	QueueNode *temp = queue->front;
	TreeNode *data = temp->data;
	
	if (queue->front == queue->rear) {
		queue->front = queue->rear = NULL;
	} else {
		queue->front = temp->next;
	}
	
	free(temp);
	return data;
}

// 创建二叉树
TreeNode *createBinaryTree() {
	int data;
	scanf("%d", &data);
	
	if (data == -1) {
		return NULL;
	}
	
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = createBinaryTree();
	newNode->right = createBinaryTree();
	
	return newNode;
}

// 判断是否为满二叉树
bool isFullBinaryTree(TreeNode *root) {
	if (root == NULL) {
		return true;
	}
	
	if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)) {
		return false;
	}
	
	return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
}

// 判断是否为完全二叉树
bool isCompleteBinaryTree(TreeNode *root) {
	if (root == NULL) {
		return true;
	}
	
	Queue queue;
	initQueue(&queue);
	enqueue(&queue, root);
	
	while (queue.front != NULL) {
		TreeNode *current = dequeue(&queue);
		
		if (current == NULL) {
			// 遇到空结点，将其子结点入队列
			enqueue(&queue, NULL);
		} else {
			// 将非空结点的左右子结点入队列
			enqueue(&queue, current->left);
			enqueue(&queue, current->right);
		}
	}
	
	// 判断队列中剩余的结点是否都是空结点
	while (queue.front != NULL && queue.front->data == NULL) {
		dequeue(&queue);
	}
	
	// 如果队列中还有非空结点，说明不是完全二叉树
	return queue.front == NULL;
}

int main() {
	printf("请输入以二叉链形式存储的二叉树（以-1表示空结点）：\n");
	TreeNode *root = createBinaryTree();
	
	if (isFullBinaryTree(root)) {
		printf("是满二叉树，");
	} else {
		printf("不是满二叉树，");
	}
	
	if (isCompleteBinaryTree(root)) {
		printf("是完全二叉树。\n");
	} else {
		printf("不是完全二叉树。\n");
	}
	
	return 0;
}

