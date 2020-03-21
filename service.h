#pragma once

#include "entities/medicine_list.h"

/* Deletes from a given medicine list a medicine with a given id.
 * Preconditions:
 *  medicine_list - MedicineList*, a pointer to a medicine list,
 *  				must be a valid pointer
 *  target_id - int, the id of the medicine to be deleted
 * Postconditions: If there is a medicine in 'medicine_list' with
 * id equal to 'target_id', it is deleted and 0 is returned. If
 * no medicine with the given id is found, the list is unaffected
 * and the value 1 is returned.
 */
int DeleteMedicineService(MedicineList* medicine_list,
	int target_id);

/* Adds to a given medicine list a medicine created from given
 * properties.
 * Preconditions:
 *  medicine_list - MedicineList*, a pointer to a medicine list,
 *  				must be a valid pointer
 *  id - int, the id of the medicine to be added
 *  name - char*, a pointer of the name of the medicine to be added
 *  concentration - int, the concentration of the medicine to be
 *  				added
 *  quantity - int, the quantity of the medicine to be added
 * Postconditions: If the medicine created using the given
 * properties is invalid, it is not added to the list and the
 * return value has the same meaning as the return value of
 * ValidateMedicine. If the medicine is valid the return value is
 * 0. If another medicine in 'medicine_list' has the id equal to
 * 'id', its quantity is increased by 'quantity'. If no such
 * medicine is found, the newly created medicine is added to
 * 'medicine_list'.
 */
int AddMedicineService(MedicineList* medicine_list, int id,
	char* name, int concentration, int quantity);

/* Modifies the name and concentration of a medicine with a given
 * id, in a given medicine list.
 * Preconditions:
 *  medicine_list - MedicineList*, a pointer to a medicine list,
 *  				must be a valid pointer
 *  id - int, the id of the medicine to be modified
 *  new_name - char*, a pointer to the name to be assigned to the
 *  		   medicine
 *  new_concentration - int, the concentration to be assigned to
 *  					the medicine
 * Postconditions: If no medicine with id equal to 'id' is found
 * in 'medicine_list', the value 1 is returned. If 'new_name' and
 * 'new_concentration' are invalid, the changes are not applied
 * and the returned value has the same meaning as ValidateMedicine.
 * If the new values are valid, they are assigned to the matching
 * medicine.
 */
int ModifyMedicineService(MedicineList* medicine_list, int id,
	char* new_name, int new_concentration);

/* Sorts a given medicine list using a specified method.
 * Preconditions:
 *  medicine_list - MedicineList*, a medicine list
 *  method - char, 0 for sorting by name and 1 for sorting by
 *  		 quantity
 *  reverse - char, 0 for normal order, 1 for reversed order.
 * Postconditions: 'medicine_list' is sorted using the method
 * specified by 'method' and 'reverse'.
 */
void SortMedicineListService(MedicineList* medicine_list,
	char field, char reverse);
