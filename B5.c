#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
typedef struct TreeNode {
	int value;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

// 定义栈结构
typedef struct StackNode {
	TreeNode* data;
	struct StackNode* next;
} StackNode;

// 初始化栈
void initStack(StackNode** stack) {
	*stack = NULL;
}

// 判断栈是否为空
int isEmpty(StackNode* stack) {
	return stack == NULL;
}

// 入栈
void push(StackNode** stack, TreeNode* data) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	newNode->data = data;
	newNode->next = *stack;
	*stack = newNode;
}

// 出栈
TreeNode* pop(StackNode** stack) {
	if (isEmpty(*stack)) {
		return NULL;
	}
	
	TreeNode* topData = (*stack)->data;
	StackNode* temp = *stack;
	*stack = (*stack)->next;
	free(temp);
	
	return topData;
}

// 先序遍历
void preOrderTraversal(TreeNode* root) {
	if (root != NULL) {
		printf("%d ", root->value);
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}
}

// 中序遍历
void inOrderTraversal(TreeNode* root) {
	if (root != NULL) {
		inOrderTraversal(root->left);
		printf("%d ", root->value);
		inOrderTraversal(root->right);
	}
}

// 后序遍历
void postOrderTraversal(TreeNode* root) {
	if (root != NULL) {
		postOrderTraversal(root->left);
		postOrderTraversal(root->right);
		printf("%d ", root->value);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	
	// 创建二叉树节点数组
	TreeNode* nodes = (TreeNode*)malloc(n * sizeof(TreeNode));
	
	// 读入节点信息并构建二叉树
	for (int i = 0; i < n; ++i) {
		int value, leftIndex, rightIndex;
		scanf("%d %d %d", &value, &leftIndex, &rightIndex);
		
		nodes[i].value = value;
		
		if (leftIndex != -1) {
			nodes[i].left = &nodes[leftIndex];
		} else {
			nodes[i].left = NULL;
		}
		
		if (rightIndex != -1) {
			nodes[i].right = &nodes[rightIndex];
		} else {
			nodes[i].right = NULL;
		}
	}
	
	// 初始化栈
	StackNode* stack;
	initStack(&stack);
	
	// 先序遍历
	printf("Preorder: ");
	push(&stack, &nodes[0]);
	while (!isEmpty(stack)) {
		TreeNode* current = pop(&stack);
		printf("%d ", current->value);
		
		if (current->right != NULL) {
			push(&stack, current->right);
		}
		
		if (current->left != NULL) {
			push(&stack, current->left);
		}
	}
	printf("\n");
	
	// 重新初始化栈
	initStack(&stack);
	
	// 中序遍历
	printf("Inorder: ");
	TreeNode* current = &nodes[0];
	while (current != NULL || !isEmpty(stack)) {
		while (current != NULL) {
			push(&stack, current);
			current = current->left;
		}
		
		current = pop(&stack);
		printf("%d ", current->value);
		
		current = current->right;
	}
	printf("\n");
	
	// 重新初始化栈
	initStack(&stack);
	
	// 后序遍历
	printf("Postorder: ");
	current = &nodes[0];
	TreeNode* lastVisited = NULL;
	while (current != NULL || !isEmpty(stack)) {
		while (current != NULL) {
			push(&stack, current);
			current = current->left;
		}
		
		current = stack->data;
		
		if (current->right == NULL || current->right == lastVisited) {
			printf("%d ", current->value);
			pop(&stack);
			lastVisited = current;
			current = NULL;
		} else {
			current = current->right;
		}
	}
	printf("\n");
	
	// 释放内存
	free(nodes);
	
	return 0;
}

