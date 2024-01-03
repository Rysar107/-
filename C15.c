#include <stdio.h>
#include <stdlib.h>

// 定义双向链表结点
typedef struct Node {
	int data;
	struct Node *prev;
	struct Node *next;
} Node;

// 初始化双向链表
Node *initList() {
	Node *head = (Node *)malloc(sizeof(Node));
	head->prev = NULL;
	head->next = NULL;
	return head;
}

// 在链表末尾插入元素
void insertEnd(Node *head, int data) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	
	Node *current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	
	current->next = newNode;
	newNode->prev = current;
}

// 递归判断B是否是A的子序列
int isSubsequence(Node *A, Node *B) {
	if (B == NULL) {
		return 1; // B为空，是子序列
	}
	
	if (A == NULL) {
		return 0; // A为空，不是子序列
	}
	
	if (A->data == B->data) {
		return isSubsequence(A->next, B->next);
	} else {
		return isSubsequence(A->next, B);
	}
}

int main() {
	// 输入序列A
	Node *A = initList();
	printf("请输入序列A，按下回车键结束输入:\n");
	int input;
	while (1) {
		if (scanf("%d", &input) == 1) {
			insertEnd(A, input);
		} else {
			break;
		}
		char c = getchar(); // 读取逗号或回车
		if (c == '\n') {
			break;
		}
	}
	
	// 输入序列B
	Node *B = initList();
	printf("请输入序列B，按下回车键结束输入:\n");
	while (1) {
		if (scanf("%d", &input) == 1) {
			insertEnd(B, input);
		} else {
			break;
		}
		char c = getchar(); // 读取逗号或回车
		if (c == '\n') {
			break;
		}
	}
	
	// 判断B是否是A的子序列
	if (isSubsequence(A->next, B->next)) {
		printf("是子序列。\n");
	} else {
		printf("不是子序列。\n");
	}
	
	// 释放链表内存
	Node *temp;
	while (A != NULL) {
		temp = A;
		A = A->next;
		free(temp);
	}
	
	while (B != NULL) {
		temp = B;
		B = B->next;
		free(temp);
	}
	
	return 0;
}

