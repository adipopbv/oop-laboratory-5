#pragma once

typedef struct{
	int id, concentration, quantity;
	char* name;
} Medicine;

/* Creates a medicine.
 * Preconditions:
 *  id - int, the id of the medicine
 *  name - char*, the name of the medicine
 *  concentration - int, the concentration of the medicine
 *  quantity - int, the quantity of the medicine
 * Postconditions: A medicine is created with the given
 * properties.
 */
Medicine* CreateMedicine(int id, char* name, int concentration, int quantity);

/* Destroys a medicine.
 * Preconditions:
 *  medicine - Medicine*, pointer to the medicine to be deleted,
 *  		   must be a valid pointer
 * Postconditions: The medicine at the given pointer will be
 * free.
 */
void DestroyMedicine(Medicine* medicine);

/* Checks equality between two medicine.
 * Preconditions:
 *  first - Medicine, a medicine
 *  second - Medicine, a medicine
 * Postconditions: 1 is returned if the two medicine are equal,
 * 0 is returned otherwise.
 */
int MedicineEqual(Medicine* first, Medicine* second);

/* Sets the name of a medicine.
 * Preconditions:
 *  medicine - Medicine*, pointer to the medicine that will be
 *  		   modified, must be a valid pointer
 *  new_name - char*, pointer to a string, must be a valid pointer
 * Postconditions: The name of the medicine will become the string
 * to witch 'new_name' is pointing.
 */
void SetMedicineName(Medicine* medicine, char* new_name);

/* Sets the concentration of a medicine.
 * Preconditions:
 *  medicine - Medicine*, pointer to the medicine that will be
 *  		   modified, must be a valid pointer
 *  new_concentration - int, the new concentration
 * Postconditions: The concentration of the medicine will become
 * 'new_concentration'.
 */
void SetMedicineConcentration(Medicine* medicine, int new_concentration);

/* Sets the quantity of a medicine.
 * Preconditions:
 *  medicine - Medicine*, pointer to the medicine that will be
 *  		   modified, must be a valid pointer
 *  new_quantity - int, the new quantity
 * Postconditions: The quantity of the medicine will become
 * 'new_quantity'.
 */
void SetMedicineQuantity(Medicine* medicine, int new_quantity);

/* Gets the id of a medicine.
 * Preconditions:
 *  medicine - Medicine, a medicine
 * Postconditions: The id of 'medicine' is returned.
 */
int GetMedicineId(Medicine* medicine);

/* Gets the concentration of a medicine.
 * Preconditions:
 *  medicine - Medicine, a medicine
 * Postconditions: The concentration of 'medicine' is returned.
 */
int GetMedicineConcentration(Medicine* medicine);

/* Gets the name of a medicine.
 * Preconditions:
 *  medicine - Medicine, a medicine
 * Postconditions: A pointer to the name of 'medicine' is
 * returned.
 */
char* GetMedicineName(Medicine* medicine);

/* Gets the quantity of a medicine.
 * Preconditions:
 *  medicine - Medicine, a medicine
 * Postconditions: The quantity of 'medicine' is returned.
 */
int GetMedicineQuantity(Medicine* medicine);

/* Validates a medicine.
 * Preconditions:
 *  medicine - Medicine, a medicine
 * Postconditions: The return value is obtained by the following
 * rules:
 *  - the bit number 0 is set if the id of 'medicine' is negative
 *  - the bit number 1 is set if the name of 'medicine' is empty
 *  - the bit number 2 is set if the concentration of 'medicine'
 *    is less than or equal to 0
 *  - the bit number 3 is set if the quantity of 'medicine' is
 *    less than or equal to 0
 */
int ValidateMedicine(Medicine* medicine);
