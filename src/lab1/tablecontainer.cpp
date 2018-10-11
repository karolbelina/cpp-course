#include <sstream>

#include "tablecontainer.h"
#include "constants.h"

TableContainer::~TableContainer() {
	removeAllTables();
}

void TableContainer::addTable(std::string name, int tableLength, Error &error) {
	Table* table = new Table(name, tableLength, error);

	if(error == NoError) {
		tables.push_back(table);
	}
	else {
		delete table;
	}
}

void TableContainer::removeTable(int tableIndex, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	error = NoError;
	delete tables[tableIndex];
	tables.erase(tables.begin() + tableIndex);
}

void TableContainer::removeAllTables() {
	for(int i = 0; i < tables.size(); i++) {
		delete tables[i];
	}

	tables.clear();
}

void TableContainer::renameTable(int tableIndex, std::string name, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	error = NoError;
	tables[tableIndex]->setName(name);
}

void TableContainer::resizeTable(int tableIndex, int tableLength, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	tables[tableIndex]->setTableLength(tableLength, error);
}

void TableContainer::cloneTable(int tableIndex, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	error = NoError;
	Table* table = tables[tableIndex]->clone();
	tables.push_back(table);
}

std::string TableContainer::getTableStatus(int tableIndex, Error & error) {
	if(checkIndex(tableIndex, error)) {
		return EMPTY_STRING;
	}

	error = NoError;
	return tables[tableIndex]->getStatus();
}

std::string TableContainer::getStatus() {
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

void TableContainer::editTable(int tableIndex, int cellIndex, int value, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	tables[tableIndex]->setElement(cellIndex, value, error);
}

int TableContainer::size() {
	return tables.size();
}

void TableContainer::testTable(int tableIndex, Error &error) {
	if(checkIndex(tableIndex, error)) {
		return;
	}

	error = NoError;
	Table::test(*tables[tableIndex]);
}

bool TableContainer::checkIndex(int tableIndex, Error &error) {
	if(tableIndex < 0 || tableIndex >= tables.size()) {
		error = IndexOutOfBounds;
		return true;
	}

	return false;
}