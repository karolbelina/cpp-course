#include <iostream>
#include <string>
#include <new>			// std::nothrow

#include "table.h"
#include "constants.h"

Table::Table(int* error) {
	name = DEFAULT_NAME;
	setTableLength(DEFAULT_LENGTH, error);

	std::cout << "bezp: " + name << std::endl;
}

Table::Table(std::string name, int tableLength, int* error) {
	this->name = name;
	setTableLength(tableLength, error);

	std::cout << "parametr: " + this->name << std::endl;
}

Table::Table(const Table &other, int* error) {
	name = other.name + "_copy";
	setTable(other, error);

	std::cout << "kopiuj: " + name << std::endl;
}

Table::~Table() {
	delete[] array;

	std::cout << "usuwam: " + name << std::endl;
}

void Table::setName(std::string name) {
	this->name = name;
}

void Table::setTableLength(int tableLength, int* error) {
	if(tableLength < 0) {
		*error = 1;
		return;
	}

	int* temp = new (std::nothrow) int[tableLength];

	if(!temp) {
		*error = 2;
		return;
	}

	if(array) { // array has been already initialized
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
	}
	else { // array is being initialized for the first time
		for(int i = 0; i < tableLength; i++) {
			temp[i] = DEFAULT_VALUE;
		}
	}

	if(array) {
		delete[] array;
	}

	array = temp;
	arraySize = tableLength;

	*error = 0;
}

void Table::setElement(int offset, int value, int* error) {
	if(offset < 0 || offset > arraySize - 1) {
		*error = 1;
		return;
	}
	*error = 0;
	array[offset] = value;
}

int Table::getElement(int offset, int* error) {
	if(offset < 0 || offset > arraySize - 1) {
		*error = 1;
		return NULL;
	}
	*error = 0;
	return array[offset];
}

Table* Table::clone() {
	return new Table(*this);
}

void Table::setTable(const Table &other, int* error) {
	int length = other.arraySize;
	int* otherArray = other.array;
	int* temp = new (std::nothrow) int[length];

	if(!temp) {
		*error = 1;
		return;
	}

	for(int i = 0; i < length; i++) {
		temp[i] = otherArray[i];
	}

	if(array) {
		delete[] array;
	}

	array = temp;
	arraySize = length;

	*error = 0;
}

std::string Table::getStatus() {
	std::string retVal = "(" + name + " len: " + std::to_string(arraySize) + " values: ";

	for(int i = 0; i < arraySize - 1; i++) {
		retVal = retVal + std::to_string(array[i]) + ", ";
	}

	retVal = retVal + std::to_string(array[arraySize - 1]) + ")";

	return retVal;
}

