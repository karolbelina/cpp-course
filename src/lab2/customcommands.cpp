#include "customcommands.h"
#include "error.h"

#include <iostream>
#include <sstream>

CustomCommand::CustomCommand(TableContainer* tableContainer) : Command(), tableContainer(tableContainer) {}

void CustomCommand::getString(std::string &destination) {
	std::cout << "> ";

	std::getline(std::cin, destination);
}

bool CustomCommand::getInt(int &destination) {
	std::cout << "> ";

	std::string input;
	std::getline(std::cin, input);
	std::istringstream stream(input);

	return (bool)(stream >> destination);
}

CreateCommand::CreateCommand(TableContainer* tableContainer) : CustomCommand(tableContainer) {}

void CreateCommand::runCommand() {
	std::cout << "enter the amount:" << std::endl;

	int amount;

	if(getInt(amount)) {
		int i = 0;

		if(amount > 0) {
			while(i < amount) {
				int index = tableContainer->size();

				std::cout << "enter the name of table #" << index << ":" << std::endl;

				std::string name;
				getString(name);

				std::cout << "enter the length of table #" << index << ":" << std::endl;

				int length;

				if(getInt(length)) {
					Error error;
					tableContainer->addTable(name, length, error);

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
		else {
			std::cout << "invalid amount" << std::endl;
		}
	}
	else {
		std::cout << "invalid amount" << std::endl;
	}
}

RemoveCommand::RemoveCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void RemoveCommand::runCommand() {
	std::cout << "enter the table index:" << std::endl;

	int tableIndex;

	if(getInt(tableIndex)) {
		// wczytalo liczbe
		// usun tabele o numerze
		Error error;
		tableContainer->removeTable(tableIndex, error);

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
	else {
		std::cout << "invalid table index" << std::endl;
	}
}

RemoveAllCommand::RemoveAllCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void RemoveAllCommand::runCommand() {
	tableContainer->removeAllTables();

	std::cout << "removed all tables" << std::endl;
}

ResizeCommand::ResizeCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void ResizeCommand::runCommand() {
	std::cout << "enter the table index:" << std::endl;

	int tableIndex;

	if(getInt(tableIndex)) {
		// wczytalo pierwsza liczbe
		std::cout << "enter the table length:" << std::endl;

		int tableLength;

		if(getInt(tableLength)) {
			// wczytalo druga liczbe
			Error error;
			tableContainer->resizeTable(tableIndex, tableLength, error);

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
		else {
			std::cout << "invalid table length" << std::endl;
		}
	}
	else {
		std::cout << "invalid table index" << std::endl;
	}
}

RenameCommand::RenameCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void RenameCommand::runCommand() {
	std::cout << "enter the table index:" << std::endl;

	int tableIndex;

	if(getInt(tableIndex)) {
		// wczytalo liczbe
		std::cout << "enter the table name:" << std::endl;

		std::string name;
		getString(name);

		Error error;
		tableContainer->renameTable(tableIndex, name, error);

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
	else {
		std::cout << "invalid table index" << std::endl;
	}
}

StatusCommand::StatusCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void StatusCommand::runCommand() {
	std::cout << "enter the table index:" << std::endl;

	int tableIndex;

	if(getInt(tableIndex)) {
		// wczytalo liczbe
		Error error;
		std::string status = tableContainer->getTableStatus(tableIndex, error);

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
		std::cout << "invalid table index" << std::endl;
	}
}

StatusAllCommand::StatusAllCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void StatusAllCommand::runCommand() {
	std::cout << tableContainer->getStatus() << std::endl;
}

CloneCommand::CloneCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void CloneCommand::runCommand() {
	std::cout << "enter the table index:" << std::endl;

	int tableIndex;

	if(getInt(tableIndex)) {
		// an int has been successfully loaded
		Error error;
		tableContainer->cloneTable(tableIndex, error);

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
	else {
		std::cout << "invalid table index" << std::endl;
	}
}

EditCommand::EditCommand(TableContainer* tableContainer): CustomCommand(tableContainer) {}

void EditCommand::runCommand() {
	std::cout << "enter the table index:" << std::endl;

	int tableIndex;

	if(getInt(tableIndex)) {
		std::cout << "enter the cell length:" << std::endl;
		std::cout << "> ";

		int cellIndex;

		if(getInt(cellIndex)) {
			std::cout << "enter the value:" << std::endl;
			std::cout << "> ";

			int value;

			if(getInt(value)) {
				// success
				Error error;
				tableContainer->editTable(tableIndex, cellIndex, value, error);

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
			else {
				std::cout << "invalid value" << std::endl;
			}
		}
		else {
			std::cout << "invalid cell index" << std::endl;
		}
	}
	else {
		std::cout << "invalid table index" << std::endl;
	}
}