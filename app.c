#include "ui.h"
#include "entities/medicine_list.h"
#include "tests.h"

int main(){
	List medicine_list = CreateList();
	List history = CreateList();
	AddToList(&history, medicine_list);

	TestAll();
	RunUI(&medicine_list, &history);

	return 0;
}
