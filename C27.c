#include <stdio.h>
#include <stdlib.h>

// 节点结构
typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

// 寻找最近公共祖先的二叉链存储算法
TreeNode* findLowestCommonAncestorTree(TreeNode* root, int i, int j) {
	if (root == NULL) {
		return NULL;
	}
	
	// 若找到其中一个节点，直接返回该节点
	if (root->data == i || root->data == j) {
		return root;
	}
	
	// 在左子树中查找
	TreeNode* leftLCA = findLowestCommonAncestorTree(root->left, i, j);
	
	// 在右子树中查找
	TreeNode* rightLCA = findLowestCommonAncestorTree(root->right, i, j);
	
	// 如果一个节点在左子树中，另一个在右子树中，则当前节点即为最近公共祖先
	if (leftLCA != NULL && rightLCA != NULL) {
		return root;
	}
	
	// 如果两个节点都在左子树中，则继续在左子树中查找
	return (leftLCA != NULL) ? leftLCA : rightLCA;
}

// 创建二叉树节点
TreeNode* createNode(int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

// 主函数
int main() {
	// 构造二叉链存储的二叉树
	TreeNode* root = createNode(1);
	root->left = createNode(2);
	root->right = createNode(3);
	root->left->left = createNode(4);
	root->left->right = createNode(5);
	root->right->left = createNode(6);
	root->right->right = createNode(7);
	
	// 输入节点 i 和 j
	int i, j;
	printf("输入节点 i 和 j：");
	scanf("%d %d", &i, &j);
	
	// 寻找最近公共祖先
	TreeNode* lcaTree = findLowestCommonAncestorTree(root, i, j);
	
	// 输出结果
	if (lcaTree != NULL) {
		printf("最近公共祖先的值为：%d\n", lcaTree->data);
	} else {
		printf("未找到最近公共祖先。\n");
	}
	
	// 释放动态分配的内存
	free(root->left->left);
	free(root->left->right);
	free(root->right->left);
	free(root->right->right);
	free(root->left);
	free(root->right);
	free(root);
	
	return 0;
}

