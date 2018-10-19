#include "error.h"

#include <string>
#include <iostream>

#pragma once

class Table {
public:
	Table();
	Table(std::string name, int tableLength, Error &error);
	Table(const Table &other);
	~Table();

	void setName(std::string name);
	std::string getName();
	void setTableLength(int tableLength, Error &error);
	void setElement(int offset, int value, Error &error);
	int getElement(int offset, Error &error);
	Table* clone();
	void setTable(const Table &other, Error &error);
	std::string getStatus();
	static void test(Table table);

private:
	std::string name;
	int* array;
	int arraySize;
};