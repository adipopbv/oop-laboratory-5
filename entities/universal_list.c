#include "universal_list.h"

#include "medicine.h"

#include <stdlib.h>

#define INITIAL_LIST_CAPACITY 1

List* CreateList(){
	List* list = (List*)malloc(sizeof(List));

	list->list = (Item*)malloc(sizeof(Item) * INITIAL_LIST_CAPACITY);
	list->list[0] = NULL;
	list->capacity = INITIAL_LIST_CAPACITY;
	list->current_size = 0;

	return list;
}

void DestroyList(List* list){
//	for(int i = 0; i < list->current_size; i++){
//		DestroyMedicine(&(list->list[i]));
//	}

	free(list->list);
}

int GetListLength(List* list){
	return list->current_size;
}

void ExpandList(List* list){
	int old_capacity = list->capacity, new_capacity = old_capacity * 2;
	Item* new_array = (Item*)malloc(sizeof(Item) * new_capacity);

	for(int i = 0; i < list->current_size; i++){
		new_array[i] = list->list[i];
	}
	free(list->list);
	list->list = new_array;

	list->capacity = new_capacity;
}

int SearchInList(List* list, Item item, MatchingFunction match_items){
	for(int i = 0; i < list->current_size; i++)
		if(match_items(item, list->list[i]) == 1)
			return i;
	return -1;
}

void AddToList(List* list, Item new_item){
	if(list->current_size == list->capacity)
		ExpandList(list);
	list->list[(list->current_size)++] = new_item;
}

void RemoveFromList(List* list, int position, DestructionFunction destory_item){
	destory_item(list->list[position]);

	for(int i = position; i < list->current_size - 1; i++)
		list->list[i] = list->list[i + 1];

	list->current_size--;
}

void SortList(List* medicine_list, CompareFunction compare_items)
{
	for (int i=0; i<medicine_list->current_size-1; i++)
		for (int j=i+1; j<medicine_list->current_size; j++)
			if (compare_items(medicine_list->list[i], medicine_list->list[j]) == 1)
			{
				Medicine* aux = medicine_list->list[i];
				medicine_list->list[i] = medicine_list->list[j];
				medicine_list->list[j] = aux;
			}
}
