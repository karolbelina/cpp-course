#include <iostream>
#include <string>
#include <new>			// std::nothrow
#include "ctable.h"
#include "constants.h"

CTable::CTable(int* state) {
	name = DEFAULT_NAME;
	setTableLength(DEFAULT_LENGTH, state);
}

CTable::CTable(std::string name, int tableLength, int* state) {
	this->name = name;
	setTableLength(tableLength, state);
}

CTable::CTable(const CTable &other) {
	name = other.name + "_copy";
	array = other.array;
}

void CTable::setName(std::string name) {
	this->name = name;
}

void CTable::setTableLength(int tableLength, int* state) {
	if(tableLength < 0) {
		*state = 1;
		return;
	}

	int* temp = new (std::nothrow) int[tableLength];

	if(!temp) {
		*state = 2;
		return;
	}

	if(tableLength < arraySize) {
		for(int i = 0; i < tableLength; i++) {
			temp[i] = array[i];
		}
	}
	else if(tableLength > arraySize) {
		for(int i = 0; i < arraySize; i++) {
			temp[i] = array[i];
		}

		for(int i = arraySize; i < tableLength; i++) {
			temp[i] = DEFAULT_VALUE;
		}
	}

	delete[] array;
	array = temp;
	arraySize = tableLength;

	*state = 0;
}

void CTable::setElement(int offset, int value, int* success) {
	if(offset < 0 || offset > arraySize - 1) {
		*success = 0;
		return;
	}
	array[offset] = value;
}