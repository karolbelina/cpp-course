#include "table.h"
#include "tablefactory.h"

Table* TableFactory::createDefaultTable(int* error) {
	return checkErrors(new Table(error), error);
}

Table* TableFactory::createTableFromParameters(std::string name, int tableLength, int* error) {
	return checkErrors(new Table(name, tableLength, error), error);
}

Table* TableFactory::createTableFromTable(const Table &other, int* error) {
	return checkErrors(new Table(other, error), error);
}

Table* TableFactory::checkErrors(Table* other, int* error) {
	if(*error == 0) {
		return other;
	}

	delete other;
	return NULL;
}