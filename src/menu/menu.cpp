#include "menu.h"
#include "menucommand.h"
#include "constants.h"

#include <algorithm>
#include <iostream>
#include <string>

Menu::Menu(std::string name, std::string commandString) : MenuItem(name, commandString) {}

Menu::~Menu() {
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); i++) {
		delete *i;
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
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); i++) {
		if(commandString == (*i)->getCommand()) {
			delete *i;
			items.erase(i);

			return true;
		}
	}

	return false;
}

void Menu::run() {
	bool retryInput = true;

	do {
		std::cout << std::endl << name << std::endl;
		std::cout << std::string(PADDING, SPACE);
		std::cout << BACK_COMMAND_NAME << SPACE << OPENING_PARENTHESIS << BACK_COMMAND_STRING << CLOSING_PARENTHESIS << std::endl;
		for(size_t i = 0; i < items.size(); i++) {
			std::cout << std::string(PADDING, SPACE);
			std::cout << items[i]->getName() << SPACE << OPENING_PARENTHESIS << items[i]->getCommand() << CLOSING_PARENTHESIS << std::endl;
		}
		std::cout << PROMPT << SPACE;

		std::string input;
		std::getline(std::cin, input);

		if(input != BACK_COMMAND_STRING) {
			bool foundValidCommand = false;

			for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); i++) {
				if(input == (*i)->getCommand()) {
					(*i)->run();

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
	if(commandString == EMPTY_STRING || commandString == BACK_COMMAND_STRING) {
		return false;
	}

	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); i++) {
		if(commandString == (*i)->getCommand()) {
			return false;
		}
	}

	return true;
}
