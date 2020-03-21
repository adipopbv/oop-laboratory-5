#pragma once

#include "medicine.h"

typedef struct{
	Medicine* list;
	int capacity, current_size;
}MedicineList;

/* Creates a medicine list.
 * Preconditions:
 *  ---
 * Postconditions: An empty medicine list is created and returned.
 */
MedicineList CreateMedicineList();

/* Destroys a medicine list.
 * Preconditions:
 *  medicine_list - MedicineList*, a pointer to a medicine list,
 *  				must be a valid pointer
 * Postconditions: The contents of the list and the list itself are
 * freed.
 */
void DestroyMedicineList(MedicineList* medicine_list);

/* Gets the length of a list.
 * Preconditions:
 * 	medicine_list - MedicineList, a medicine list
 * Postconditions: The number of elements in 'medicine_list' is
 * returned.
 */
int GetMedicineListLength(MedicineList medicine_list);

/* Searches in a medicine list using a key medicine.
 * Preconditions:
 *  medicine_list - MedicineList, a medicine list
 *  key_medicine - Medicine, a medicine
 * Postconditions: If 'key_medicine' matches with a medicine in
 * 'medicine_list', the index of the matching medicine is
 * returned. If no match is found, the value -1 is returned
 * instead.
 */
int SearchInList(MedicineList medicine_list,
	Medicine key_medicine);

/* Adds a medicine to a medicine list.
 * Preconditions:
 *  medicine_list - MedicineList*, a pointer to a medicine list,
 *  				must be a valid pointer
 *  new_medicine - Medicine, a medicine
 * Postconditions: 'new_medicine' is added to 'medicine_list'.
 */
void AddToList(MedicineList* medicine_list,
	Medicine new_medicine);

/* Removes the medicine at a given position from a medicine list.
 * Preconditions:
 *  medicine_list - MedicineList*, a pointer to a medicine list,
 *  				must be a valid pointer
 *  position - int, the position of the medicine to be removed
 * Postconditions: If a medicine exists in 'medicine_list' at
 * position 'position', it is removed. Nothing happens, otherwise.
 */
void RemoveFromList(MedicineList* medicine_list, int position);
