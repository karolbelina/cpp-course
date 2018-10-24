#include "menu.h"
#include "menucommand.h"
#include "constants.h"

#include <iostream>
#include <string>

Menu::Menu(std::string name, std::string commandString) : MenuItem(name, commandString) {}

Menu::~Menu() {
	for(size_t i = 0, size = items.size(); i < size; i++) {
		delete items[i];
	}
}

bool Menu::addMenu(std::string name, std::string commandString) {
	if(checkCommandString(commandString)) {
		items.push_back(new Menu(name, commandString));

		return true;
	}

	return false;
}

bool Menu::addCommand(std::string name, std::string commandString, Command* command) {
	if(checkCommandString(commandString)) {
		items.push_back(new MenuCommand(name, commandString, command));

		return true;
	}

	return false;
}

bool Menu::removeItem(std::string commandString) {
	for(size_t i = 0, itemsSize = items.size(); i < itemsSize; i++) {
		if(commandString == items[i]->getCommand()) {
			delete items[i];
			items.erase(items.begin() + i);

			return true;
		}
	}

	return false;
}

void Menu::run() {
	bool retryInput = true;

	do {
		std::cout << std::endl << name << std::endl;
		std::cout << std::string(PADDING, SPACE) << BACK_COMMAND << std::endl;
		for(size_t i = 0, size = items.size(); i < size; i++) {
			std::cout << std::string(PADDING, SPACE);
			std::cout << items[i]->getName() << SPACE << OPEN_PARENTHESIS << items[i]->getCommand() << CLOSE_PARENTHESIS << std::endl;
		}
		std::cout << PROMPT << SPACE;

		std::string input;
		std::getline(std::cin, input);

		if(input != BACK_COMMAND) {
			bool foundValidCommand = false;

			for(size_t i = 0, size = items.size(); i < size; i++) {
				if(input == items[i]->getCommand()) {
					items[i]->run();

					foundValidCommand = true;
				}
			}

			if(!foundValidCommand) {
				std::cout << INVALID_COMMAND_MESSAGE << std::endl;
			}
		}
		else {
			retryInput = false;
		}
	} while(retryInput);
}

bool Menu::checkCommandString(std::string commandString) {
	if(commandString == EMPTY_STRING || commandString == BACK_COMMAND) {
		return false;
	}

	for(size_t i = 0, size = items.size(); i < size; i++) {
		if(commandString == items[i]->getCommand()) {
			return false;
		}
	}

	return true;
}
