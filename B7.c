#include <stdio.h>

// 函数声明
int minStepsToSort(int arr[], int n);

int main() {
	// 读取输入N
	int N;
	scanf("%d", &N);
	
	// 读取排列
	int arr[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	
	// 调用函数计算最少变换步数
	int result = minStepsToSort(arr, N);
	
	// 输出结果
	printf("%d\n", result);
	
	return 0;
}

// 计算最少变换步数的函数
int minStepsToSort(int arr[], int n) {
	int steps = 0;
	
	for (int i = 0; i < n; i++) {
		if (arr[i] != i + 1) {
			// 找到当前位置不是正确数的位置
			// 交换当前位置和正确位置的数
			int temp = arr[i];
			arr[i] = arr[temp - 1];
			arr[temp - 1] = temp;
			
			steps++; // 步数加一
			i--; // 重新检查当前位置
		}
	}
	
	return steps;
}

