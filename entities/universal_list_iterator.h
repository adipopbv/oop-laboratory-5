#pragma once

#include "universal_list.h"

typedef struct{
	List* list;
	int current_element;
} ListIterator;

/* Creates an iterator of a given list, initialized on the first
 * position of the list.
 * Preconditions:
 *  list - List*, a pointer to a list,
 *  				must be a valid pointer
 * Postconditions: An iterator of 'list' is returned,
 * initialized on the first poistion.
 */
ListIterator* CreateListIterator(List* list);

/* Destroys an iterator.
 * Preconditions:
 *  iterator - ListIterator*, pointer to the iterator to be deleted,
 *  		   must be a valid pointer
 * Postconditions: The iterator at the given pointer will be
 * free.
 */
void DestroyIterator(ListIterator* iterator);

/* Checks if a given iterator is valid.
 * Preconditions:
 * 	iterator - ListIterator, an iterator
 * Postconditions: If 'iterator' is valid, 1 is returned. 0 is
 * returned otherwise.
 */
int IteratorIsValid(ListIterator* iterator);

/* Gets the current element of a given iterator.
 * Preconditions:
 * 	iterator - ListIterator, an iterator
 * Postconditions: The current element of the iterator is
 * returned.
 */
Item GetElement(ListIterator* iterator);

/* Moves a given iterator to the next element.
 * Preconditions:
 *  iterator - ListIterator*, a pointer to a 
 *  		 list iterator, must be a valid pointer
 * Postconditions: If 'iterator' is valid, it is moved to the
 * next element in the list and the value 1 is returned.
 * If 'iterator' is not valid, it is not affected, and 0 is
 * returned.
 */
int NextIterator(ListIterator* iterator);

/* Resets a given iterator to the first position in the list.
 * Preconditions:
 *  iterator - ListIterator*, a pointer to a 
 *  		 list iterator, must be a valid pointer
 * Postconditions: 'iterator' is reset to the first position in
 * the list.
 */
void ResetIterator(ListIterator* iterator);
