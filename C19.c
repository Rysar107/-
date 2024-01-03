#include <stdio.h>
#include <stdlib.h>

// 定义链表结点
typedef struct Node {
	int data;
	struct Node* next;
} Node;

// 初始化链表
Node* initList(int n) {
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	Node* current = head;
	
	for (int i = 1; i <= n; i++) {
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->data = i;
		newNode->next = NULL;
		current->next = newNode;
		current = newNode;
	}
	
	return head;
}

// 拆分链表
void splitList(Node* head, Node** oddList, Node** evenList) {
	*oddList = (Node*)malloc(sizeof(Node));
	*evenList = (Node*)malloc(sizeof(Node));
	
	Node* oddCurrent = *oddList;
	Node* evenCurrent = *evenList;
	
	Node* current = head->next;
	int position = 1;
	
	while (current != NULL) {
		if (position % 2 == 1) {
			oddCurrent->next = current;
			oddCurrent = oddCurrent->next;
		} else {
			evenCurrent->next = current;
			evenCurrent = evenCurrent->next;
		}
		
		current = current->next;
		position++;
	}
	
	oddCurrent->next = NULL;
	evenCurrent->next = NULL;
}

// 打印链表
void printList(Node* head) {
	Node* current = head->next;
	
	while (current != NULL) {
		printf("%d -> ", current->data);
		current = current->next;
	}
	
	printf("NULL\n");
}

// 释放链表内存
void freeList(Node** head) {
	Node* current = (*head)->next;
	while (current != NULL) {
		Node* temp = current;
		current = current->next;
		free(temp);
	}
	free(*head);
}

int main() {
	// 输入链表
	Node* head = initList(10);
	printf("输入链表：");
	printList(head);
	
	// 拆分链表
	Node* oddList;
	Node* evenList;
	splitList(head, &oddList, &evenList);
	
	// 输出结果
	printf("输出奇数位置节点：");
	printList(oddList);
	printf("输出偶数位置节点：");
	printList(evenList);
	
	// 释放内存
	freeList(&head);
	freeList(&oddList);
	freeList(&evenList);
	
	return 0;
}

