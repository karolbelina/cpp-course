#include <string>
#include <iostream>

#include "error.h"

#pragma once

class Table {
public:
	Table(Error &error);
	Table(std::string name, int tableLength, Error &error);
	Table(const Table &other, Error &error);
	~Table();

	void setName(std::string name);
	std::string getName();
	void setTableLength(int tableLength, Error &error);
	void setElement(int offset, int value, Error &error);
	int getElement(int offset, Error &error);
	Table* clone(Error &error);
	void setTable(const Table &other, Error &error);
	friend std::ostream& operator<<(std::ostream &stream, const Table &table);

private:
	std::string name;
	int* array;
	int arraySize;
};