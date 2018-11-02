#include "constants.h"
#include "menu.h"
#include "menucommand.h"

#include <iostream>
#include <sstream>
#include <string>

menu::Menu::Menu() : MenuItem() {
	name = "main";
	commandString = "";
	parent = nullptr;
}

/*menu::Menu::Menu(const std::string name, const std::string commandString, Menu* parent) : MenuItem(name, commandString, parent) {}*/

menu::Menu::~Menu() {
	for(std::vector<MenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
		delete *i;
	}
}

/*menu::Menu* menu::Menu::addMenu(const std::string name, const std::string commandString) {
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
}*/

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

std::string menu::Menu::getHelp() const {
	return std::string();
}

std::string menu::Menu::exportItem() const {
	std::ostringstream stream;

	stream << LEFT_PARENTHESIS << APOSTROPHE << name << APOSTROPHE << COMMA;
	stream << APOSTROPHE << commandString << APOSTROPHE << SEMICOLON;

	std::string separator = std::string();
	for(std::vector<MenuItem*>::const_iterator i = items.begin(); i != items.end(); ++i) {
		stream << separator << (*i)->exportItem();
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

menu::Menu::Menu(Menu* parent, const std::string &source, size_t &position, const std::map<std::string, std::unique_ptr<menu::Command>> &environment, Error &error) {
	this->parent = parent;

	if(source[position] != LEFT_PARENTHESIS) {
		error.occur(position, LEFT_PARENTHESIS);
		return;
	}
	++position;

	if(!parseElement(source, position, name, error)) {
		return;
	}

	if(source[position] != COMMA) {
		error.occur(position, COMMA);
		return;
	}
	++position;

	if(!parseElement(source, position, commandString, error)) {
		return;
	}

	if(source[position] != SEMICOLON) {
		error.occur(position, SEMICOLON);
		return;
	}
	++position;

	if(source[position] == RIGHT_PARENTHESIS) {
		++position;
		return;
	}

	while(source[position] == LEFT_PARENTHESIS || source[position] == LEFT_SQUARE_BRACKET) {
		if(source[position] == LEFT_PARENTHESIS) { // menu
			MenuItem* item = new Menu(this, source, position, environment, error);

			if(error.occured) {
				return;
			}

			items.push_back(item);
		}
		else if(source[position] == LEFT_SQUARE_BRACKET) { // menucommand
			MenuItem* item = new MenuCommand(this, source, position, environment, error);

			if(error.occured) {
				return;
			}

			items.push_back(item);
		}
		else {
			error.occur(position, RIGHT_PARENTHESIS); // expected ( or [
			return;
		}

		if(source[position] == RIGHT_PARENTHESIS) {
			++position;
			return;
		}
		else if(source[position] != COMMA) {
			error.occur(position, COMMA); // expected ) or ,
			return;
		}
		++position;
	}
}

std::string menu::Menu::validateCommandString(const std::string commandString) {
	std::istringstream stream(commandString);
	std::string retVal;

	stream >> retVal;

	return retVal;
}