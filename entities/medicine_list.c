#include "medicine_list.h"

#include "medicine.h"

#include <stdlib.h>

#define INITIAL_LIST_CAPACITY 1

MedicineList CreateMedicineList(){
	MedicineList medicine_list;

	medicine_list.list = (Medicine*)malloc(sizeof(Medicine) *
		INITIAL_LIST_CAPACITY);
	medicine_list.capacity = INITIAL_LIST_CAPACITY;
	medicine_list.current_size = 0;

	return medicine_list;
}

void DestroyMedicineList(MedicineList* medicine_list){
	for(int i = 0; i < medicine_list->current_size; i++){
		DestroyMedicine(&(medicine_list->list[i]));
	}

	free(medicine_list->list);
}

int GetMedicineListLength(MedicineList medicine_list){
	return medicine_list.current_size;
}

void ExpandList(MedicineList* medicine_list){
	Medicine* new_array;
	int old_capacity = medicine_list->capacity,
		new_capacity = old_capacity * 2;

	new_array = (Medicine*)malloc(sizeof(Medicine) * new_capacity);
	for(int i = 0; i < medicine_list->current_size; i++){
		new_array[i] = medicine_list->list[i];
	}

	free(medicine_list->list);
	medicine_list->list = new_array;
	medicine_list->capacity = new_capacity;
}

int SearchInList(MedicineList medicine_list, Medicine key_medicine){
	for(int i = 0; i < medicine_list.current_size; i++){
		if(MedicineEqual(key_medicine, medicine_list.list[i]) == 1){
			return i;
		}
	}

	return -1;
}

void AddToList(MedicineList* medicine_list, Medicine new_medicine){
	int position = SearchInList(*medicine_list, new_medicine);

	if(position != -1){
		SetMedicineQuantity(&(medicine_list->list[position]),
			GetMedicineQuantity(medicine_list->list[position]) +
			new_medicine.quantity);
		free(new_medicine.name);
	} else {
		int current_list_size = medicine_list->current_size;

		if(current_list_size == medicine_list->capacity){
			ExpandList(medicine_list);
		}

		medicine_list->list[current_list_size] = new_medicine;
		medicine_list->current_size++;
	}
}

void RemoveFromList(MedicineList* medicine_list, int position){
	DestroyMedicine(&(medicine_list->list[position]));

	for(int i = position; i < medicine_list->current_size - 1;
		i++){
		medicine_list->list[i] = medicine_list->list[i + 1];
	}

	medicine_list->current_size--;
}
