#include <stdio.h>
#include <stdlib.h>

// 定义哈夫曼树节点结构
struct HuffmanNode {
	char data;
	float frequency;
	struct HuffmanNode *left;
	struct HuffmanNode *right;
};

// 创建哈夫曼树节点
struct HuffmanNode *createNode(char data, float frequency) {
	struct HuffmanNode *node = (struct HuffmanNode *)malloc(sizeof(struct HuffmanNode));
	node->data = data;
	node->frequency = frequency;
	node->left = node->right = NULL;
	return node;
}

// 构建哈夫曼树
struct HuffmanNode *buildHuffmanTree(char data[], float frequency[], int n) {
	// 创建初始节点数组
	struct HuffmanNode *nodes[n];
	for (int i = 0; i < n; ++i) {
		nodes[i] = createNode(data[i], frequency[i]);
	}
	
	while (n > 1) {
		// 找到最小和次小的节点
		int minIndex1 = 0, minIndex2 = 1;
		if (nodes[minIndex1]->frequency > nodes[minIndex2]->frequency) {
			int temp = minIndex1;
			minIndex1 = minIndex2;
			minIndex2 = temp;
		}
		
		for (int i = 2; i < n; ++i) {
			if (nodes[i]->frequency < nodes[minIndex1]->frequency) {
				minIndex2 = minIndex1;
				minIndex1 = i;
			} else if (nodes[i]->frequency < nodes[minIndex2]->frequency) {
				minIndex2 = i;
			}
		}
		
		// 创建新节点，合并最小和次小节点
		struct HuffmanNode *newNode = createNode('$', nodes[minIndex1]->frequency + nodes[minIndex2]->frequency);
		newNode->left = nodes[minIndex1];
		newNode->right = nodes[minIndex2];
		
		// 从数组中删除合并的节点，将新节点添加到数组中
		nodes[minIndex1] = newNode;
		for (int i = minIndex2; i < n - 1; ++i) {
			nodes[i] = nodes[i + 1];
		}
		
		// 更新节点数
		n--;
	}
	
	// 返回根节点
	return nodes[0];
}

// 打印哈夫曼编码
void printHuffmanCodes(struct HuffmanNode *root, int arr[], int top) {
	if (root->left) {
		arr[top] = 0;
		printHuffmanCodes(root->left, arr, top + 1);
	}
	
	if (root->right) {
		arr[top] = 1;
		printHuffmanCodes(root->right, arr, top + 1);
	}
	
	if (!(root->left) && !(root->right)) {
		printf("%c: ", root->data);
		for (int i = 0; i < top; ++i) {
			printf("%d", arr[i]);
		}
		printf("\n");
	}
}

int main() {
	char data[] = {'A', 'B', 'C', 'D', 'E'};
	float frequency[5];
	
	printf("Enter the frequencies for characters A, B, C, D, E:\n");
	
	// 从键盘输入频率
	for (int i = 0; i < 5; ++i) {
		printf("Frequency for %c: ", data[i]);
		scanf("%f", &frequency[i]);
	}
	
	int n = sizeof(data) / sizeof(data[0]);
	
	struct HuffmanNode *root = buildHuffmanTree(data, frequency, n);
	
	int arr[100], top = 0;
	printf("\nHuffman Codes:\n");
	printHuffmanCodes(root, arr, top);
	
	return 0;
}

