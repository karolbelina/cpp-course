#include "constants.h"
#include "menu.h"
#include "menucommand.h"

#include <iostream>
#include <sstream>
#include <string>

menu::Menu::Menu(const Menu &other) : MenuItem(other) {
	for(MenuItem* item : other.items) {
		items.push_back(item->clone());
	}
}

menu::Menu::~Menu() {
	for(MenuItem* item : items) {
		delete item;
	}
}

menu::Menu& menu::Menu::operator=(const Menu &other) {
	if(this == &other) {
		return *this;
	}

	MenuItem::operator=(other);

	for(MenuItem* item : items) {
		delete item;
	}

	items.clear();

	for(MenuItem* item : other.items) {
		items.push_back(item->clone());
	}

	return *this;
}

menu::MenuItem* menu::Menu::clone() const {
	return new Menu(*this);
}

bool menu::Menu::search(std::string &term, const std::string path, std::ostream &stream) {
	std::string currentPath = path + commandString + "/";
	bool foundCommands = false;

	for(MenuItem* item : items) {
		if(item->search(term, currentPath, stream)) {
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
	for(MenuItem* item : items) {
		stream << separator << item->exportItem();
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
		for(MenuItem* item : items) {
			std::cout << std::string(PADDING, SPACE);
			std::cout << item->name << SPACE << LEFT_PARENTHESIS << item->commandString << RIGHT_PARENTHESIS << std::endl;
		}
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
				for(MenuItem* item : items) {
					if(input == item->commandString) {
						item->run();

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

menu::Menu::Menu(Menu* parent, const std::string &source, size_t &position, const Environment &environment, Error &error) {
	this->parent = parent;
	std::string temporaryCommandString;

	if(!parseCharacter(source, position, LEFT_PARENTHESIS, error)) {
		return;
	}

	if(!parseElement(source, position, name, error)) {
		return;
	}

	if(!parseCharacter(source, position, COMMA, error)) {
		return;
	}

	if(!parseElement(source, position, temporaryCommandString, error)) {
		return;
	}

	commandString = validateCommandString(temporaryCommandString);

	if(!checkKeywords(commandString)) {
		error.invalidElementError(position - 1);
		return;
	}

	if(!checkDuplicates(commandString)) {
		error.duplicateElementError(position - 1);
		return;
	}

	if(!parseCharacter(source, position, SEMICOLON, error)) {
		return;
	}

	while(source[position] == LEFT_PARENTHESIS || source[position] == LEFT_SQUARE_BRACKET) {
		if(source[position] == LEFT_PARENTHESIS) {
			MenuItem* item = new Menu(this, source, position, environment, error);

			if(error) {
				return;
			}

			items.push_back(item);
		}
		else if(source[position] == LEFT_SQUARE_BRACKET) {
			MenuItem* item = new MenuCommand(this, source, position, environment, error);

			if(error) {
				return;
			}

			items.push_back(item);
		}

		if(source[position] == RIGHT_PARENTHESIS) {
			++position;
			return;
		}
		else if(source[position] == COMMA) {
			++position;
		}
		else {
			error.syntaxError(position, {RIGHT_PARENTHESIS, COMMA}); // expected ) or ,
			return;
		}

		if(source[position] != LEFT_PARENTHESIS && source[position] != LEFT_SQUARE_BRACKET) {
			error.syntaxError(position, {LEFT_PARENTHESIS, LEFT_SQUARE_BRACKET}); // expected ( or [
			return;
		}
	}

	if(source[position] == RIGHT_PARENTHESIS) {
		++position;
		return;
	}
	else {
		error.syntaxError(position, {RIGHT_PARENTHESIS, LEFT_PARENTHESIS, LEFT_SQUARE_BRACKET}); // expected ), ( or [
		return;
	}
}