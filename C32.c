#include <stdio.h>
#include <stdlib.h>

// 二叉树结点定义
typedef struct TreeNode {
	char data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

// 在中序遍历序列中找到根结点的位置
int findRootIndex(char inOrder[], int start, int end, char rootValue) {
	for (int i = start; i <= end; i++) {
		if (inOrder[i] == rootValue) {
			return i;
		}
	}
	return -1; // 未找到根结点
}

// 根据先序遍历和中序遍历序列构造二叉树
TreeNode* buildTree(char preOrder[], char inOrder[], int start, int end) {
	static int preIndex = 0; // 保持先序遍历索引在递归调用之间的状态
	
	if (start > end) {
		return NULL;
	}
	
	// 创建当前子树的根结点
	TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
	root->data = preOrder[preIndex++];
	root->left = root->right = NULL;
	
	// 在中序遍历序列中找到根结点的位置
	int rootIndex = findRootIndex(inOrder, start, end, root->data);
	
	// 递归构造左右子树
	root->left = buildTree(preOrder, inOrder, start, rootIndex - 1);
	root->right = buildTree(preOrder, inOrder, rootIndex + 1, end);
	
	return root;
}

// 后序遍历输出二叉树
void postOrderTraversal(TreeNode *root) {
	if (root == NULL) {
		return;
	}
	postOrderTraversal(root->left);
	postOrderTraversal(root->right);
	printf("%c ", root->data);
}

int main() {
	char preOrder[100], inOrder[100];
	
	// 输入先序遍历序列
	printf("请输入先序遍历序列: ");
	scanf("%s", preOrder);
	
	// 输入中序遍历序列
	printf("请输入中序遍历序列: ");
	scanf("%s", inOrder);
	
	int length = 0;
	while (preOrder[length] != '\0') {
		length++;
	}
	
	// 构造二叉树
	TreeNode *root = buildTree(preOrder, inOrder, 0, length - 1);
	
	// 输出构造的二叉树的后序遍历序列
	printf("构造的二叉树的后序遍历序列：");
	postOrderTraversal(root);
	printf("\n");
	
	return 0;
}

