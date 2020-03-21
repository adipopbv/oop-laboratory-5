#pragma once

#include "medicine_list.h"

typedef struct{
	MedicineList* medicine_list;
	int current_element;
} MedicineListIterator;

/* Creates an iterator of a given list, initialized on the first
 * position of the list.
 * Preconditions:
 *  medicine_list - MedicineList*, a pointer to a medicine list,
 *  				must be a valid pointer
 * Postconditions: An iterator of 'medicine_list' is returned,
 * initialized on the first poistion.
 */
MedicineListIterator CreateMedicineListIterator(MedicineList*
	medicine_list);

/* Checks if a given iterator is valid.
 * Preconditions:
 * 	iterator - MedicineListIterator, an iterator
 * Postconditions: If 'iterator' is valid, 1 is returned. 0 is
 * returned otherwise.
 */
int IteratorIsValid(MedicineListIterator iterator);

/* Gets the current element of a given iterator.
 * Preconditions:
 * 	iterator - MedicineListIterator, an iterator
 * Postconditions: The current element of the iterator is
 * returned.
 */
Medicine GetElement(MedicineListIterator iterator);

/* Moves a given iterator to the next element.
 * Preconditions:
 *  iterator - MedicineListIterator*, a pointer to a medicine
 *  		   list iterator, must be a valid pointer
 * Postconditions: If 'iterator' is valid, it is moved to the
 * next element in the list and the value 1 is returned.
 * If 'iterator' is not valid, it is not affected, and 0 is
 * returned.
 */
int NextIterator(MedicineListIterator* iterator);

/* Resets a given iterator to the first position in the list.
 * Preconditions:
 *  iterator - MedicineListIterator*, a pointer to a medicine
 *  		   list iterator, must be a valid pointer
 * Postconditions: 'iterator' is reset to the first position in
 * the list.
 */
void ResetIterator(MedicineListIterator* iterator);
