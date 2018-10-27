#include "menu.h"
#include "menucommand.h"
#include "constants.h"

#include <iostream>
#include <string>
#include <sstream>

Menu::Menu() : MenuItem("main", "", nullptr) {}

Menu::Menu(const std::string name, const std::string commandString, Menu* parent) : MenuItem(name, commandString, parent) {}

Menu::~Menu() {
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		delete *i;
	}
}

Menu* Menu::addMenu(const std::string name, const std::string commandString) {
	const std::string validatedCommandString = validateCommandString(commandString);

	if(checkKeywords(validatedCommandString) && checkDuplicates(validatedCommandString)) {
		Menu* menu = new Menu(name, validatedCommandString, this);
		items.push_back(menu);

		return menu;
	}

	return nullptr;
}

MenuCommand* Menu::addCommand(const std::string name, const std::string commandString, const std::string help, Command* command) {
	const std::string validatedCommandString = validateCommandString(commandString);

	if(checkKeywords(validatedCommandString) && checkDuplicates(validatedCommandString)) {
		MenuCommand* menuCommand = new MenuCommand(name, validatedCommandString, help, this, command);
		items.push_back(menuCommand);

		return menuCommand;
	}

	return nullptr;
}

bool Menu::removeItem(const std::string commandString) {
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		if(commandString == (*i)->getCommand()) {
			delete *i;
			items.erase(i);

			return true;
		}
	}

	return false;
}

bool Menu::search(std::string &term, const std::string path, std::ostream &stream) {
	std::string currentPath = path + getCommand() + "/";
	bool foundCommands = false;

	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		if((*i)->search(term, currentPath, stream)) {
			stream << std::endl; // separator
			foundCommands = true;
		}
	}

	return foundCommands;
}

bool Menu::getHelp(std::string &destination) {
	return false;
}

void Menu::run() {
	bool retryInput = true;

	do {
		std::cout << std::endl << name << std::endl;
		std::cout << std::string(PADDING, SPACE);
		std::cout << BACK_COMMAND_NAME << SPACE << OPENING_PARENTHESIS << BACK_COMMAND_STRING << CLOSING_PARENTHESIS << std::endl;
		for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
			std::cout << std::string(PADDING, SPACE);
			std::cout << (*i)->getName() << SPACE << OPENING_PARENTHESIS << (*i)->getCommand() << CLOSING_PARENTHESIS << std::endl;
		}
		std::cout << std::string(PADDING, SPACE);
		std::cout << PRINT_LEAVES_COMMAND_NAME << SPACE << OPENING_PARENTHESIS << PRINT_LEAVES_COMMAND_STRING << CLOSING_PARENTHESIS << std::endl;
		std::cout << PROMPT << SPACE;

		std::string input;
		std::getline(std::cin, input);

		if(input != BACK_COMMAND_STRING) {
			bool foundValidCommand = false;

			if(input == PRINT_LEAVES_COMMAND_STRING) {
				//printLeaves();

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

bool Menu::checkKeywords(const std::string commandString) {
	if(commandString == EMPTY_STRING || commandString == BACK_COMMAND_STRING) {
		return false;
	}

	return true;
}

bool Menu::checkDuplicates(const std::string commandString) {
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		if(commandString == (*i)->getCommand()) {
			return false;
		}
	}

	return true;
}

std::string Menu::validateCommandString(const std::string commandString) {
	std::istringstream stream(commandString);
	std::string retVal;

	stream >> retVal;

	return retVal;
}
