#include "constants.h"
#include "error.h"
#include "table.h"
#include "tablecontainer.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

void getLine(std::istringstream &stream) {
	std::string input;

	std::cout << PROMPT_MESSAGE;

	std::getline(std::cin, input);
	stream.clear();
	stream.str(input);
}

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

bool printError(table::Error &error) {
	if(error == table::NoError) {
		return true;
	}
	else if(error == table::IndexOutOfBounds) {
		std::cout << INDEX_OUT_OF_BOUNDS_MESSAGE << std::endl;
	}
	else if(error == table::InvalidArgument) {
		std::cout << INVALID_ARGUMENT_MESSAGE << std::endl;
	}
	else if(error == table::OutOfMemory) {
		std::cout << OUT_OF_MEMORY_MESSAGE << std::endl;
	}
	else {
		std::cout << UNKNOWN_ERROR_MESSAGE << std::endl;
	}

	return false;
}

int main() {
	table::TableContainer tableContainer;
	std::string input;
	std::istringstream inputStream;
	std::string command;

	std::cout << TITLE_MESSAGE << std::endl;
	std::cout << HELP_MESSAGE << std::endl;

	while(command != QUIT_COMMAND) {
		getLine(inputStream);
		nextString(inputStream, command);

		if(command == CREATE_COMMAND) {
			int amount;

			if(nextInt(inputStream, amount, NO_PARAMETERS_MESSAGE, INVALID_AMOUNT_MESSAGE)) {
				int iterator = 0;

				if(amount > 0) {
					while(iterator < amount) {
						int index = tableContainer.size();

						std::cout << ENTER_TABLE_NAME_MESSAGE << index << COLON << std::endl;

						std::string name;
						getLine(inputStream);
						nextString(inputStream, name);

						std::cout << ENTER_TABLE_LENGTH_MESSAGE << index << COLON << std::endl;

						int length;
						getLine(inputStream);

						if(nextInt(inputStream, length, NO_PARAMETERS_MESSAGE, INVALID_TABLE_LENGTH_MESSAGE)) {
							table::Error error;
							tableContainer.addTable(name, length, error);

							if(printError(error)) {
								iterator++;

								std::cout << CREATED_TABLE_MESSAGE << std::endl;
							}
						}
					}
				}
				else {
					std::cout << AMOUNT_GREATER_THAN_ZERO_MESSAGE << std::endl;
				}
			}
		}
		else if(command == REMOVE_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, EMPTY_STRING)) { // wczytalo liczbe
				table::Error error;
				tableContainer.removeTable(tableIndex, error);

				if(printError(error)) {
					std::cout << REMOVED_TABLE_MESSAGE << tableIndex << std::endl;
				}
			}
			else { // nie liczba
				inputStream.clear();

				std::string allFlag;
				nextString(inputStream, allFlag);

				if(allFlag == ALL_COMMAND) { // usun wszystkie tabele
					tableContainer.removeAllTables();

					std::cout << REMOVED_ALL_TABLES_MESSAGE << std::endl;
				}
				else {
					std::cout << INVALID_COMMAND_MESSAGE << std::endl;
				}
			}
		}
		else if(command == RESIZE_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, INVALID_TABLE_INDEX_MESSAGE)) { // read the first int
				int tableLength;

				if(nextInt(inputStream, tableLength, NO_SECOND_PARAMETER_MESSAGE, INVALID_TABLE_LENGTH_MESSAGE)) { // read the second int
					table::Error error;
					tableContainer.resizeTable(tableIndex, tableLength, error);

					if(printError(error)) {
						std::cout << TABLE_LENGTH_MESSAGE << tableIndex << SET_TO_MESSAGE << tableLength << std::endl;
					}
				}
			}
		}
		else if(command == RENAME_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, INVALID_TABLE_INDEX_MESSAGE)) { // read an int
				std::string name;

				nextString(inputStream, name); // read a string

				table::Error error;
				tableContainer.renameTable(tableIndex, name, error);

				if(printError(error)) {
					std::cout << TABLE_NAME_MESSAGE << tableIndex << SET_TO_MESSAGE << name << std::endl;
				}
			}
		}
		else if(command == STATUS_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, EMPTY_STRING, EMPTY_STRING)) { // read an int
				table::Error error;
				std::string status = tableContainer.getTableStatus(tableIndex, error);

				if(printError(error)) {
					std::cout << status << std::endl;
				}
			}
			else {
				// no int has been read
				std::cout << tableContainer.getStatus() << std::endl;
			}
		}
		else if(command == CLONE_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, INVALID_TABLE_INDEX_MESSAGE)) { // read an int
				// an int has been successfully loaded
				table::Error error;
				tableContainer.cloneTable(tableIndex, error);

				if(printError(error)) {
					std::cout << CLONED_TABLE_MESSAGE << tableIndex << std::endl;
				}
			}
		}
		else if(command == EDIT_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, INVALID_TABLE_INDEX_MESSAGE)) { // read the first int
				int cellIndex;

				if(nextInt(inputStream, cellIndex, NO_SECOND_AND_THIRD_PARAMETER_MESSAGE, INVALID_CELL_INDEX_MESSAGE)) { // read the second int
					int value;

					if(nextInt(inputStream, value, NO_THIRD_PARAMETER_MESSAGE, INVALID_VALUE_MESSAGE)) { // read the third int
						table::Error error;
						tableContainer.editTable(tableIndex, cellIndex, value, error);

						if(printError(error)) {
							std::cout << CELL_VALUE_MESSAGE << cellIndex << OF_TABLE_MESSAGE << tableIndex << SET_TO_MESSAGE << value << std::endl;
						}
					}
				}
			}
		}
		else if(command == HELP_COMMAND) {
			std::cout << HELP_MESSAGE << std::endl;
		}
		else if(command == TEST_COMMAND) {
			int tableIndex;

			if(nextInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, INVALID_TABLE_INDEX_MESSAGE)) { // read an int
				// an int has been successfully loaded
				table::Error error;
				tableContainer.testTable(tableIndex, error);

				if(printError(error)) {
					std::cout << TESTED_TABLE_MESSAGE << tableIndex << std::endl;
				}
			}
		}
		else if(command != QUIT_COMMAND) {
			std::cout << INVALID_COMMAND_MESSAGE << std::endl;
		}
	}
}