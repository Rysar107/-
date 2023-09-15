void clearList(ShoppingItem** list) {
	ShoppingItem* current = *list;
	while (current != NULL) {
		ShoppingItem* next = current->next;
		free(current);
		current = next;
	}
	*list = NULL;
	printf("购物清单已清空。\n");
}
