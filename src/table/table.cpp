#include "stdafx.h"
#include "constants.h"
#include "table.h"

#include <iostream>
#include <string>
#include <sstream>
#include <new>			// std::nothrow

Table::Table() {
	name = DEFAULT_NAME;
	Error error;
	setTableLength(DEFAULT_LENGTH, error);

	std::cout << NOARG_CONSTRUCTOR_MESSAGE + name << std::endl;
}

Table::Table(std::string name, int tableLength, Error &error) {
	this->name = name;
	setTableLength(tableLength, error);

	std::cout << PARAM_CONSTRUCTOR_MESSAGE + this->name << std::endl;
}

Table::Table(const Table &other) {
	name = other.name + COPY_STRING;
	Error error;
	setTable(other, error);

	std::cout << COPYING_CONSTRUCTOR_MESSAGE + name << std::endl;
}

Table::~Table() {
	if(array != NULL) {
		delete[] array;
	}

	std::cout << DESTRUCTOR_MESSAGE + name << std::endl;
}

void Table::setName(std::string name) {
	this->name = name;
}

std::string Table::getName() {
	return name;
}

void Table::setTableLength(int tableLength, Error &error) {
	if(tableLength < 0) {
		error = InvalidArgument;
		return;
	}

	int* temp = new (std::nothrow) int[tableLength];

	if(temp == NULL) {
		error = OutOfMemory;
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

	error = NoError;
}

void Table::setElement(int offset, int value, Error &error) {
	if(offset < 0 || offset > arraySize - 1) {
		error = IndexOutOfBounds;
		return;
	}
	error = NoError;
	array[offset] = value;
}

int Table::getElement(int offset, Error &error) {
	if(offset < 0 || offset > arraySize - 1) {
		error = IndexOutOfBounds;
		return NULL;
	}
	error = NoError;
	return array[offset];
}

Table* Table::clone() {
	return new Table(*this);
}

void Table::setTable(const Table &other, Error &error) {
	int length = other.arraySize;
	int* otherArray = other.array;
	int* temp = new (std::nothrow) int[length];

	if(temp == NULL) {
		error = OutOfMemory;
		return;
	}

	for(int i = 0; i < length; i++) {
		temp[i] = otherArray[i];
	}

	if(array != NULL) {
		delete[] array;
	}

	array = temp;
	arraySize = length;

	error = NoError;
}

std::string Table::getStatus() {
	std::ostringstream stream;

	stream << OPEN_PARENTHESIS << name << LENGTH_STRING << arraySize << VALUES_STRING;

	for(int i = 0; i < arraySize - 1; i++) {
		stream << array[i] << COMMA;
	}

	if(arraySize > 0) {
		stream << array[arraySize - 1];
	}

	stream << CLOSE_PARENTHESIS;

	return stream.str();
}

void Table::test(Table table) {
	Error error;
	table.setTableLength(1, error);
}