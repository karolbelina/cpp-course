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
			for(size_t i = 0; i < tableLength; i++) {
				temp[i] = array[i];
			}
		}
		else if(tableLength > arraySize) {
			for(size_t i = 0; i < arraySize; i++) {
				temp[i] = array[i];
			}

			for(size_t i = arraySize; i < tableLength; i++) {
				temp[i] = DEFAULT_VALUE;
			}
		}
	}
	else { // array is being initialized for the first time
		for(size_t i = 0; i < tableLength; i++) {
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
	catch(const std::out_of_range) {
		throw std::out_of_range("cell index out of range");
	}
}

int table::Table::getElement(size_t offset) {
	try {
		return array[offset];
	}
	catch(const std::out_of_range) {
		throw std::out_of_range("cell index out of range");
	}
}

table::Table* table::Table::clone() {
	return new Table(*this);
}

void table::Table::setTable(const Table &other) {
	int* temp = new int[other.arraySize];

	for(size_t i = 0; i < other.arraySize; i++) {
		temp[i] = other.array[i];
	}

	if(array != nullptr) {
		delete[] array;
	}

	array = temp;
	arraySize = other.arraySize;
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