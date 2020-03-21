#include "service.h"

#include "entities/medicine.h"
#include "entities/universal_list.h"

#include <stdlib.h>
#include <string.h>

int DeleteMedicineService(List* medicine_list, int target_id){
	Medicine* medicine = CreateMedicine(target_id, "", 0, 0);
	int target_index = SearchInList(medicine_list, medicine, MedicineEqual);
	DestroyMedicine(medicine);

	if(target_index == -1)
		return 1;
	RemoveFromList(medicine_list, target_index, DestroyMedicine);
	return 0;
}

int AddMedicineService(List* medicine_list, int id, char* name, int concentration, int quantity){
	Medicine* new_medicine = CreateMedicine(id, name, concentration, quantity);

	int validation_status = 0;
	validation_status = ValidateMedicine(new_medicine);
	
	if(validation_status != 0){
		DestroyMedicine(new_medicine);
		return validation_status;
	}

	int position = SearchInList(medicine_list, new_medicine, MedicineEqual);
	if(position != -1){
		SetMedicineQuantity(medicine_list->list[position], 
			GetMedicineQuantity(medicine_list->list[position]) + new_medicine->quantity);
		DestroyMedicine(new_medicine);
	} else 
		AddToList(medicine_list, new_medicine);
	return 0;
}

int ModifyMedicineService(List* medicine_list, int id, char* new_name, int new_concentration){
	Medicine* medicine = CreateMedicine(id, "", 0, 0);
	int target_index = SearchInList(medicine_list, medicine, MedicineEqual), status = 0;
	DestroyMedicine(medicine);

	if(target_index == -1)
		return 1;

	//validation
	if(strlen(new_name) == 0)
		status |= 2;
	if(new_concentration <= 0)
		status |= 4;

	if(status == 0){
		SetMedicineName(medicine_list->list[target_index], new_name);
		SetMedicineConcentration(medicine_list->list[target_index], new_concentration);
	}
	return status;
}

int CompareName(const void* first, const void* second){
	return strcmp(GetMedicineName((Medicine*)first), GetMedicineName((Medicine*)second));
}

int CompareNameReverse(const void* first, const void* second){
	return CompareName(first, second) * -1;
}

int CompareQuantity(const void* first, const void* second){
	int first_quantity = GetMedicineQuantity((Medicine*)first),
		second_quantity = GetMedicineQuantity((Medicine*)second);

	if(first_quantity < second_quantity)
		return -1;
	else if(first_quantity == second_quantity)
		return 0;
	else
		return 1;
}

int CompareQuantityReverse(const void* first, const void* second){
	return CompareQuantity(first, second) * -1;
}

void SortListService(List* medicine_list, char field, char reverse){
	if(field == 0){
		if(reverse == 0){
			SortList(medicine_list, CompareName);
			//qsort(medicine_list->list, medicine_list->current_size, sizeof(Medicine*), CompareName);
		} else{
			SortList(medicine_list, CompareNameReverse);
			//qsort(medicine_list->list, medicine_list->current_size, sizeof(Medicine*), CompareNameReverse);
		}
	} else{
		if(reverse == 0){
			SortList(medicine_list, CompareQuantity);
			//qsort(medicine_list->list, medicine_list->current_size, sizeof(Medicine*), CompareQuantity);
		} else{
			SortList(medicine_list, CompareQuantityReverse);
			//qsort(medicine_list->list, medicine_list->current_size, sizeof(Medicine*), CompareQuantityReverse);
		}
	}
}

int UndoLastOperationService(List* medicine_list, List* history)
{
	if (history->current_size <= 1)
		return 1;

	DestroyList(medicine_list);
	medicine_list = history->list[(history->current_size) - 1];
	RemoveFromList(history, (history->current_size) - 1, DestroyList);
	return 0;
}
