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

void printList(ShoppingItem* list) {
	printf("购物清单:\n");
	ShoppingItem* current = list;
	while (current != NULL) {
		printf("商品名称: %s\t 价格: %.2f\n", current->name, current->price);
		current = current->next;
	}
	printf("\n");
}

int main() {
	ShoppingItem* shoppingList = NULL;  
	addItem(&shoppingList, "苹果", 5.0);
	addItem(&shoppingList, "香蕉", 3.0);
	addItem(&shoppingList, "西瓜", 10.0);
	
	printList(shoppingList);
	
	return 0;
}


