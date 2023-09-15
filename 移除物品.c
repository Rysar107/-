#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ShoppingItem {
	char name[50];
	float price;
	struct ShoppingItem* next;
} ShoppingItem;

ShoppingItem* createItem(char* name, float price) {
	ShoppingItem* item = (ShoppingItem*)malloc(sizeof(ShoppingItem));
	strcpy(item->name, name);
	item->price = price;
	item->next = NULL;
	return item;
}

void addItem(ShoppingItem** list, char* name, float price) {
	ShoppingItem* newItem = createItem(name, price);
	if (*list == NULL) {
		*list = newItem;
	} else {
		ShoppingItem* current = *list;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newItem;
	}
}

void removeItem(ShoppingItem** list, char* name) {
	if (*list == NULL) {
		printf("清单为空，无法移除物品。\n");
		return;
	}
	
	ShoppingItem* current = *list;
	ShoppingItem* previous = NULL;
	
	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			if (previous == NULL) {
				*list = current->next;
			} else {
				previous->next = current->next;
			}
			free(current);
			printf("已从清单中移除物品：%s\n", name);
			return;
		}
		previous = current;
		current = current->next;
	}
	
	printf("未找到物品：%s\n", name);
}

// 打印购物清单
void printList(ShoppingItem* list) {
	printf("购物清单:\n");
	ShoppingItem* current = list;
	while (current != NULL) {
		printf("商品名称: %s\t 价格: %.2f\n", current->name, current->price);
		current = current->next;
	}
	printf("\n");
}

// 主函数
int main() {
	ShoppingItem* shoppingList = NULL;  // 初始化空清单
	
	// 添加购物项到清单
	addItem(&shoppingList, "苹果", 5.0);
	addItem(&shoppingList, "香蕉", 3.0);
	addItem(&shoppingList, "西瓜", 10.0);
	
	// 打印购物清单
	printList(shoppingList);
	
	// 从清单中移除物品
	removeItem(&shoppingList, "香蕉");
	
	// 再次打印购物清单
	printList(shoppingList);
	
	return 0;
}
