#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "table.h"
#include "constants.h"

int main() {
	std::vector<Table*> tables; // kasuj tabelki z pamieci a pozniej wskazniki z wektora !!!!!!!!!!!!
	std::string input;

	std::cout << "table creator\navailable commands:\n\tcreate <amount>\n\trename <table index>\n\tresize <table index>\n\t"
		"remove <table index>\n\tremove all\n\tclone <table index>\n\tstatus\n\tstatus <table index>\n\t"
		"edit <table index> <cell index> <value>\n\thelp\n\tquit" << std::endl;

	while(input != "quit") {
		std::cout << "> ";

		std::getline(std::cin, input);
		std::istringstream inputStream(input);
		std::string command;

		inputStream >> command;

		if(command == "create") {
			int amount;

			if(inputStream >> amount) {
				int i = 0;

				while(i < amount) {
					int index = tables.size();

					std::cout << "enter the name of table #" << index << ": " << std::endl << "> ";

					std::getline(std::cin, input);
					inputStream.clear();
					inputStream.str(input);
					std::string name;

					inputStream >> name;

					std::cout << "enter the length of table #" << index << ": " << std::endl << "> ";

					std::getline(std::cin, input);
					inputStream.clear();
					inputStream.str(input);
					int length;

					if(inputStream >> length) {
						Error error;
						Table* table = new Table(name, length, error);

						if(error == NoError) {
							tables.push_back(table);
							i++;
						}
						else if(error == InvalidArgument) {
							std::cout << "length cannot be negative" << std::endl;
						}
						else if(error == OutOfMemory) {
							std::cout << "out of memory" << std::endl;
						}
						else {
							std::cout << "unknown error" << std::endl;
						}
					}
					else {
						std::cout << "invalid length" << std::endl;
					}
				}
			}
			else if(inputStream.eof()) { // sama komenda
				std::cout << "no parameters" << std::endl;
			}
			else {
				std::cout << "invalid amount" << std::endl;
			}
		}
		else if(command == "remove") {
			int tableIndex;

			if(inputStream >> tableIndex) {
				// wczytalo liczbe
				// usun tabele o numerze
				delete tables[tableIndex];
				tables.erase(tables.begin() + tableIndex);

				std::cout << "removed table #" << tableIndex << std::endl;
			}
			else if(inputStream.eof()) {
				std::cout << "no parameters" << std::endl;
			}
			else {
				// nie liczba
				std::string allFlag;
				inputStream.clear();
				inputStream >> allFlag;

				if(allFlag == "all") {
					// usun wszystkie tabele
					for(int j = 0; j < tables.size(); j++) {
						delete tables[j];
					}
					tables.clear();

					std::cout << "removed all tables" << std::endl;
				}
			}
		}
		else if(command == "status") {
			int tableIndex;

			if(inputStream >> tableIndex) {
				// wczytalo liczbe

				std::cout << *tables[tableIndex] << std::endl;
			}
			else {
				// wczytalo nic ciekawego poza komenda
				std::cout << "(";
				for(int j = 0; j < tables.size() - 1; j++) {
					std::cout << tables[j]->getName() << ", ";
				}
				std::cout << tables[tables.size() - 1]->getName() << ")" << std::endl;
			}
		}
		else {
			std::cout << "invalid command" << std::endl;
		}
	}

	//int error;
	//Table& table = *TableFactory::createTableFromParameters("test", 8, error);
	//table.setElement(0, 5, error);

	//std::cout << table.getStatus() << std::endl;

	//delete &table;
}