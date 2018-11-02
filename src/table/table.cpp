#include "constants.h"
#include "table.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

table::Table::Table() : name(DEFAULT_NAME) {
	setTableLength(DEFAULT_LENGTH);

	std::cout << std::string(PADDING, SPACE) << NOARG_CONSTRUCTOR_MESSAGE << COLON << SPACE << name << std::endl;
}

table::Table::Table(std::string name, size_t tableLength) : name(name) {
	setTableLength(tableLength);

	std::cout << std::string(PADDING, SPACE) << PARAM_CONSTRUCTOR_MESSAGE << COLON << SPACE << this->name << std::endl;
}

table::Table::Table(const Table &other) : name(other.name + COPY_STRING) {
	setTable(other);

	std::cout << std::string(PADDING, SPACE) << COPYING_CONSTRUCTOR_MESSAGE << COLON << SPACE << name << std::endl;
}

table::Table::~Table() {
	if(array != nullptr) {
		delete[] array;
	}

	std::cout << std::string(PADDING, SPACE) << DESTRUCTOR_MESSAGE << COLON << SPACE << name << std::endl;
}

void table::Table::setName(std::string name) {
	this->name = name;
}

std::string table::Table::getName() {
	return name;
}

void table::Table::setTableLength(size_t tableLength) {
	int* temp = new int[tableLength];

	if(array != nullptr) { // array has been already initialized
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

	if(array != nullptr) {
		delete[] array;
	}

	array = temp;
	arraySize = tableLength;
}

void table::Table::setElement(size_t offset, int value) {
	try {
		array[offset] = value;
	}
	catch(const std::out_of_range &e) {
		throw std::out_of_range("cell index out of range");
	}
}

int table::Table::getElement(size_t offset) {
	try {
		return array[offset];
	}
	catch(const std::out_of_range &e) {
		throw std::out_of_range("cell index out of range");
	}
}

table::Table* table::Table::clone() {
	return new Table(*this);
}

void table::Table::setTable(const Table &other) {
	int length = other.arraySize;
	int* otherArray = other.array;
	int* temp = new int[length];

	for(int i = 0; i < length; i++) {
		temp[i] = otherArray[i];
	}

	if(array != nullptr) {
		delete[] array;
	}

	array = temp;
	arraySize = length;
}

std::string table::Table::getStatus() {
	std::ostringstream stream;

	stream << OPEN_PARENTHESIS << name << SPACE << LENGTH_STRING << COLON << SPACE << arraySize << SPACE << VALUES_STRING << COLON << SPACE;

	std::string separator;
	for(size_t i = 0; i < arraySize; i++) {
		stream << separator << array[i];
		separator = COMMA + SPACE;
	}

	stream << CLOSE_PARENTHESIS;

	return stream.str();
}