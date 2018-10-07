#include <iostream>
#include <string>
#include <new>			// std::nothrow
#include "table.h"
#include "constants.h"

Table::Table() {
	name = DEFAULT_NAME;

	arraySize = DEFAULT_LENGTH;
	array = new int[arraySize];
	for(int i = 0; i < arraySize; i++) {
		array[i] = DEFAULT_VALUE;
	}

	std::cout << "bezp: " + name;
}

Table::Table(std::string name, int tableLength, int* error) {
	this->name = name;
	
	arraySize = tableLength;
	array = new int[arraySize];
	for(int i = 0; i < arraySize; i++) {
		array[i] = DEFAULT_VALUE;
	}

	std::cout << "parametr: " + this->name;
}

Table::Table(const Table &other) {
	name = other.name + "_copy";
	setTable(other);

	std::cout << "kopiuj: " + name;
}

Table::~Table() {
	std::cout << "usuwam: " + name;

	delete[] array;
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

void Table::setTable(const Table &other) {
	array = other.array;			// ????
}

std::string Table::getStatus() {
	std::string retVal = "(" + name + " len: " + std::to_string(arraySize) + " values: ";

	for(int i = 0; i < arraySize - 1; i++) {
		retVal = retVal + std::to_string(array[i]) + ", ";
	}

	retVal = retVal + std::to_string(array[arraySize - 1]) + ")";

	return retVal;
}

