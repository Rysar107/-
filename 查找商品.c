#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义购物清单节点结构体
typedef struct ShoppingItem {
	char name[50];
	float price;
	int quantity;
	struct ShoppingItem* next;
} ShoppingItem;

// 创建购物清单节点
ShoppingItem* createItem(char* name, float price, int quantity) {
	ShoppingItem* item = (ShoppingItem*)malloc(sizeof(ShoppingItem));
	strcpy(item->name, name);
	item->price = price;
	item->quantity = quantity;
	item->next = NULL;
	return item;
}

// 添加购物项到清单
void addItem(ShoppingItem** list, char* name, float price, int quantity) {
	ShoppingItem* newItem = createItem(name, price, quantity);
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

ShoppingItem* findItem(ShoppingItem* list, char* name) {
	ShoppingItem* current = list;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

int main() {
	ShoppingItem* shoppingList = NULL;  
	addItem(&shoppingList, "苹果", 5.0, 3);
	addItem(&shoppingList, "香蕉", 3.0, 2);
	addItem(&shoppingList, "西瓜", 10.0, 1);
	char itemName[50];
	printf("请输入要查找的商品名称：");
	scanf("%s", itemName);
	ShoppingItem* foundItem = findItem(shoppingList, itemName);
	if (foundItem != NULL) {
		printf("找到商品：%s\n", foundItem->name);
		printf("价格: %.2f\t 数量: %d\n", foundItem->price, foundItem->quantity);
	} else {
		printf("未找到商品：%s\n", itemName);
	}
	
	return 0;
}
