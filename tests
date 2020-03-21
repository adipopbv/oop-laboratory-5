#include "tests.h"

#include "service.h"
#include "entities/medicine.h"
#include "entities/medicine_list.h"
#include "entities/medicine_list_iterator.h"

#include <string.h>
#include <assert.h>

void TestAddMedicineService(){
	MedicineList medicine_list = CreateMedicineList();
	int id = 1,
		concentration = 2,
		quantity = 3,
		second_quantity = 2;
	char name[] = "asd";

	assert(AddMedicineService(&medicine_list, -1, "", -1, -1) == 15);

	assert(AddMedicineService(&medicine_list, id, name,
		concentration, quantity) == 0);

	assert(GetMedicineListLength(medicine_list) == 1);

	MedicineListIterator iterator =
		CreateMedicineListIterator(&medicine_list);

	Medicine medicine = GetElement(iterator);

	assert(GetMedicineId(medicine) == id);
	assert(strcmp(GetMedicineName(medicine), name) == 0);
	assert(GetMedicineConcentration(medicine) == concentration);
	assert(GetMedicineQuantity(medicine) == quantity);

	AddMedicineService(&medicine_list, 2, "dsa", 2, 4);
	AddMedicineService(&medicine_list, 3, "qwe", 3, 4);

	assert(GetMedicineListLength(medicine_list) == 3);

	AddMedicineService(&medicine_list, 1, "asd", 2, second_quantity);

	assert(GetMedicineListLength(medicine_list) == 3);

	medicine = GetElement(iterator);
	assert(GetMedicineQuantity(medicine) == quantity +
		second_quantity);

	DestroyMedicineList(&medicine_list);
}

void TestDeleteMedicineService(){
	MedicineList medicine_list = CreateMedicineList();
	int first_id = 1,
		first_concentration = 2,
		first_quantity = 3,
		second_id = 2,
		second_concentration = 3,
		second_quantity = 2;
	char first_name[] = "asd",
		 second_name[] = "dsaasd";

	AddMedicineService(&medicine_list, first_id, first_name,
		first_concentration, first_quantity);
	AddMedicineService(&medicine_list, second_id, second_name,
		second_concentration, second_quantity);

	assert(GetMedicineListLength(medicine_list) == 2);

	assert(DeleteMedicineService(&medicine_list, first_id + 3)
		== 1);
	assert(GetMedicineListLength(medicine_list) == 2);

	assert(DeleteMedicineService(&medicine_list, first_id)
		== 0);
	assert(GetMedicineListLength(medicine_list) == 1);

	assert(DeleteMedicineService(&medicine_list, second_id)
		== 0);
	assert(GetMedicineListLength(medicine_list) == 0);

	DestroyMedicineList(&medicine_list);
}

void TestModifyMedicineService(){
	MedicineList medicine_list = CreateMedicineList();
	int id = 1,
		first_concentration = 2,
		quantity = 4,
		second_concentration = 5;
	char first_name[] = "asd",
		 second_name[] = "dsaqwe";

	AddMedicineService(&medicine_list, id, first_name,
		first_concentration, quantity);

	assert(ModifyMedicineService(&medicine_list, id + 3, second_name,
		second_concentration) == 1);
	assert(ModifyMedicineService(&medicine_list, id, "", -1) == 6);

	MedicineListIterator iterator =
		CreateMedicineListIterator(&medicine_list);
	Medicine medicine = GetElement(iterator);

	assert(strcmp(GetMedicineName(medicine), first_name) == 0);
	assert(GetMedicineConcentration(medicine) ==
		first_concentration);

	assert(ModifyMedicineService(&medicine_list, id, second_name,
		second_concentration) == 0);

	medicine = GetElement(iterator);

	assert(strcmp(GetMedicineName(medicine), second_name) == 0);
	assert(GetMedicineConcentration(medicine) ==
		second_concentration);

	DestroyMedicineList(&medicine_list);
}

void TestSortMedicineListService(){
	MedicineList medicine_list = CreateMedicineList();
	int medicine_number = 3,
		id[] = {1, 2, 3},
		concentration[] = {2, 4, 3},
		quantity[] = {3, 1, 3};
	char name[3][10];
	strcpy(name[0], "asd");
	strcpy(name[1], "dwasq");
	strcpy(name[2], "easc");

	for(int i = 0; i < medicine_number; i++){
		AddMedicineService(&medicine_list, id[i], name[i],
			concentration[i], quantity[i]);
	}

	MedicineListIterator first_iterator =
		CreateMedicineListIterator(&medicine_list),
		second_iterator =
		CreateMedicineListIterator(&medicine_list);

	//Quantity, not reversed
	SortMedicineListService(&medicine_list, 1, 0);

	ResetIterator(&first_iterator);
	ResetIterator(&second_iterator);
	NextIterator(&second_iterator);

	while(IteratorIsValid(second_iterator)){
		assert(GetElement(first_iterator).quantity
			<= GetElement(second_iterator).quantity);

		NextIterator(&first_iterator);
		NextIterator(&second_iterator);
	}

	//Quantity, reversed
	SortMedicineListService(&medicine_list, 1, 1);

	ResetIterator(&first_iterator);
	ResetIterator(&second_iterator);
	NextIterator(&second_iterator);

	while(IteratorIsValid(second_iterator)){
		assert(GetElement(first_iterator).quantity
			>= GetElement(second_iterator).quantity);

		NextIterator(&first_iterator);
		NextIterator(&second_iterator);
	}

	//Name, not reversed
	SortMedicineListService(&medicine_list, 0, 0);

	ResetIterator(&first_iterator);
	ResetIterator(&second_iterator);
	NextIterator(&second_iterator);

	while(IteratorIsValid(second_iterator)){
		assert(strcmp(GetElement(first_iterator).name,
			GetElement(second_iterator).name) <= 0);

		NextIterator(&first_iterator);
		NextIterator(&second_iterator);
	}

	//Name, reversed
	SortMedicineListService(&medicine_list, 0, 1);

	ResetIterator(&first_iterator);
	ResetIterator(&second_iterator);
	NextIterator(&second_iterator);

	while(IteratorIsValid(second_iterator)){
		assert(strcmp(GetElement(first_iterator).name,
			GetElement(second_iterator).name) >= 0);

		NextIterator(&first_iterator);
		NextIterator(&second_iterator);
	}

	DestroyMedicineList(&medicine_list);
}

void TestMedicineListIterator(){
	MedicineList medicine_list = CreateMedicineList();
	int first_id = 1,
		first_concentration = 2,
		first_quantity = 3,
		second_id = 2,
		second_concentration = 3,
		second_quantity = 2;
	char first_name[] = "asd",
		 second_name[] = "dsaasd";

	AddMedicineService(&medicine_list, first_id, first_name,
		first_concentration, first_quantity);
	AddMedicineService(&medicine_list, second_id, second_name,
		second_concentration, second_quantity);

	MedicineListIterator iterator = CreateMedicineListIterator(
		&medicine_list);

	assert(GetMedicineId(GetElement(iterator)) == 1);
	assert(NextIterator(&iterator) == 0);
	assert(GetMedicineId(GetElement(iterator)) == 2);
	assert(NextIterator(&iterator) == 0);
	assert(IteratorIsValid(iterator) == 0);
	assert(NextIterator(&iterator) == 1);

	DestroyMedicineList(&medicine_list);
}

void TestAll(){
	TestAddMedicineService();
	TestDeleteMedicineService();
	TestModifyMedicineService();
	TestSortMedicineListService();
	TestMedicineListIterator();
}
