#pragma once

#include <iostream>
#include <string>

namespace table {
	class Table {
	public:
		Table();
		Table(std::string name, size_t tableLength);
		Table(const Table &other);
		~Table();

		void setName(std::string name);
		std::string getName();
		void setTableLength(size_t tableLength);
		void setElement(size_t offset, int value);
		int getElement(size_t offset);
		Table* clone();
		void setTable(const Table &other);
		std::string getStatus();

	private:
		std::string name;
		int* array;
		int arraySize;
	};
}