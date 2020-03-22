#include "ui.h"

#include "entities/universal_list.h"
#include "entities/universal_list_iterator.h"
#include "service.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 100

void GetMedicineString(Medicine* medicine, char** string){
	*string = (char*)malloc(sizeof(char) * (strlen(medicine->name) + 50));
	sprintf(
		*string,
		"ID: %d\nName: %s\nConcentration: %d\nQuantity: %d",
		medicine->id,
		medicine->name,
		medicine->concentration,
		medicine->quantity
	);
}

void PrintMenu(){
	printf("~~~~~~~~~~~~~~~~~~~~\n");
	printf("1: Add medicine\n2: Print medicine list\n3: Delete medicine\n4: Modify medicine\n5: Sort medicine list\n6: Print filtered medicine list\n7: Undo last operation\n0: Exit\n\nEnter option: ");
}

int ReadNumber(){
	char buffer[BUFFERSIZE];
	int number;

	fgets(buffer, BUFFERSIZE, stdin);
	sscanf(buffer, "%d", &number);

	return number;
}

void AddMedicine(List* medicine_list, List* history){
	int id = 0, concentration = 0, quantity = 0, status;
	char buffer[BUFFERSIZE], name[BUFFERSIZE];
	name[0] = '\0';

	printf("Enter medicine id: ");
	fgets(buffer, BUFFERSIZE, stdin);
	sscanf(buffer, "%d", &id);

	printf("Enter medicine name: ");
	fgets(buffer, BUFFERSIZE, stdin);
	sscanf(buffer, "%s", name);

	printf("Enter medicine concentration: ");
	fgets(buffer, BUFFERSIZE, stdin);
	sscanf(buffer, "%d", &concentration);

	printf("Enter medicine quantity: ");
	fgets(buffer, BUFFERSIZE, stdin);
	sscanf(buffer, "%d", &quantity);

	status = AddMedicineService(medicine_list, history, id, name, concentration, quantity);

	if(status != 0){
		printf("Validation error:\n");

		if(status & 1){
			printf("Invalid id\n");
		}
		if(status & 2){
			printf("Invalid name\n");
		}
		if(status & 4){
			printf("Invalid concentration\n");
		}
		if(status & 8){
			printf("Invalid quantity\n");
		}
	}
}

void PrintList(List* medicine_list){
	ListIterator* iterator = CreateListIterator(medicine_list);

	while(IteratorIsValid(iterator) == 1){
		char* medicine_string;
		Medicine* current_medicine = (Medicine*)GetElement(iterator);
		GetMedicineString(current_medicine, &medicine_string);

		printf("%s\n\n", medicine_string);
		free(medicine_string);

		NextIterator(iterator);
	}

	DestroyIterator(iterator);
	printf("\n");
}

void PrintFilteredList(List* medicine_list){
	int method = -1, value = -1;
	char buffer[BUFFERSIZE], string[BUFFERSIZE], letter = '\0';

	printf("Select filter method:\n0: Quantity less than given value\n1: Name starting with given letter\n\nEnter option: ");
	method = ReadNumber();

	if(method < 0 || method > 1){
		printf("Invalid option\n");
		return;
	}

	if(method == 0){
		printf("Enter value: ");
		value = ReadNumber();

		if(value < 0){
			printf("Invalid option\n");
			return;
		}
	} else{
		printf("Enter starting letter: ");

		fgets(buffer, BUFFERSIZE, stdin);
		sscanf(buffer, "%s", string);

		if(strlen(string) > 0)
			letter = string[0];
		else{
			printf("Invalid option\n");
			return;
		}
	}

	ListIterator* iterator = CreateListIterator(medicine_list);

	while(IteratorIsValid(iterator) == 1){
		Medicine* current_medicine = (Medicine*)GetElement(iterator);

		if((method == 0 && GetMedicineQuantity(current_medicine) < value) ||
			(method == 1 && GetMedicineName(current_medicine)[0] == letter)){

			char* medicine_string;
			GetMedicineString(current_medicine, &medicine_string);

			printf("%s\n\n", medicine_string);
			free(medicine_string);
		}

		NextIterator(iterator);
	}

	DestroyIterator(iterator);

	printf("\n");
}

void DeleteMedicine(List* medicine_list, List* history){
	char buffer[BUFFERSIZE];
	int target_id, status;

	printf("Enter medicine id: ");
	fgets(buffer, BUFFERSIZE, stdin);
	sscanf(buffer, "%d", &target_id);

	status = DeleteMedicineService(medicine_list, history, target_id);

	if(status == 1){
		printf("Medicine with specified ID not found\n");
	}
}

void ModifyMedicine(List* medicine_list, List* history){
	char buffer[BUFFERSIZE], new_name[BUFFERSIZE];
	int target_id = -1, new_concentration = 0, status;
	new_name[0] = '\0';

	printf("Enter medicine id: ");
	fgets(buffer, BUFFERSIZE, stdin);
	sscanf(buffer, "%d", &target_id);

	printf("Enter new name: ");
	fgets(buffer, BUFFERSIZE, stdin);
	sscanf(buffer, "%s", new_name);

	printf("Enter new concentration: ");
	fgets(buffer, BUFFERSIZE, stdin);
	sscanf(buffer, "%d", &new_concentration);

	status = ModifyMedicineService(medicine_list, history, target_id, new_name, new_concentration);

	if(status == 1)
		printf("Medicine ID not found\n");
	if(status & 2)
		printf("The name can't be empty\n");
	if(status & 4)
		printf("The concentration can't be less than or equal to 0\n");
}

void SortMedicineList(List* medicine_list){
	int field = -1, reverse = -1;
	printf("Select the field by which to sort:\n0: Name\n1: Quantity\n\nEnter option: ");
	field = ReadNumber();

	if(field < 0 || field > 1){
		printf("Invalid option\n");
		return;
	}

	printf("Select order:\n0: Ascending\n1: Descending\n\nEnter option: ");
	reverse = ReadNumber();

	if(reverse < 0 || reverse > 1){
		printf("Invalid option\n");
		return;
	}

	SortListService(medicine_list, field, reverse);
	PrintList(medicine_list);
}

void UndoLastOperation(List** medicine_list, List* history)
{
	int status = UndoLastOperationService(medicine_list, history);

	if (status == 1)
		printf("Already at oldest change!\n");
	else
		printf("Operation succesful!\n");
}

void CleanupMedicineList(List* medicine_list){
	DeepDestroyList(medicine_list, (DestructionFunction)DestroyMedicine);
}

void CleanupHistory(List* history)
{
	for (int i=0; i<history->current_size; i++)
		DeepDestroyList(history->list[i], (DestructionFunction)DestroyMedicine);
	DestroyList(history);
}

void RunUI(List* medicine_list, List* history){
	int option;

	while(1){
		PrintMenu();
		option = ReadNumber();

		switch(option){
			case 0:
				CleanupMedicineList(medicine_list);
				CleanupHistory(history);
				return;

			case 1:
				AddMedicine(medicine_list, history);
				break;

			case 2:
				PrintList(medicine_list);
				break;

			case 3:
				DeleteMedicine(medicine_list, history);
				break;

			case 4:
				ModifyMedicine(medicine_list, history);
				break;

			case 5:
				SortMedicineList(medicine_list);
				break;

			case 6:
				PrintFilteredList(medicine_list);
				break;

			case 7:
				UndoLastOperation(&medicine_list, history);
				break;

			default:
				printf("Invalid option\n");
		}
	}
}
