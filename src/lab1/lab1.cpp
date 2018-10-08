#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "table.h"
#include "tablecontainer.h"
#include "constants.h"

int main() {
	TableContainer tableContainer;
	std::string input;

	

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
					int index = tableContainer.size();

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
						tableContainer.addTable(name, length, error);

						if(error == NoError) {
							i++;
							std::cout << "table created successfully" << std::endl;
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
				Error error;
				tableContainer.removeTable(tableIndex, error);

				if(error == NoError) {
					std::cout << "removed table #" << tableIndex << std::endl;
				}
				else if(error == IndexOutOfBounds) {
					std::cout << "invalid index" << std::endl;
				}
				else {
					std::cout << "unknown error" << std::endl;
				}
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
					tableContainer.removeAllTables();

					std::cout << "removed all tables" << std::endl;
				}
			}
		}
		else if(command == "status") {
			int tableIndex;

			if(inputStream >> tableIndex) {
				// wczytalo liczbe
				Error error;
				tableContainer.getTableStatus(tableIndex, error);

				if(error == NoError) {
					// nic
				}
				else if(error == IndexOutOfBounds) {
					std::cout << "invalid index" << std::endl;
				}
				else {
					std::cout << "unknown error" << std::endl;
				}
			}
			else {
				// wczytalo nic ciekawego poza komenda
				tableContainer.getStatus();
			}
		}
		else {
			std::cout << "invalid command" << std::endl;
		}
	}
}

void showHelp() {
	std::cout << "table creator\navailable commands:\n\tcreate <amount>\n\trename <table index>\n\tresize <table index>\n\t"
		"remove <table index>\n\tremove all\n\tclone <table index>\n\tstatus\n\tstatus <table index>\n\t"
		"edit <table index> <cell index> <value>\n\thelp\n\tquit" << std::endl;
}