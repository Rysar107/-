void mergeLists(ShoppingItem** list1, ShoppingItem* list2) {
	if (list2 == NULL) {
		printf("第二个清单为空，无需合并。\n");
		return;
	}
	
	ShoppingItem* current = list2;
	while (current != NULL) {
		addItem(list1, current->name, current->price, current->quantity);
		current = current->next;
	}
	
	printf("购物清单已合并。\n");
}
