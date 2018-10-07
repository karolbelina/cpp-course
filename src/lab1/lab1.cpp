#include <iostream>

#include "table.h"
#include "tablefactory.h"

int main() {
    std::cout << "Hello World!\n";

	int* error = new int();
	Table& table = *TableFactory::createTableFromParameters("test", 8, error);
	table.setElement(0, 5, error);

	std::cout << table.getStatus() << std::endl;

	delete &table;
}