#include <stdio.h>
#include <stdlib.h>

// 希尔排序
void shellSort(int arr[], int n) {
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}

// 快速排序
void quickSort(int arr[], int low, int high) {
	if (low < high) {
		int pivotIndex = partition(arr, low, high);
		quickSort(arr, low, pivotIndex - 1);
		quickSort(arr, pivotIndex + 1, high);
	}
}

int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = low - 1;
	
	for (int j = low; j <= high - 1; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	
	swap(&arr[i + 1], &arr[high]);
	return i + 1;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// 堆排序（大根堆）
void heapifyMax(int arr[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	
	if (left < n && arr[left] > arr[largest]) {
		largest = left;
	}
	
	if (right < n && arr[right] > arr[largest]) {
		largest = right;
	}
	
	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapifyMax(arr, n, largest);
	}
}

void heapSortMax(int arr[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapifyMax(arr, n, i);
	}
	
	for (int i = n - 1; i > 0; i--) {
		swap(&arr[0], &arr[i]);
		heapifyMax(arr, i, 0);
	}
}

// 堆排序（小根堆）
void heapifyMin(int arr[], int n, int i) {
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	
	if (left < n && arr[left] < arr[smallest]) {
		smallest = left;
	}
	
	if (right < n && arr[right] < arr[smallest]) {
		smallest = right;
	}
	
	if (smallest != i) {
		swap(&arr[i], &arr[smallest]);
		heapifyMin(arr, n, smallest);
	}
}

void heapSortMin(int arr[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapifyMin(arr, n, i);
	}
	
	for (int i = n - 1; i > 0; i--) {
		swap(&arr[0], &arr[i]);
		heapifyMin(arr, i, 0);
	}
}

// 归并排序
void merge(int arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	
	int L[n1], R[n2];
	
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	
	i = 0;
	j = 0;
	k = l;
	
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;
		
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		
		merge(arr, l, m, r);
	}
}

// 计数排序
void countSort(int arr[], int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	
	int count[max + 1];
	int output[n];
	
	for (int i = 0; i <= max; i++) {
		count[i] = 0;
	}
	
	for (int i = 0; i < n; i++) {
		count[arr[i]]++;
	}
	
	for (int i = 1; i <= max; i++) {
		count[i] += count[i - 1];
	}
	
	for (int i = n - 1; i >= 0; i--) {
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}
	
	for (int i = 0; i < n; i++) {
		arr[i] = output[i];
	}
}

// 打印数组
void printArray(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

// 测试数据
int main() {
	int arr[] = {6, 12, 458, 5, 4, 28, 19, 1230, 9, 47};
	int n = sizeof(arr) / sizeof(arr[0]);
	
	printf("原始序列: ");
	printArray(arr, n);
	
	// 希尔排序
	shellSort(arr, n);
	printf("希尔排序后序列: ");
	printArray(arr, n);
	
	// 快速排序
	quickSort(arr, 0, n - 1);
	printf("快速排序后序列: ");
	printArray(arr, n);
	
	// 大根堆排序
	heapSortMax(arr, n);
	printf("堆排序（大根堆）后序列: ");
	printArray(arr, n);
	
	// 小根堆排序
	heapSortMin(arr, n);
	printf("堆排序（小根堆）后序列: ");
	printArray(arr, n);
	
	// 归并排序
	mergeSort(arr, 0, n - 1);
	printf("归并排序后序列: ");
	printArray(arr, n);
	
	// 计数排序
	countSort(arr, n);
	printf("计数排序后序列: ");
	printArray(arr, n);
	
	return 0;
}

