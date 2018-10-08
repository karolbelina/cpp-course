#include "tablecontainer.h"

TableContainer::~TableContainer() {
	removeAllTables();
}

void TableContainer::addTable(std::string name, int tableLength, Error &error) {
	Table* table = new Table(name, tableLength, error);

	if(error == NoError) {
		tables.push_back(table);
	}
}

void TableContainer::removeTable(int tableIndex, Error &error) {
	if(tableIndex < 0 || tableIndex > tables.size() - 1) {
		error = IndexOutOfBounds;
		return;
	}

	delete tables[tableIndex];
	tables.erase(tables.begin() + tableIndex);
	error = NoError;
}

void TableContainer::removeAllTables() {
	for(int i = 0; i < tables.size(); i++) {
		delete tables[i];
	}

	tables.clear();
}

void TableContainer::renameTable(int tableIndex, std::string name, Error &error) {
	if(tableIndex < 0 || tableIndex > tables.size() - 1) {
		error = IndexOutOfBounds;
		return;
	}

	tables[tableIndex]->setName(name);
	error = NoError;
}

void TableContainer::resizeTable(int tableIndex, int tableLength, Error &error) {
	if(tableIndex < 0 || tableIndex > tables.size() - 1) {
		error = IndexOutOfBounds;
		return;
	}

	tables[tableIndex]->setTableLength(tableLength, error);
}

void TableContainer::cloneTable(int tableIndex, Error &error) {
	if(tableIndex < 0 || tableIndex > tables.size() - 1) {
		error = IndexOutOfBounds;
		return;
	}

	Table* table = tables[tableIndex]->clone(error);

	if(error == NoError) {
		tables.push_back(table);
	}
}

std::string TableContainer::getTableStatus(int tableIndex, Error & error) {
	if(tableIndex < 0 || tableIndex > tables.size() - 1) {
		error = IndexOutOfBounds;
		return;
	}

	std::cout << *tables[tableIndex] << std::endl;
	error = NoError;
}

std::string TableContainer::getStatus() {
	std::cout << "(";
	for(int j = 0; j < tables.size() - 1; j++) {
		std::cout << tables[j]->getName() << ", ";
	}
	std::cout << tables[tables.size() - 1]->getName() << ")" << std::endl;
}

void TableContainer::editTable(int tableIndex, int cellIndex, int value, Error &error) {
	if(tableIndex < 0 || tableIndex > tables.size() - 1) {
		error = IndexOutOfBounds;
		return;
	}

	tables[tableIndex]->setElement(cellIndex, value, error);
}

int TableContainer::size() {
	return tables.size();
}