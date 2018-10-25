#include "menu.h"
#include "menucommand.h"
#include "constants.h"

#include <algorithm>
#include <iostream>
#include <string>

Menu::Menu(std::string name, std::string commandString) : MenuItem(name, commandString) {}

Menu::~Menu() {
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		delete *i;
	}
}

bool Menu::addMenu(std::string name, std::string commandString) {
	if(checkCommandString(commandString)) {
		Menu* menu = new Menu(name, commandString);
		items.push_back(menu);
		menus.push_back(menu);

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
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		if(commandString == (*i)->getCommand()) {
			for(std::vector<Menu*>::iterator j = menus.begin(); j != menus.end(); ++j) {
				if(*i == *j) {
					menus.erase(j);
				}
			}

			delete *i;
			items.erase(i);

			return true;
		}
	}

	return false;
}

Menu* Menu::getMenu(std::string commandString) {
	for(std::vector<Menu*>::iterator i = menus.begin(); i != menus.end(); ++i) {
		if(commandString == (*i)->getCommand()) {
			return *i;
		}
	}
	return NULL;
}

void Menu::printLeaves() {
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		(*i)->printLeaves();
	}
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
		std::cout << std::string(PADDING, SPACE);
		std::cout << PRINT_LEAVES_COMMAND_NAME << SPACE << OPENING_PARENTHESIS << PRINT_LEAVES_COMMAND_STRING << CLOSING_PARENTHESIS << std::endl;
		std::cout << PROMPT << SPACE;

		std::string input;
		std::getline(std::cin, input);

		if(input != BACK_COMMAND_STRING) {
			bool foundValidCommand = false;

			if(input == PRINT_LEAVES_COMMAND_STRING) {
				printLeaves();

				foundValidCommand = true;
			}
			else {
				for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
					if(input == (*i)->getCommand()) {
						(*i)->run();

						foundValidCommand = true;
					}
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

	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		if(commandString == (*i)->getCommand()) {
			return false;
		}
	}

	return true;
}
