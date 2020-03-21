#include "ui.h"
#include "entities/medicine_list.h"
#include "tests.h"

int main(){
	MedicineList medicine_list = CreateMedicineList();

	TestAll();
	RunUI(&medicine_list);

	return 0;
}
