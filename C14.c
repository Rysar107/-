#include <stdio.h>

int is_wiggle_sequence(int nums[], int n, int *deletions) {
	if (n < 2) {
		*deletions = 0; // 不需要删除元素
		return 1; // 是摆动序列
	}
	
	// 记录摆动方向，1表示上升，-1表示下降
	int direction = 0;
	// 记录需要删除的元素数量
	*deletions = 0;
	
	for (int i = 1; i < n; i++) {
		int diff = nums[i] - nums[i - 1];
		if (diff == 0) {
			(*deletions)++; // 相邻元素相等，需要删除一个元素
		} else if (direction == 0) {
			direction = (diff > 0) ? 1 : -1;
		} else if ((direction > 0 && diff < 0) || (direction < 0 && diff > 0)) {
			(*deletions)++; // 摆动方向改变，需要删除一个元素
		}
	}
	
	return *deletions; // 返回需要删除的元素数量
}

int main() {
	int nums[100]; // 假设最多输入100个数字
	int n;
	
	printf("请输入数字序列的长度：");
	scanf("%d", &n);
	
	printf("请输入数字序列：");
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	
	int deletions = 0;
	int result = is_wiggle_sequence(nums, n, &deletions);
	
	printf("输入的数字序列，");
	if (deletions == 0) {
		printf("是摆动序列\n");
	} else {
		printf("不是摆动序列，需要删除 %d 个元素\n", deletions);
	}
	
	return 0;
}

