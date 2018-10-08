#include <iostream>
#include <vector>
#include <string>

#include "table.h"
#include "tablefactory.h"
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

		int commandEndPos;
		std::string command;

		if((commandEndPos = input.find(DELIMETER)) != -1) {
			command = input.substr(0, commandEndPos);
		}

		if(command == "create") {
			std::string amountString = input.substr(commandEndPos + DELIMETER.length(), input.length());
			int amount = atoi(amountString.c_str());

			if(amount) {
				for(int i = 0; i < amount; i++) {
					int index = tables.size();

					std::cout << "enter the name of table #" << index << ": " << std::endl << "> ";

					std::string name;
					std::cin >> name;

					std::cout << "enter the length of table #" << index << ": " << std::endl << "> ";

					std::string lengthString;
					std::cin >> lengthString;
					int length = atoi(lengthString.c_str());

					if(length) {
						int error = 0;
						Table* table = TableFactory::createTableFromParameters(name, length, error);

						if(error == 0) {
							tables.push_back(table);
						}
						else if(error == 1) {
							std::cout << "length cannot be negative" << std::endl;
						}
						else {
							std::cout << "out of memory" << std::endl;
						}
					}
					else {
						std::cout << "invalid length" << std::endl;
					}
				}
			}
			else {
				std::cout << "invalid amount" << std::endl;
			}
		}
		else if(command == "rename") {

		}
	}

	//int error;
	//Table& table = *TableFactory::createTableFromParameters("test", 8, error);
	//table.setElement(0, 5, error);

	//std::cout << table.getStatus() << std::endl;

	//delete &table;
}