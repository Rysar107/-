void removeItem(ShoppingItem** list, const char* itemName) {
	if (*list == NULL) {
		printf("购物清单为空，无法删除物品。\n");
		return;
	}
	
	ShoppingItem* current = *list;
	ShoppingItem* previous = NULL;

	while (current != NULL) {
		if (strcmp(current->name, itemName) == 0) {
			if (previous == NULL) {

				*list = current->next;
			} else {
				previous->next = current->next;
			}	
			free(current);
			printf("物品 '%s' 已从购物清单中删除。\n", itemName);
			return;
		}
		
		previous = current;
		current = current->next;
	}
	
	printf("购物清单中没有找到物品 '%s'。\n", itemName);
}
