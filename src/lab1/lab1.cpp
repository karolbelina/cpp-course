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

	std::cout << TITLE_MESSAGE << std::endl;
	std::cout << HELP_MESSAGE << std::endl;

	while(input != QUIT_COMMAND) {
		std::cout << PROMPT_MESSAGE;

		std::getline(std::cin, input);
		std::istringstream inputStream(input);
		std::string command;

		inputStream >> command;

		if(command == CREATE_COMMAND) {
			int amount;

			if(inputStream >> amount) {
				int i = 0;

				while(i < amount) {
					int index = tableContainer.size();

					std::cout << ENTER_TABLE_NAME_MESSAGE << index << COLON << std::endl;
					std::cout << PROMPT_MESSAGE;

					std::getline(std::cin, input);
					inputStream.clear();
					inputStream.str(input);
					std::string name;

					inputStream >> name;

					std::cout << ENTER_TABLE_LENGTH_MESSAGE << index << COLON << std::endl;
					std::cout << PROMPT_MESSAGE;

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
		else if(command == REMOVE_COMMAND) {
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

				if(allFlag == ALL_COMMAND) {
					// usun wszystkie tabele
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

			if(inputStream >> tableIndex) {
				// wczytalo pierwsza liczbe
				int tableLength;

				if(inputStream >> tableLength) {
					// wczytalo druga liczbe
					Error error;
					tableContainer.resizeTable(tableIndex, tableLength, error);

					if(error == NoError) {
						std::cout << "the length of table #" << tableIndex << " has been set to " << tableLength << std::endl;
					}
					else if(error == IndexOutOfBounds) {
						std::cout << "table index out of bounds" << std::endl;
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
				else if(inputStream.eof()) {
					std::cout << "no second parameter" << std::endl;
				}
				else {
					std::cout << "invalid table length" << std::endl;
				}
			}
			else if(inputStream.eof()) {
				std::cout << "no parameters" << std::endl;
			}
			else {
				std::cout << "invalid table index" << std::endl;
			}
		}
		else if(command == RENAME_COMMAND) {
			int tableIndex;

			if(inputStream >> tableIndex) {
				// wczytalo liczbe
				std::string name;
				inputStream >> name;

				Error error;
				tableContainer.renameTable(tableIndex, name, error);

				if(error == NoError) {
					std::cout << "the name of table #" << tableIndex << " has been set to " << name << std::endl;
				}
				else if(error == IndexOutOfBounds) {
					std::cout << "table index out of bounds" << std::endl;
				}
				else {
					std::cout << "unknown error" << std::endl;
				}
			}
			else if(inputStream.eof()) {
				std::cout << "no parameters" << std::endl;
			}
			else {
				std::cout << "invalid table index" << std::endl;
			}
		}
		else if(command == STATUS_COMMAND) {
			int tableIndex;

			if(inputStream >> tableIndex) {
				// wczytalo liczbe
				Error error;
				std::string status = tableContainer.getTableStatus(tableIndex, error);

				if(error == NoError) {
					std::cout << status << std::endl;
				}
				else if(error == IndexOutOfBounds) {
					std::cout << "index out of bounds" << std::endl;
				}
				else {
					std::cout << "unknown error" << std::endl;
				}
			}
			else {
				// wczytalo nic ciekawego poza komenda
				std::cout << tableContainer.getStatus() << std::endl;
			}
		}
		else if(command == CLONE_COMMAND) {
			int tableIndex;

			if(inputStream >> tableIndex) {
				// wczytalo liczbe
				Error error;
				tableContainer.cloneTable(tableIndex, error);

				if(error == NoError) {
					std::cout << "table #" << tableIndex << " has been cloned successfully" << std::endl;
				}
				else if(error == IndexOutOfBounds) {
					std::cout << "table index out of bounds" << std::endl;
				}
				else if(error == OutOfMemory) {
					std::cout << "out of memory" << std::endl;
				}
				else {
					std::cout << "unknown error" << std::endl;
				}
			}
			else if(inputStream.eof()) {
				std::cout << "no parameters" << std::endl;
			}
			else {
				std::cout << "invalid table index" << std::endl;
			}
		}
		else if(command == EDIT_COMMAND) {
			int tableIndex;

			if(inputStream >> tableIndex) {
				// wczytalo pierwsza liczbe
				int cellIndex;

				if(inputStream >> cellIndex) {
					// wczytalo druga liczbe
					int value;

					if(inputStream >> value) {
						// wczytalo trzecia liczbe
						Error error;
						tableContainer.editTable(tableIndex, cellIndex, value, error);

						if(error == NoError) {
							std::cout << "the value of cell #" << cellIndex << " of table #" << tableIndex << " has been set to " << value << std::endl;
						}
						else if(error == IndexOutOfBounds) {
							std::cout << "index out of bounds" << std::endl;
						}
						else {
							std::cout << "unknown error" << std::endl;
						}
					}
					else if(inputStream.eof()) {
						std::cout << "no third parameter" << std::endl;
					}
					else {
						std::cout << "invalid value" << std::endl;
					}
				}
				else if(inputStream.eof()) {
					std::cout << "no second and third parameter" << std::endl;
				}
				else {
					std::cout << "invalid cell index" << std::endl;
				}
			}
			else if(inputStream.eof()) {
				std::cout << "no parameters" << std::endl;
			}
			else {
				std::cout << "invalid table index" << std::endl;
			}
		}
		else if(command == HELP_COMMAND) {
			std::cout << HELP_MESSAGE << std::endl;
		}
		else if(input != QUIT_COMMAND) {
			std::cout << "invalid command" << std::endl;
		}
	}
}