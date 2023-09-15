void sortList(ShoppingItem** list) {
	ShoppingItem* current = *list;
	ShoppingItem* temp;
	int swapped;
	
	if (current == NULL) {
		printf("购物清单为空，无需排序。\n");
		return;
	}
	
	do {
		swapped = 0;
		current = *list;
		
		while (current->next != NULL) {
			if (strcmp(current->name, current->next->name) > 0) {
				temp = current->next;
				current->next = temp->next;
				temp->next = current;
				*list = temp;
				swapped = 1;
			}
			current = current->next;
		}
	} while (swapped);
}
