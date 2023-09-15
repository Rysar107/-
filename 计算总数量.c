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

int calculateTotalQuantity(ShoppingItem* list) {
	int totalQuantity = 0;
	ShoppingItem* current = list;
	while (current != NULL) {
		totalQuantity += current->quantity;
		current = current->next;
	}
	return totalQuantity;
}

int main() {
	ShoppingItem* shoppingList = NULL; 
	addItem(&shoppingList, "苹果", 5.0, 3);
	addItem(&shoppingList, "香蕉", 3.0, 2);
	addItem(&shoppingList, "西瓜", 10.0, 1);
	printf("初始购物清单:\n");
	printList(shoppingList);
	int totalQuantity = calculateTotalQuantity(shoppingList);
	printf("商品总数量: %d\n", totalQuantity);

	return 0;
}
