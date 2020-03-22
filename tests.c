#include "tests.h"
#include <stdio.h>

#include "service.h"
#include "entities/medicine.h"
#include "entities/universal_list.h"
#include "entities/universal_list_iterator.h"

#include <string.h>
#include <assert.h>

void TestAddMedicineService(){
	List* medicine_list = CreateList();
	List* history = CreateList();
	AddToList(history, DeepCloneList(medicine_list, (CloningFunction)CloneMedicine));

	int id = 1,
		concentration = 2,
		quantity = 3,
		second_quantity = 2;
	char name[] = "asd";

	assert(AddMedicineService(medicine_list, history, -1, "", -1, -1) == 15);

	assert(AddMedicineService(medicine_list, history, id, name,
		concentration, quantity) == 0);

	assert(GetListLength(medicine_list) == 1);

	ListIterator* iterator =
		CreateListIterator(medicine_list);

	Medicine* medicine = GetElement(iterator);

	assert(GetMedicineId(medicine) == id);
	assert(strcmp(GetMedicineName(medicine), name) == 0);
	assert(GetMedicineConcentration(medicine) == concentration);
	assert(GetMedicineQuantity(medicine) == quantity);

	AddMedicineService(medicine_list, history, 2, "dsa", 2, 4);
	AddMedicineService(medicine_list, history, 3, "qwe", 3, 4);

	assert(GetListLength(medicine_list) == 3);

	AddMedicineService(medicine_list, history, 1, "asd", 2, second_quantity);

	assert(GetListLength(medicine_list) == 3);

	medicine = GetElement(iterator);
	assert(GetMedicineQuantity(medicine) == quantity +
		second_quantity);

	DeepDestroyList(medicine_list, (DestructionFunction)DestroyMedicine);
	DestroyIterator(iterator);
}

void TestDeleteMedicineService(){
	List* medicine_list = CreateList();
	List* history = CreateList();
	AddToList(history, DeepCloneList(medicine_list, (CloningFunction)CloneMedicine));
	int first_id = 1,
		first_concentration = 2,
		first_quantity = 3,
		second_id = 2,
		second_concentration = 3,
		second_quantity = 2;
	char first_name[] = "asd",
		 second_name[] = "dsaasd";

	AddMedicineService(medicine_list, history, first_id, first_name,
		first_concentration, first_quantity);
	AddMedicineService(medicine_list, history, second_id, second_name,
		second_concentration, second_quantity);

	assert(GetListLength(medicine_list) == 2);

	assert(DeleteMedicineService(medicine_list, history, first_id + 3)
		== 1);
	assert(GetListLength(medicine_list) == 2);

	assert(DeleteMedicineService(medicine_list, history, first_id)
		== 0);
	assert(GetListLength(medicine_list) == 1);

	assert(DeleteMedicineService(medicine_list, history, second_id)
		== 0);
	assert(GetListLength(medicine_list) == 0);

	DeepDestroyList(medicine_list, (DestructionFunction)DestroyMedicine);
}

void TestModifyMedicineService(){
	List* medicine_list = CreateList();
	List* history = CreateList();
	AddToList(history, DeepCloneList(medicine_list, (CloningFunction)CloneMedicine));
	int id = 1,
		first_concentration = 2,
		quantity = 4,
		second_concentration = 5;
	char first_name[] = "asd",
		 second_name[] = "dsaqwe";

	AddMedicineService(medicine_list, history, id, first_name,
		first_concentration, quantity);

	assert(ModifyMedicineService(medicine_list, history, id + 3, second_name,
		second_concentration) == 1);
	assert(ModifyMedicineService(medicine_list, history, id, "", -1) == 6);

	ListIterator* iterator =
		CreateListIterator(medicine_list);
	Medicine* medicine = GetElement(iterator);

	assert(strcmp(GetMedicineName(medicine), first_name) == 0);
	assert(GetMedicineConcentration(medicine) ==
		first_concentration);

	assert(ModifyMedicineService(medicine_list, history, id, second_name,
		second_concentration) == 0);

	medicine = GetElement(iterator);

	assert(strcmp(GetMedicineName(medicine), second_name) == 0);
	assert(GetMedicineConcentration(medicine) ==
		second_concentration);

	DeepDestroyList(medicine_list, (DestructionFunction)DestroyMedicine);
	DestroyIterator(iterator);
}

void TestSortMedicineListService(){
	List* medicine_list = CreateList();
	List* history = CreateList();
	AddToList(history, DeepCloneList(medicine_list, (CloningFunction)CloneMedicine));
	int medicine_number = 3,
		id[] = {1, 2, 3},
		concentration[] = {2, 4, 3},
		quantity[] = {3, 1, 3};
	char name[3][10];
	strcpy(name[0], "asd");
	strcpy(name[1], "dwasq");
	strcpy(name[2], "easc");

	for(int i = 0; i < medicine_number; i++){
		AddMedicineService(medicine_list, history, id[i], name[i],
			concentration[i], quantity[i]);
	}

	ListIterator* first_iterator =
		CreateListIterator(medicine_list),
		* second_iterator =
		CreateListIterator(medicine_list);

	//Quantity, not reversed
	SortListService(medicine_list, 1, 0);

	ResetIterator(first_iterator);
	ResetIterator(second_iterator);
	NextIterator(second_iterator);

	while(IteratorIsValid(second_iterator)){
		assert(((Medicine*)((Medicine*)GetElement(first_iterator)))->quantity
			<= ((Medicine*)GetElement(second_iterator))->quantity);

		NextIterator(first_iterator);
		NextIterator(second_iterator);
	}

	//Quantity, reversed
	SortListService(medicine_list, 1, 1);

	ResetIterator(first_iterator);
	ResetIterator(second_iterator);
	NextIterator(second_iterator);

	while(IteratorIsValid(second_iterator)){
		assert(((Medicine*)GetElement(first_iterator))->quantity
			>= ((Medicine*)GetElement(second_iterator))->quantity);

		NextIterator(first_iterator);
		NextIterator(second_iterator);
	}

	//Name, not reversed
	SortListService(medicine_list, 0, 0);

	ResetIterator(first_iterator);
	ResetIterator(second_iterator);
	NextIterator(second_iterator);

	while(IteratorIsValid(second_iterator)){
		assert(strcmp(((Medicine*)GetElement(first_iterator))->name,
			((Medicine*)GetElement(second_iterator))->name) <= 0);

		NextIterator(first_iterator);
		NextIterator(second_iterator);
	}

	//Name, reversed
	SortListService(medicine_list, 0, 1);

	ResetIterator(first_iterator);
	ResetIterator(second_iterator);
	NextIterator(second_iterator);

	while(IteratorIsValid(second_iterator)){
		assert(strcmp(((Medicine*)GetElement(first_iterator))->name,
			((Medicine*)GetElement(second_iterator))->name) >= 0);

		NextIterator(first_iterator);
		NextIterator(second_iterator);
	}

	DeepDestroyList(medicine_list, (DestructionFunction)DestroyMedicine);
	DestroyIterator(first_iterator);
	DestroyIterator(second_iterator);
}

void TestListIterator(){
	List* medicine_list = CreateList();
	List* history = CreateList();
	AddToList(history, DeepCloneList(medicine_list, (CloningFunction)CloneMedicine));
	int first_id = 1,
		first_concentration = 2,
		first_quantity = 3,
		second_id = 2,
		second_concentration = 3,
		second_quantity = 2;
	char first_name[] = "asd",
		 second_name[] = "dsaasd";

	AddMedicineService(medicine_list, history, first_id, first_name,
		first_concentration, first_quantity);
	AddMedicineService(medicine_list, history, second_id, second_name,
		second_concentration, second_quantity);

	ListIterator* iterator = CreateListIterator(
		medicine_list);

	assert(GetMedicineId(GetElement(iterator)) == 1);
	assert(NextIterator(iterator) == 0);
	assert(GetMedicineId(GetElement(iterator)) == 2);
	assert(NextIterator(iterator) == 0);
	assert(IteratorIsValid(iterator) == 0);
	assert(NextIterator(iterator) == 1);

	DeepDestroyList(medicine_list, (DestructionFunction)DestroyMedicine);
	DestroyIterator(iterator);
}

void TestUndo(){
	List* medicine_list = CreateList();
	List* history = CreateList();
	AddToList(history, DeepCloneList(medicine_list, (CloningFunction)CloneMedicine));

	assert(history->current_size == 1);
	assert(((List*)history->list[0])->current_size == 0);

	AddMedicineService(medicine_list, history, 1, "a", 1, 1);
	assert(((Medicine*)((List*)history->list[1])->list[0])->id == 1);
	int status = UndoLastOperationService(&medicine_list, history);
	assert(medicine_list->current_size == 0);
	status = UndoLastOperationService(&medicine_list, history);
	assert(status == 1);

	DeepDestroyList(medicine_list, (DestructionFunction)DestroyMedicine);
}

void TestAll(){
	TestAddMedicineService();
	TestDeleteMedicineService();
	TestModifyMedicineService();
	TestSortMedicineListService();
	TestListIterator();
	TestUndo();
}
