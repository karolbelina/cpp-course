#include <string>
#include "ctable.h"
#include "constants.h"

CTable::CTable() {
	name = DEFAULT_NAME;
	setTableLength(DEFAULT_LENGTH); // todo: success check?
}

CTable::CTable(std::string name, int tableLength) {
	this->name = name;

	int* success;
	setTableLength(tableLength, success);

	if(*success == 1) {
		// print the error message
	}
}

// todo
CTable::CTable(CTable &other) {
	name = (*other).name;
}