#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "medicine.h"

Medicine CreateMedicine(int id, char* name, int concentration,
	int quantity){
	Medicine medicine;

	medicine.id = id;
	medicine.concentration = concentration;
	medicine.quantity = quantity;

	int name_length = strlen(name);
	medicine.name = (char*)malloc(sizeof(char) *
		(name_length + 1));
	strcpy(medicine.name, name);

	return medicine;
}

void DestroyMedicine(Medicine* medicine){
	free(medicine->name);
}

int MedicineEqual(Medicine first, Medicine second){
	if(first.id == second.id){
		return 1;
	}

	return 0;
}

void SetMedicineName(Medicine* medicine, char* new_name){
	int new_name_length = strlen(new_name);

	free(medicine->name);
	medicine->name = (char*)malloc(sizeof(char) *
		(new_name_length + 1));
	strcpy(medicine->name, new_name);
}

void SetMedicineConcentration(Medicine* medicine,
	int new_concentration){
	medicine->concentration = new_concentration;
}

void SetMedicineQuantity(Medicine* medicine, int new_quantity){
	medicine->quantity = new_quantity;
}

int GetMedicineId(Medicine medicine){
	return medicine.id;
}

int GetMedicineConcentration(Medicine medicine){
	return medicine.concentration;
}

char* GetMedicineName(Medicine medicine){
	return medicine.name;
}

int GetMedicineQuantity(Medicine medicine){
	return medicine.quantity;
}

int ValidateMedicine(Medicine medicine){
	int error_code = 0;

	if(medicine.id < 0){
		error_code |= 1;
	}
	if(strlen(medicine.name) == 0){
		error_code |= 2;
	}
	if(medicine.concentration <= 0){
		error_code |= 4;
	}
	if(medicine.quantity <= 0){
		error_code |= 8;
	}

	return error_code;
}
