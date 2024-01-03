#include <stdio.h>

void find_minimum_coins(int change, int coin_values[], int coins_count[], int num_coins) {
	for (int i = 0; i < num_coins; i++) {
		while (change >= coin_values[i]) {
			change -= coin_values[i];
			coins_count[i]++;
		}
	}
}

void print_change(int coins_count[], int coin_values[], int num_coins) {
	printf("期望输出：");
	for (int i = 0; i < num_coins; i++) {
		if (coins_count[i] > 0) {
			printf("%d 个 %d 分硬币", coins_count[i], coin_values[i]);
			if (i < num_coins - 1 && coins_count[i + 1] > 0) {
				printf("，");
			}
		}
	}
	printf("\n");
}

int main() {
	int change;
	
	printf("请输入找零金额（单位：分）：");
	scanf("%d", &change);
	
	int coin_values[] = {25, 10, 5, 1};
	int coins_count[] = {0, 0, 0, 0};
	int num_coins = sizeof(coin_values) / sizeof(coin_values[0]);
	
	find_minimum_coins(change, coin_values, coins_count, num_coins);
	printf("找零 %d 分，", change);
	print_change(coins_count, coin_values, num_coins);
	
	return 0;
}

