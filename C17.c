#include <stdio.h>
#include <stdlib.h>

// 定义循环链表结点
typedef struct Node {
	int data;
	struct Node *next;
} Node;

// 创建循环链表
Node* createCircularLinkedList(int n) {
	Node *head = (Node *)malloc(sizeof(Node));
	head->data = 1;
	head->next = NULL;
	
	Node *current = head;
	
	for (int i = 2; i <= n; i++) {
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->data = i;
		newNode->next = head; // 将新结点连接到链表末尾
		current->next = newNode;
		current = newNode;
	}
	
	return head;
}

// 解决约瑟夫环问题
void josephus(int totalPeople, int interval) {
	Node *head = createCircularLinkedList(totalPeople);
	Node *current = head;
	
	// 找到链表末尾
	while (current->next != head) {
		current = current->next;
	}
	
	// 从头开始循环报数
	while (head->next != head) {
		// 报数到第 interval 个人，淘汰
		for (int i = 1; i < interval - 1; i++) {
			head = head->next;
		}
		
		Node *temp = head->next;
		printf("淘汰的人：%d\n", temp->data);
		
		// 从链表中删除被淘汰的结点
		head->next = temp->next;
		free(temp);
		
		// 更新链表末尾
		while (current->next != head) {
			current = current->next;
		}
	}
	
	// 输出最后剩下的人
	printf("最后剩下的人：%d\n", head->data);
	
	// 释放链表内存
	free(head);
}

int main() {
	int totalPeople, interval;
	
	// 输入总人数和报数间隔
	printf("请输入总人数和报数间隔（空格分隔）：");
	scanf("%d %d", &totalPeople, &interval);
	
	// 解决约瑟夫环问题
	josephus(totalPeople, interval);
	
	return 0;
}

