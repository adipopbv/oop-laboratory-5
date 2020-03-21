#include "medicine_list_iterator.h"

MedicineListIterator CreateMedicineListIterator(MedicineList*
	medicine_list){
	MedicineListIterator iterator;

	iterator.medicine_list = medicine_list;
	iterator.current_element = 0;

	return iterator;
}

int IteratorIsValid(MedicineListIterator iterator){
	if(iterator.current_element <
		iterator.medicine_list->current_size){
		return 1;
	}

	return 0;
}

Medicine GetElement(MedicineListIterator iterator){
	return iterator.medicine_list->list[iterator.current_element];
}

int NextIterator(MedicineListIterator* iterator){
	if(IteratorIsValid(*iterator)){
		iterator->current_element++;
		return 0;
	} else{
		return 1;
	}
}

void ResetIterator(MedicineListIterator* iterator){
	iterator->current_element = 0;
}
