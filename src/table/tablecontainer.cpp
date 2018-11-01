#include "constants.h"
#include "tablecontainer.h"

#include <sstream>

table::TableContainer::~TableContainer() {
	removeAllTables();
}

void table::TableContainer::addTable(std::string name, int tableLength, Error &error) {
	Table* table = new Table(name, tableLength, error);

	if(error == NoError) {
		tables.push_back(table);
	}
	else {
		delete table;
	}
}

void table::TableContainer::removeTable(int tableIndex, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	error = NoError;
	delete tables[tableIndex];
	tables.erase(tables.begin() + tableIndex);
}

void table::TableContainer::removeAllTables() {
	for(size_t i = 0, size = tables.size(); i < size; i++) {
		delete tables[i];
	}

	tables.clear();
}

void table::TableContainer::renameTable(int tableIndex, std::string name, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	error = NoError;
	tables[tableIndex]->setName(name);
}

void table::TableContainer::resizeTable(int tableIndex, int tableLength, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	tables[tableIndex]->setTableLength(tableLength, error);
}

void table::TableContainer::cloneTable(int tableIndex, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	error = NoError;
	Table* table = tables[tableIndex]->clone();
	tables.push_back(table);
}

std::string table::TableContainer::getTableStatus(int tableIndex, Error & error) {
	if(checkIndex(tableIndex, error)) {
		return EMPTY_STRING;
	}

	error = NoError;
	return tables[tableIndex]->getStatus();
}

std::string table::TableContainer::getStatus() {
	std::ostringstream stream;

	stream << OPEN_PARENTHESIS;

	for(int i = 0; i < (int)(tables.size()) - 1; i++) {
		stream << tables[i]->getName() << COMMA;
	}

	if(tables.size() > 0) {
		stream << tables[tables.size() - 1]->getName();
	}

	stream << CLOSE_PARENTHESIS;

	return stream.str();
}

void table::TableContainer::editTable(int tableIndex, int cellIndex, int value, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	tables[tableIndex]->setElement(cellIndex, value, error);
}

int table::TableContainer::size() {
	return tables.size();
}

void table::TableContainer::testTable(int tableIndex, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	error = NoError;
	Table::test(*tables[tableIndex]);
}

bool table::TableContainer::checkIndex(int tableIndex, Error &error) {
	if(tableIndex < 0 || tableIndex >= (int) tables.size()) {
		error = IndexOutOfBounds;
		return true;
	}

	return false;
}