#include "ui.h"
#include "entities/universal_list.h"
#include "tests.h"

int main(){
	List* medicine_list = CreateList();
	List* history = CreateList();
	AddToList(history, DeepCloneList(medicine_list, (CloningFunction)CloneMedicine));

	TestAll();
	RunUI(medicine_list, history);

	return 0;
}
