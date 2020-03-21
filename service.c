#include "service.h"

#include "entities/medicine.h"
#include "entities/medicine_list.h"

#include <stdlib.h>
#include <string.h>

int DeleteMedicineService(MedicineList* medicine_list,
	int target_id){
	Medicine key_medicine = CreateMedicine(target_id, "", 0, 0);
	int target_index = SearchInList(*medicine_list, key_medicine);

	DestroyMedicine(&key_medicine);

	if(target_index == -1){
		return 1;
	}

	RemoveFromList(medicine_list, target_index);

	return 0;
}

int AddMedicineService(MedicineList* medicine_list, int id,
	char* name, int concentration, int quantity){
	int validation_status = 0;
	Medicine new_medicine = CreateMedicine(id, name, concentration,
		quantity);

	validation_status = ValidateMedicine(new_medicine);
	
	if(validation_status != 0){
		DestroyMedicine(&new_medicine);
		return validation_status;
	}

	AddToList(medicine_list, new_medicine);

	return 0;
}

int ModifyMedicineService(MedicineList* medicine_list, int id,
	char* new_name, int new_concentration){
	Medicine key_medicine = CreateMedicine(id, "", 0, 0);
	int target_index = SearchInList(*medicine_list,
		key_medicine), status = 0;

	DestroyMedicine(&key_medicine);

	if(target_index == -1){
		return 1;
	}

	if(strlen(new_name) == 0){
		status |= 2;
	}
	if(new_concentration <= 0){
		status |= 4;
	}

	if(status == 0){
		SetMedicineName(&(medicine_list->list[target_index]),
			new_name);
		SetMedicineConcentration(&(medicine_list->
			list[target_index]), new_concentration);
	}

	return status;
}

int CompareName(const void* first, const void* second){
	return strcmp(GetMedicineName(*(Medicine*)first),
		GetMedicineName(*(Medicine*)second));
}

int CompareNameReverse(const void* first, const void* second){
	return CompareName(first, second)
		* -1;
}

int CompareQuantity(const void* first, const void* second){
	int first_quantity = GetMedicineQuantity(*(Medicine*)first),
		second_quantity = GetMedicineQuantity(*(Medicine*)second);

	if(first_quantity < second_quantity){
		return -1;
	} else if(first_quantity == second_quantity){
		return 0;
	} else{
		return 1;
	}
}

int CompareQuantityReverse(const void* first, const void* second){
	return CompareQuantity(first, second)
		* -1;
}

void SortMedicineListService(MedicineList* medicine_list,
	char field, char reverse){
	if(field == 0){
		if(reverse == 0){
			qsort(medicine_list->list,
				medicine_list->current_size, sizeof(Medicine),
				CompareName);
		} else{
			qsort(medicine_list->list,
				medicine_list->current_size, sizeof(Medicine),
				CompareNameReverse);
		}
	} else{
		if(reverse == 0){
			qsort(medicine_list->list,
				medicine_list->current_size, sizeof(Medicine),
				CompareQuantity);
		} else{
			qsort(medicine_list->list,
				medicine_list->current_size, sizeof(Medicine),
				CompareQuantityReverse);
		}
	}
}
