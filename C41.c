#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点
struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

// 创建新的二叉树节点
struct TreeNode* createNode(int value) {
	struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	newNode->val = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// 插入节点到二叉搜索树
struct TreeNode* insertNode(struct TreeNode* root, int value) {
	if (root == NULL) {
		return createNode(value);
	}
	
	if (value < root->val) {
		root->left = insertNode(root->left, value);
	} else {
		root->right = insertNode(root->right, value);
	}
	
	return root;
}

// 计算在给定范围内节点的总和
int rangeSumBST(struct TreeNode* root, int low, int high) {
	if (root == NULL) {
		return 0;
	}
	
	int sum = 0;
	
	// 如果当前节点的值在范围内，加入总和
	if (root->val >= low && root->val <= high) {
		sum += root->val;
	}
	
	// 如果当前节点值小于范围下限，只需考虑右子树
	if (root->val < low) {
		sum += rangeSumBST(root->right, low, high);
	}
	// 如果当前节点值大于范围上限，只需考虑左子树
	else if (root->val > high) {
		sum += rangeSumBST(root->left, low, high);
	}
	// 如果当前节点值在范围内，考虑左右子树
	else {
		sum += rangeSumBST(root->left, low, high);
		sum += rangeSumBST(root->right, low, high);
	}
	
	return sum;
}

// 释放二叉树节点
void freeTree(struct TreeNode* root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

int main() {
	// 模拟构建一棵二叉搜索树
	struct TreeNode* root = NULL;
	root = insertNode(root, 10);
	insertNode(root, 5);
	insertNode(root, 15);
	insertNode(root, 3);
	insertNode(root, 7);
	insertNode(root, 18);
	
	// 设定范围
	int low = 7;
	int high = 15;
	
	// 计算在给定范围内节点的总和
	int sum = rangeSumBST(root, low, high);
	
	// 输出计算结果
	printf("范围[%d, %d]内节点的总和为: %d\n", low, high, sum);
	
	// 释放内存
	freeTree(root);
	
	return 0;
}

