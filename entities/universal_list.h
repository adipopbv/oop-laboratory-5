#pragma once

#include "medicine.h"

typedef void* Item;

typedef int (*MatchingFunction)(Item, Item);
typedef void (*DestructionFunction)(Item);
typedef int (*CompareFunction)(Item, Item);
typedef Item* (*CloningFunction)(Item*);


typedef struct{
	Item* list;
	int capacity, current_size;
} List;

/* Creates a medicine list.
 * Preconditions:
 *  ---
 * Postconditions: An empty medicine list is created and returned.
 */
List* CreateList();

/* Destroys a list.
 * Preconditions:
 *  list - List*, a pointer to a medicine list,
 *  				must be a valid pointer
 * Postconditions: The the list itself is
 * freed.
 */
void DestroyList(List* list);

/* Destroys a list and all it's items contents.
 * Preconditions:
 *  list - List*, a pointer to a medicine list,
 *  				must be a valid pointer
 *  destroy_item - DestructionFunction, a destruction function
 * Postconditions: The contents of the list and the list itself are
 * freed.
 */
void DeepDestroyList(List* list, DestructionFunction destroy_item);

/* Deep copies the given list
 * Preconditions:
 *  list - List*, a pointer to the list to be deep cloned
 *  clone_item - CloningFunction, a function that clones fields of the list
 * Postconditions: The new list is a deep copy of the given one
 */
List* DeepCloneList(List* list, CloningFunction clone_item);

/* Gets the length of a list.
 * Preconditions:
 * 	list - List, a medicine list
 * Postconditions: The number of elements in 'list' is
 * returned.
 */
int GetListLength(List* list);

/* Searches in a medicine list using a key medicine.
 * Preconditions:
 *  list - List, a list
 *  match_medicine - MatchMedicine, a matching function
 * Postconditions: If match_medicine returns 1
 * , the index of the matching medicine is
 * returned. If no match is found, the value -1 is returned
 * instead.
 */
int SearchInList(List* list, Item item, MatchingFunction match_items);

/* Adds an item to a list.
 * Preconditions:
 *  list - List*, a pointer to a list,
 *  				must be a valid pointer
 *  new_item - Item, an item
 * Postconditions: 'new_item' is added to 'list'.
 */
void AddToList(List* list, Item new_item);

/* Removes the item at a given position from a list.
 * Preconditions:
 *  list - List*, a pointer to a list,
 *  				must be a valid pointer
 *  position - int, the position of the item to be removed
 * Postconditions: If a exists in 'list' at
 * position 'position', it is removed. Nothing happens, otherwise.
 */
void RemoveFromList(List* list, int position, DestructionFunction destroy_item);

/* Sorts list with the given compare function
 * Preconditions:
 *  list - List*, a pointer to a list
 *  compare_items - CompareFunction, a function for comparations
 * Postconditions: the list is sorted
 */
void SortList(List* list, CompareFunction compare_items);
