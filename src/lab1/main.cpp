#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "table.h"
#include "tablecontainer.h"
#include "constants.h"

bool nextInt(std::istringstream &stream, int &destination, std::string noParameterString, std::string invalidParameterString) {
	if(stream >> destination) {
		return true;
	}
	else if(stream.eof()) {
		if(noParameterString != "") {
			std::cout << noParameterString << std::endl;
		}
	}
	else {
		if(invalidParameterString != "") {
			std::cout << invalidParameterString << std::endl;
		}
	}

	return false;
}

void nextString(std::istringstream &stream, std::string &destination) {
	stream >> destination;
}

void getLine(std::istringstream &stream) {
	std::string input;

	std::getline(std::cin, input);
	stream.clear();
	stream.str(input);
}

bool printError(Error &error) {
	if(error == NoError) {
		return true;
	}
	else if(error == IndexOutOfBounds) {
		std::cout << "index out of bounds" << std::endl;
	}
	else if(error == InvalidArgument) {
		std::cout << "invalid argument" << std::endl;
	}
	else if(error == OutOfMemory) {
		std::cout << "out of memory" << std::endl;
	}
	else {
		std::cout << "unknown error" << std::endl;
	}

	return false;
}

int main() {
	TableContainer tableContainer;
	std::string input;
	std::istringstream inputStream;
	std::string command;

	std::cout << TITLE_MESSAGE << std::endl;
	std::cout << HELP_MESSAGE << std::endl;

	while(command != QUIT_COMMAND) {
		std::cout << PROMPT_MESSAGE;

		getLine(inputStream);
		nextString(inputStream, command);

		if(command == CREATE_COMMAND) {
			int amount;

			if(nextInt(inputStream, amount, "no parameters", "invalid amount")) {
				int i = 0;

				if(amount > 0) {
					while(i < amount) {
						int index = tableContainer.size();

						std::cout << ENTER_TABLE_NAME_MESSAGE << index << COLON << std::endl << PROMPT_MESSAGE;

						std::string name;
						getLine(inputStream);
						nextString(inputStream, name);

						std::cout << ENTER_TABLE_LENGTH_MESSAGE << index << COLON << std::endl << PROMPT_MESSAGE;

						int length;
						getLine(inputStream);

						if(nextInt(inputStream, length, "no parameters", "invalid length")) {
							Error error;
							tableContainer.addTable(name, length, error);

							if(printError(error)) {
								i++;

								std::cout << "table created successfully" << std::endl;
							}
						}
					}
				}
				else {
					std::cout << "invalid amount" << std::endl;
				}
			}
		}
		else if(command == REMOVE_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, "no parameters", "")) { // wczytalo liczbe
				Error error;
				tableContainer.removeTable(tableIndex, error);

				if(printError(error)) {
					std::cout << "removed table #" << tableIndex << std::endl;
				}
			}
			else { // nie liczba
				inputStream.clear();

				std::string allFlag;
				nextString(inputStream, allFlag);

				if(allFlag == ALL_COMMAND) { // usun wszystkie tabele
					tableContainer.removeAllTables();

					std::cout << "removed all tables" << std::endl;
				}
				else {
					std::cout << "invalid command" << std::endl;
				}
			}
		}
		else if(command == RESIZE_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, "no parameters", "invalid table index")) { // wczytalo pierwsza liczbe
				int tableLength;

				if(nextInt(inputStream, tableLength, "no second parameter", "invalid table length")) { // wczytalo druga liczbe
					Error error;
					tableContainer.resizeTable(tableIndex, tableLength, error);

					if(printError(error)) {
						std::cout << "the length of table #" << tableIndex << " has been set to " << tableLength << std::endl;
					}
				}
			}
		}
		else if(command == RENAME_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, "no parameters", "invalid table index")) { // wczytalo liczbe
				std::string name;
				
				nextString(inputStream, name);

				Error error;
				tableContainer.renameTable(tableIndex, name, error);

				if(printError(error)) {
					std::cout << "the name of table #" << tableIndex << " has been set to " << name << std::endl;
				}
			}
		}
		else if(command == STATUS_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, "", "")) { // wczytalo liczbe
				Error error;
				std::string status = tableContainer.getTableStatus(tableIndex, error);

				if(printError(error)) {
					std::cout << status << std::endl;
				}
			}
			else {
				// wczytalo nic ciekawego poza komenda
				std::cout << tableContainer.getStatus() << std::endl;
			}
		}
		else if(command == CLONE_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, "no parameters", "invalid table index")) { // read an int
				// an int has been successfully loaded
				Error error;
				tableContainer.cloneTable(tableIndex, error);

				if(printError(error)) {
					std::cout << "table #" << tableIndex << " has been cloned successfully" << std::endl;
				}
			}
		}
		else if(command == EDIT_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, "no parameters", "invalid table index")) { // read the first int
				int cellIndex;

				if(nextInt(inputStream, cellIndex, "no second and third parameter", "invalid cell index")) { // read the second int
					int value;

					if(nextInt(inputStream, value, "no third parameter", "invalid value")) { // read the third int
						Error error;
						tableContainer.editTable(tableIndex, cellIndex, value, error);

						if(printError(error)) {
							std::cout << "the value of cell #" << cellIndex << " of table #" << tableIndex << " has been set to " << value << std::endl;
						}
					}
				}
			}
		}
		else if(command == HELP_COMMAND) {
			std::cout << HELP_MESSAGE << std::endl;
		}
		else if(command != QUIT_COMMAND) {
			std::cout << "invalid command" << std::endl;
		}
	}
}