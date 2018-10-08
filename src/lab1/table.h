#include <string>
#include <iostream>

#pragma once

class Table {
public:
	Table(int &error);
	Table(std::string name, int tableLength, int &error);
	Table(const Table &other, int &error);
	~Table();

	void setName(std::string name);
	void setTableLength(int tableLength, int &error);
	void setElement(int offset, int value, int &error);
	int getElement(int offset, int &error);
	Table* clone();
	void setTable(const Table &other, int &error);
	friend std::ostream& operator<<(std::ostream &stream, const Table &table);

private:
	std::string name;
	int* array;
	int arraySize;
};