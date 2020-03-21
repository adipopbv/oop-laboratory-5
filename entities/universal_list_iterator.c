#include "universal_list_iterator.h"
#include <stdlib.h>

ListIterator* CreateListIterator(List* list){
	ListIterator* iterator = (ListIterator*)malloc(sizeof(ListIterator));

	iterator->list = list;
	iterator->current_element = 0;

	return iterator;
}

void DestroyIterator(ListIterator* iterator)
{
	free(iterator);
}

int IteratorIsValid(ListIterator* iterator){
	if(iterator->current_element < iterator->list->current_size)
		return 1;
	return 0;
}

Item GetElement(ListIterator* iterator){
	return iterator->list->list[iterator->current_element];
}

int NextIterator(ListIterator* iterator){
	if(IteratorIsValid(iterator)){
		iterator->current_element++;
		return 0;
	}
	return 1;
}

void ResetIterator(ListIterator* iterator){
	iterator->current_element = 0;
}
