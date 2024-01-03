#include <stdio.h>
#include <stdlib.h>

// 定义双向循环链表结点
typedef struct Node {
	int data;
	struct Node *prev;
	struct Node *next;
} Node;

// 定义双向循环链表
typedef struct {
	Node *head;
} DoublyCircularLinkedList;

// 初始化双向循环链表
DoublyCircularLinkedList initList() {
	DoublyCircularLinkedList list;
	list.head = (Node *)malloc(sizeof(Node));
	list.head->prev = list.head;
	list.head->next = list.head;
	return list;
}

// 在链表尾部插入元素
void insertEnd(DoublyCircularLinkedList *list, int data) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = list->head;
	newNode->prev = list->head->prev;
	
	list->head->prev->next = newNode;
	list->head->prev = newNode;
}

// 求两个集合的交集
DoublyCircularLinkedList intersection(DoublyCircularLinkedList A, DoublyCircularLinkedList B) {
	DoublyCircularLinkedList result = initList();
	
	Node *nodeA = A.head->next;
	
	while (nodeA != A.head) {
		Node *nodeB = B.head->next;
		while (nodeB != B.head) {
			if (nodeA->data == nodeB->data) {
				insertEnd(&result, nodeA->data);
				break;
			}
			nodeB = nodeB->next;
		}
		nodeA = nodeA->next;
	}
	
	return result;
}

// 求两个集合的并集
DoublyCircularLinkedList unionSet(DoublyCircularLinkedList A, DoublyCircularLinkedList B) {
	DoublyCircularLinkedList result = initList();
	
	Node *nodeA = A.head->next;
	Node *nodeB = B.head->next;
	
	while (nodeA != A.head || nodeB != B.head) {
		if ((nodeB == B.head) || (nodeA != A.head && nodeA->data < nodeB->data)) {
			insertEnd(&result, nodeA->data);
			nodeA = nodeA->next;
		} else if ((nodeA == A.head) || (nodeB != B.head && nodeA->data > nodeB->data)) {
			insertEnd(&result, nodeB->data);
			nodeB = nodeB->next;
		} else {
			insertEnd(&result, nodeA->data);
			nodeA = nodeA->next;
			nodeB = nodeB->next;
		}
	}
	
	return result;
}

// 打印链表元素
void printList(DoublyCircularLinkedList list) {
	Node *current = list.head->next;
	while (current != list.head) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

// 释放链表内存
void freeList(DoublyCircularLinkedList *list) {
	Node *current = list->head->next;
	while (current != list->head) {
		Node *temp = current;
		current = current->next;
		free(temp);
	}
	free(list->head);
}

int main() {
	// 创建集合 A
	DoublyCircularLinkedList A = initList();
	insertEnd(&A, 1);
	insertEnd(&A, 2);
	insertEnd(&A, 3);
	insertEnd(&A, 4);
	insertEnd(&A, 5);
	
	// 创建集合 B
	DoublyCircularLinkedList B = initList();
	insertEnd(&B, 3);
	insertEnd(&B, 4);
	insertEnd(&B, 5);
	insertEnd(&B, 6);
	insertEnd(&B, 7);
	
	// 求交集和并集
	DoublyCircularLinkedList inter = intersection(A, B);
	DoublyCircularLinkedList uni = unionSet(A, B);
	
	// 打印结果
	printf("集合 A: ");
	printList(A);
	printf("集合 B: ");
	printList(B);
	printf("交集: ");
	printList(inter);
	printf("并集: ");
	printList(uni);
	
	// 释放内存
	freeList(&A);
	freeList(&B);
	freeList(&inter);
	freeList(&uni);
	
	return 0;
}

