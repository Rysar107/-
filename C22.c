#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
	char data[MAX_SIZE];
	int top;
} Stack;

void initStack(Stack *stack) {
	stack->top = -1;
}

bool isEmpty(Stack *stack) {
	return stack->top == -1;
}

bool isFull(Stack *stack) {
	return stack->top == MAX_SIZE - 1;
}

void push(Stack *stack, char value) {
	if (isFull(stack)) {
		printf("栈已满，无法入栈\n");
		return;
	}
	stack->data[++stack->top] = value;
}

char pop(Stack *stack) {
	if (isEmpty(stack)) {
		printf("栈为空，无法出栈\n");
		return '\0';
	}
	return stack->data[stack->top--];
}

bool isValidPopSequence(char *inputSequence, char *expectedPopSequence) {
	Stack stack;
	initStack(&stack);
	
	int inputIndex = 0;
	int expectedIndex = 0;
	
	while (expectedPopSequence[expectedIndex] != '\0') {
		while (!isEmpty(&stack) && stack.data[stack.top] == expectedPopSequence[expectedIndex]) {
			pop(&stack);
			expectedIndex++;
		}
		
		if (inputSequence[inputIndex] != '\0') {
			push(&stack, inputSequence[inputIndex]);
			inputIndex++;
		}
	}
	
	return isEmpty(&stack);
}

int main() {
	char inputSequence[MAX_SIZE];
	char expectedPopSequence[MAX_SIZE];
	
	printf("请输入待测试的序列（以Enter结束）：\n");
	fgets(inputSequence, MAX_SIZE, stdin);
	
	printf("请输入期望的出栈序列（以Enter结束）：\n");
	fgets(expectedPopSequence, MAX_SIZE, stdin);
	
	// 移除输入序列和期望出栈序列中的换行符
	inputSequence[strcspn(inputSequence, "\n")] = '\0';
	expectedPopSequence[strcspn(expectedPopSequence, "\n")] = '\0';
	
	if (isValidPopSequence(inputSequence, expectedPopSequence)) {
		printf("序列 \"%s\" 是合法的出栈序列。\n", inputSequence);
	} else {
		printf("序列 \"%s\" 不是合法的出栈序列。\n", inputSequence);
	}
	
	return 0;
}

