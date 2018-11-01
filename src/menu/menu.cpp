#include "constants.h"
#include "menu.h"
#include "menucommand.h"

#include <iostream>
#include <sstream>
#include <string>

menu::Menu::Menu() : MenuItem("main", "", nullptr) {}

menu::Menu::Menu(const std::string name, const std::string commandString, Menu* parent) : MenuItem(name, commandString, parent) {}

menu::Menu::~Menu() {
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		delete *i;
	}
}

menu::Menu* menu::Menu::addMenu(const std::string name, const std::string commandString) {
	const std::string validatedCommandString = validateCommandString(commandString);

	if(checkKeywords(validatedCommandString) && checkDuplicates(validatedCommandString)) {
		Menu* menu = new Menu(name, validatedCommandString, this);
		items.push_back(menu);

		return menu;
	}

	return nullptr;
}

menu::MenuCommand* menu::Menu::addCommand(const std::string name, const std::string commandString, const std::string help, Command* command) {
	const std::string validatedCommandString = validateCommandString(commandString);

	if(checkKeywords(validatedCommandString) && checkDuplicates(validatedCommandString)) {
		MenuCommand* menuCommand = new MenuCommand(name, validatedCommandString, help, this, command);
		items.push_back(menuCommand);

		return menuCommand;
	}

	return nullptr;
}

bool menu::Menu::removeItem(const std::string commandString) {
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		if(commandString == (*i)->commandString) {
			delete *i;
			items.erase(i);

			return true;
		}
	}

	return false;
}

bool menu::Menu::search(std::string &term, const std::string path, std::ostream &stream) {
	std::string currentPath = path + commandString + "/";
	bool foundCommands = false;

	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		if((*i)->search(term, currentPath, stream)) {
			stream << std::endl; // separator
			foundCommands = true;
		}
	}

	return foundCommands;
}

// zwroc pustego stringa
bool menu::Menu::getHelp(std::string &destination) {
	return false;
}

std::string menu::Menu::exportToString() {
	std::ostringstream stream;

	stream << LEFT_PARENTHESIS << APOSTROPHE << name << APOSTROPHE << COMMA;
	stream << APOSTROPHE << commandString << APOSTROPHE << SEMICOLON;

	std::string separator = "";
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		stream << separator << (*i)->exportToString();
		separator = COMMA;
	}

	stream << RIGHT_PARENTHESIS;

	return stream.str();
}

void menu::Menu::run() {
	bool retryInput = true;

	do {
		std::cout << std::endl << name << std::endl;
		std::cout << std::string(PADDING, SPACE);
		std::cout << BACK_COMMAND_NAME << SPACE << LEFT_PARENTHESIS << BACK_COMMAND_STRING << RIGHT_PARENTHESIS << std::endl;
		for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
			std::cout << std::string(PADDING, SPACE);
			std::cout << (*i)->name << SPACE << LEFT_PARENTHESIS << (*i)->commandString << RIGHT_PARENTHESIS << std::endl;
		}
		std::cout << std::string(PADDING, SPACE);
		std::cout << PRINT_LEAVES_COMMAND_NAME << SPACE << LEFT_PARENTHESIS << PRINT_LEAVES_COMMAND_STRING << RIGHT_PARENTHESIS << std::endl;
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
					if(input == (*i)->commandString) {
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

bool menu::Menu::checkKeywords(const std::string commandString) {
	// TODO: also check if the commandString contains any apostophes

	if(commandString == EMPTY_STRING || commandString == BACK_COMMAND_STRING) {
		return false;
	}

	return true;
}

bool menu::Menu::checkDuplicates(const std::string commandString) {
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		if(commandString == (*i)->commandString) {
			return false;
		}
	}

	return true;
}

std::string menu::Menu::validateCommandString(const std::string commandString) {
	std::istringstream stream(commandString);
	std::string retVal;

	stream >> retVal;

	return retVal;
}