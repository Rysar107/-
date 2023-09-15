#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ShoppingItem {
	char name[50];
	float price;
	int quantity;
	struct ShoppingItem* next;
} ShoppingItem;

ShoppingItem* createItem(char* name, float price, int quantity) {
	ShoppingItem* item = (ShoppingItem*)malloc(sizeof(ShoppingItem));
	strcpy(item->name, name);
	item->price = price;
	item->quantity = quantity;
	item->next = NULL;
	return item;
}

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

void modifyQuantity(ShoppingItem* list, char* name, int newQuantity) {
	ShoppingItem* current = list;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0) {
			current->quantity = newQuantity;
			printf("已将 %s 的数量修改为 %d\n", name, newQuantity);
			return;
		}
		current = current->next;
	}
	printf("未找到物品：%s\n", name);
}

void printList(ShoppingItem* list) {
	if (list == NULL) {
		printf("购物清单为空。\n");
		return;
	}
	
	printf("购物清单:\n");
	ShoppingItem* current = list;
	while (current != NULL) {
		printf("商品名称: %s\t 价格: %.2f\t 数量: %d\n", current->name, current->price, current->quantity);
		current = current->next;
	}
	printf("\n");
}


int main() {
	ShoppingItem* shoppingList = NULL;  // 初始化空清单

	addItem(&shoppingList, "苹果", 5.0, 3);
	addItem(&shoppingList, "香蕉", 3.0, 2);
	addItem(&shoppingList, "西瓜", 10.0, 1);
	
	printList(shoppingList);

	modifyQuantity(shoppingList, "苹果", 4);
	

	printList(shoppingList);
	
	return 0;
}
