#include <stdio.h>
#include <limits.h>

// 返回两个数中的较小值
int min(int a, int b) {
	return (a < b) ? a : b;
}

// 返回两个数中的较大值
int max(int a, int b) {
	return (a > b) ? a : b;
}

// 找到两个等长升序序列的中位数
double findMedianSortedArrays(int A[], int B[], int n) {
	// 确保 A 是更短的序列
	if (n > 0 && A[n - 1] > B[n - 1]) {
		int* temp = A;
		A = B;
		B = temp;
	}
	
	int m = n;
	
	while (1) {
		int i = (m + 1) / 2;
		int j = (n + m + 1) / 2 - i;
		
		int ALeftMax = (i > 0) ? A[i - 1] : INT_MIN;
		int ARightMin = (i < m) ? A[i] : INT_MAX;
		
		int BLeftMax = (j > 0) ? B[j - 1] : INT_MIN;
		int BRightMin = (j < n) ? B[j] : INT_MAX;
		
		if (ALeftMax <= BRightMin && BLeftMax <= ARightMin) {
			// 如果找到了合适的分割点，计算中位数
			if ((m + n) % 2 == 0) {
				return (max(ALeftMax, BLeftMax) + min(ARightMin, BRightMin)) / 2.0;
			} else {
				return max(ALeftMax, BLeftMax);
			}
		} else if (ALeftMax > BRightMin) {
			// 缩小搜索范围，使得 i 减小
			m = i - 1;
		} else {
			// 缩小搜索范围，使得 i 增大
			m = i + 1;
		}
	}
}

int main() {
	// 通过键盘输入测试用例
	int n;
	printf("请输入序列长度（假设两个序列等长）：");
	scanf("%d", &n);
	
	int A[n], B[n];
	printf("请输入升序序列 A 的元素：");
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	
	printf("请输入升序序列 B 的元素：");
	for (int i = 0; i < n; i++) {
		scanf("%d", &B[i]);
	}
	
	// 计算并输出中位数
	double median = findMedianSortedArrays(A, B, n);
	printf("两个升序序列的中位数为：%.1f\n", median);
	
	return 0;
}

