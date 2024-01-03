#include <stdio.h>

// 定义栈结构
#define MAX_SIZE 100
int stack[MAX_SIZE];
int top = -1;

// 将元素压入栈
void push(int item) {
	if (top == MAX_SIZE - 1) {
		printf("Stack Overflow\n");
		return;
	}
	stack[++top] = item;
}

// 弹出栈顶元素
int pop() {
	if (top == -1) {
		printf("Stack Underflow\n");
		return -1;
	}
	return stack[top--];
}

// 递归函数将十进制数转换为二进制
void convertToBinary(int decimal_num) {
	if (decimal_num > 0) {
		int remainder = decimal_num % 2;
		push(remainder);
		convertToBinary(decimal_num / 2);
	}
}

// 将栈中的元素输出为二进制
void printBinary() {
	printf("二进制: ");
	while (top != -1) {
		printf("%d", pop());
	}
	printf("\n");
}

// 递归函数将十进制数转换为八进制
void convertToOctal(int decimal_num) {
	if (decimal_num > 0) {
		int remainder = decimal_num % 8;
		push(remainder);
		convertToOctal(decimal_num / 8);
	}
}

// 将栈中的元素输出为八进制
void printOctal() {
	printf("八进制: ");
	while (top != -1) {
		printf("%d", pop());
	}
	printf("\n");
}

// 递归函数将十进制数转换为十六进制
void convertToHex(int decimal_num) {
	if (decimal_num > 0) {
		int remainder = decimal_num % 16;
		if (remainder < 10) {
			push(remainder + '0');
		} else {
			push(remainder - 10 + 'A');
		}
		convertToHex(decimal_num / 16);
	}
}

// 将栈中的元素输出为十六进制
void printHex() {
	printf("十六进制: ");
	while (top != -1) {
		printf("%c", pop());
	}
	printf("\n");
}

int main() {
	int decimal_num;
	
	// 输入十进制数
	printf("输入十进制数: ");
	scanf("%d", &decimal_num);
	
	// 转换为二进制
	convertToBinary(decimal_num);
	printBinary();
	
	// 重置栈
	top = -1;
	
	// 转换为八进制
	convertToOctal(decimal_num);
	printOctal();
	
	// 重置栈
	top = -1;
	
	// 转换为十六进制
	convertToHex(decimal_num);
	printHex();
	
	return 0;
}

