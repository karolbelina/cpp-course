#include "constants.h"
#include "tablecontainer.h"

#include <sstream>

table::TableContainer::~TableContainer() {
	removeAllTables();
}

void table::TableContainer::addTable(std::string name, size_t tableLength) {
	tables.push_back(new Table(name, tableLength));
}

void table::TableContainer::removeTable(size_t tableIndex) {
	delete getTable(tableIndex);
	tables.erase(tables.begin() + tableIndex);
}

void table::TableContainer::removeAllTables() {
	for(table::Table* table : tables) {
		delete table;
	}

	tables.clear();
}

void table::TableContainer::renameTable(size_t tableIndex, std::string name) {
	getTable(tableIndex)->setName(name);
}

void table::TableContainer::resizeTable(size_t tableIndex, size_t tableLength) {
	getTable(tableIndex)->setTableLength(tableLength);
}

void table::TableContainer::cloneTable(size_t tableIndex) {
	tables.push_back(getTable(tableIndex)->clone());
}

std::string table::TableContainer::getTableStatus(size_t tableIndex) {
	return getTable(tableIndex)->getStatus();
}

std::string table::TableContainer::getStatus() {
	std::ostringstream stream;

	stream << OPEN_PARENTHESIS;

	std::string separator;
	for(table::Table* table : tables) {
		stream << separator << table->getName();
		separator = COMMA;
	}

	stream << CLOSE_PARENTHESIS;

	return stream.str();
}

void table::TableContainer::editTable(size_t tableIndex, size_t cellIndex, int value) {
	getTable(tableIndex)->setElement(cellIndex, value);
}

size_t table::TableContainer::tableCount() {
	return tables.size();
}

table::Table* table::TableContainer::getTable(size_t tableIndex) {
	try {
		return tables[tableIndex];
	}
	catch(const std::out_of_range &e) {
		throw std::out_of_range("table index out of range");
	}
}