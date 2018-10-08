#include <iostream>
#include <string>
#include <sstream>
#include <new>			// std::nothrow

#include "table.h"
#include "constants.h"

Table::Table(int &error) {
	name = DEFAULT_NAME;
	setTableLength(DEFAULT_LENGTH, error);

	std::cout << "\tbezp: " + name << std::endl;
}

Table::Table(std::string name, int tableLength, int &error) {
	this->name = name;
	setTableLength(tableLength, error);

	std::cout << "\tparametr: " + this->name << std::endl;
}

Table::Table(const Table &other, int &error) {
	name = other.name + "_copy";
	setTable(other, error);

	std::cout << "\tkopiuj: " + name << std::endl;
}

Table::~Table() {
	delete[] array;

	std::cout << "\tusuwam: " + name << std::endl;
}

void Table::setName(std::string name) {
	this->name = name;
}

void Table::setTableLength(int tableLength, int &error) {
	if(tableLength < 0) {
		error = 1;
		return;
	}

	int* temp = new (std::nothrow) int[tableLength];

	if(temp == NULL) {
		error = 2;
		return;
	}

	if(array != NULL) { // array has been already initialized
		if(tableLength <= arraySize) {
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

	if(array != NULL) {
		delete[] array;
	}

	array = temp;
	arraySize = tableLength;

	error = 0;
}

void Table::setElement(int offset, int value, int &error) {
	if(offset < 0 || offset > arraySize - 1) {
		error = 1;
		return;
	}
	error = 0;
	array[offset] = value;
}

int Table::getElement(int offset, int &error) {
	if(offset < 0 || offset > arraySize - 1) {
		error = 1;
		return NULL;
	}
	error = 0;
	return array[offset];
}

Table* Table::clone() {
	return new Table(*this); // todo: error
}

void Table::setTable(const Table &other, int &error) {
	int length = other.arraySize;
	int* otherArray = other.array;
	int* temp = new (std::nothrow) int[length];

	if(!temp) {
		error = 1;
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

	error = 0;
}

std::ostream& operator<<(std::ostream &stream, const Table &table) {
	stream << "(" << table.name << " len: " << table.arraySize << " values: ";

	for(int i = 0; i < table.arraySize - 1; i++) {
		stream << table.array[i] << ", ";
	}

	stream << table.array[table.arraySize - 1] << ")";

	return stream;
}