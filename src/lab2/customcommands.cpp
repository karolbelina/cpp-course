#include "customcommands.h"
#include "error.h"
#include "constants.h"

#include <iostream>
#include <sstream>

static void getStringFromUserInput(std::string &destination) {
	std::cout << PROMPT << SPACE;

	std::getline(std::cin, destination);
}

static bool getIntFromUserInput(int &destination) {
	std::cout << PROMPT << SPACE;

	std::string input;
	std::getline(std::cin, input);
	std::istringstream stream(input);

	return static_cast<bool>(stream >> destination);
}

CustomCommand::CustomCommand(TableContainer* tableContainer) : Command(), tableContainer(tableContainer) {}

CreateCommand::CreateCommand(TableContainer* tableContainer) : CustomCommand(tableContainer) {}

void CreateCommand::runCommand() {
	std::cout << ENTER_THE_AMOUNT_MESSAGE << COLON << std::endl;

	int amount;

	if(getIntFromUserInput(amount)) {
		int i = 0;

		if(amount > 0) {
			while(i < amount) {
				int index = tableContainer->size();

				std::cout << ENTER_THE_NAME_OF_TABLE_MESSAGE << SPACE << HASH << index << COLON << std::endl;

				std::string name;
				getStringFromUserInput(name);

				std::cout << ENTER_THE_LENGTH_OF_TABLE_MESSAGE << SPACE << HASH << index << COLON << std::endl;

				int length;

				if(getIntFromUserInput(length)) {
					Error error;
					tableContainer->addTable(name, length, error);

					if(error == NoError) {
						i++;
						std::cout << TABLE_CREATED_SUCCESSFULLY_MESSAGE << std::endl;
					}
					else if(error == InvalidArgument) {
						std::cout << LENGTH_CANNOT_BE_NEGATIVE_MESSAGE << std::endl;
					}
					else if(error == OutOfMemory) {
						std::cout << OUT_OF_MEMORY_MESSAGE << std::endl;
					}
					else {
						std::cout << UNKNOWN_ERROR_MESSAGE << std::endl;
					}
				}
				else {
					std::cout << INVALID_TABLE_LENGTH_MESSAGE << std::endl;
				}
			}
		}
		else {
			std::cout << AMOUNT_CANNOT_BE_NEGATIVE_MESSAGE << std::endl;
		}
	}
	else {
		std::cout << INVALID_AMOUNT_MESSAGE << std::endl;
	}
}

RemoveCommand::RemoveCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void RemoveCommand::runCommand() {
	std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

	int tableIndex;

	if(getIntFromUserInput(tableIndex)) {
		// wczytalo liczbe
		// usun tabele o numerze
		Error error;
		tableContainer->removeTable(tableIndex, error);

		if(error == NoError) {
			std::cout << REMOVED_TABLE_MESSAGE << SPACE << HASH << tableIndex << std::endl;
		}
		else if(error == IndexOutOfBounds) {
			std::cout << INDEX_OUT_OF_BOUNDS_MESSAGE << std::endl;
		}
		else {
			std::cout << UNKNOWN_ERROR_MESSAGE << std::endl;
		}
	}
	else {
		std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
	}
}

RemoveAllCommand::RemoveAllCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void RemoveAllCommand::runCommand() {
	tableContainer->removeAllTables();

	std::cout << REMOVED_ALL_TABLES_MESSAGE << std::endl;
}

ResizeCommand::ResizeCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void ResizeCommand::runCommand() {
	std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

	int tableIndex;

	if(getIntFromUserInput(tableIndex)) {
		// wczytalo pierwsza liczbe
		std::cout << ENTER_THE_TABLE_LENGTH_MESSAGE << COLON << std::endl;

		int tableLength;

		if(getIntFromUserInput(tableLength)) {
			// wczytalo druga liczbe
			Error error;
			tableContainer->resizeTable(tableIndex, tableLength, error);

			if(error == NoError) {
				std::cout << THE_LENGTH_OF_TABLE_MESSAGE << SPACE << HASH << tableIndex << SPACE << HAS_BEEN_SET_TO_MESSAGE << SPACE << tableLength << std::endl;
			}
			else if(error == IndexOutOfBounds) {
				std::cout << INDEX_OUT_OF_BOUNDS_MESSAGE << std::endl;
			}
			else if(error == InvalidArgument) {
				std::cout << LENGTH_CANNOT_BE_NEGATIVE_MESSAGE << std::endl;
			}
			else if(error == OutOfMemory) {
				std::cout << OUT_OF_MEMORY_MESSAGE << std::endl;
			}
			else {
				std::cout << UNKNOWN_ERROR_MESSAGE << std::endl;
			}
		}
		else {
			std::cout << INVALID_TABLE_LENGTH_MESSAGE << std::endl;
		}
	}
	else {
		std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
	}
}

RenameCommand::RenameCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void RenameCommand::runCommand() {
	std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

	int tableIndex;

	if(getIntFromUserInput(tableIndex)) {
		// wczytalo liczbe
		std::cout << ENTER_THE_TABLE_NAME_MESSAGE << COLON << std::endl;

		std::string name;
		getStringFromUserInput(name);

		Error error;
		tableContainer->renameTable(tableIndex, name, error);

		if(error == NoError) {
			std::cout << THE_NAME_OF_TABLE_MESSAGE << SPACE << HASH << tableIndex << SPACE << HAS_BEEN_SET_TO_MESSAGE << SPACE << name << std::endl;
		}
		else if(error == IndexOutOfBounds) {
			std::cout << INDEX_OUT_OF_BOUNDS_MESSAGE << std::endl;
		}
		else {
			std::cout << UNKNOWN_ERROR_MESSAGE << std::endl;
		}
	}
	else {
		std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
	}
}

StatusCommand::StatusCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void StatusCommand::runCommand() {
	std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

	int tableIndex;

	if(getIntFromUserInput(tableIndex)) {
		// wczytalo liczbe
		Error error;
		std::string status = tableContainer->getTableStatus(tableIndex, error);

		if(error == NoError) {
			std::cout << status << std::endl;
		}
		else if(error == IndexOutOfBounds) {
			std::cout << INDEX_OUT_OF_BOUNDS_MESSAGE << std::endl;
		}
		else {
			std::cout << UNKNOWN_ERROR_MESSAGE << std::endl;
		}
	}
	else {
		std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
	}
}

StatusAllCommand::StatusAllCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void StatusAllCommand::runCommand() {
	std::cout << tableContainer->getStatus() << std::endl;
}

CloneCommand::CloneCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void CloneCommand::runCommand() {
	std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

	int tableIndex;

	if(getIntFromUserInput(tableIndex)) {
		// an int has been successfully loaded
		Error error;
		tableContainer->cloneTable(tableIndex, error);

		if(error == NoError) {
			std::cout << CLONED_TABLE_MESSAGE << SPACE << HASH << tableIndex << std::endl;
		}
		else if(error == IndexOutOfBounds) {
			std::cout << INDEX_OUT_OF_BOUNDS_MESSAGE << std::endl;
		}
		else if(error == OutOfMemory) {
			std::cout << OUT_OF_MEMORY_MESSAGE << std::endl;
		}
		else {
			std::cout << UNKNOWN_ERROR_MESSAGE << std::endl;
		}
	}
	else {
		std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
	}
}

EditCommand::EditCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void EditCommand::runCommand() {
	std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

	int tableIndex;

	if(getIntFromUserInput(tableIndex)) {
		std::cout << ENTER_THE_CELL_INDEX_MESSAGE << COLON << std::endl;

		int cellIndex;

		if(getIntFromUserInput(cellIndex)) {
			std::cout << ENTER_THE_VALUE_MESSAGE << COLON << std::endl;

			int value;

			if(getIntFromUserInput(value)) {
				// success
				Error error;
				tableContainer->editTable(tableIndex, cellIndex, value, error);

				if(error == NoError) {
					std::cout << THE_VALUE_OF_CELL_MESSAGE << SPACE << HASH << cellIndex << SPACE << OF_TABLE_MESSAGE << SPACE << HASH;
					std::cout << tableIndex << SPACE << HAS_BEEN_SET_TO_MESSAGE << SPACE << value << std::endl;
				}
				else if(error == IndexOutOfBounds) {
					std::cout << INDEX_OUT_OF_BOUNDS_MESSAGE << std::endl;
				}
				else {
					std::cout << UNKNOWN_ERROR_MESSAGE << std::endl;
				}
			}
			else {
				std::cout << INVALID_VALUE_MESSAGE << std::endl;
			}
		}
		else {
			std::cout << INVALID_CELL_INDEX_MESSAGE << std::endl;
		}
	}
	else {
		std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
	}
}