#include "constants.h"
#include "menu.h"
#include "menuitem.h"

menu::MenuItem::MenuItem() {}

menu::MenuItem::MenuItem(const MenuItem &other) :
	name(other.name), commandString(other.commandString), parent(other.parent) {
}

menu::MenuItem::~MenuItem() {}

menu::MenuItem& menu::MenuItem::operator=(const MenuItem &other) {
	if(this == &other) {
		return *this;
	}

	name = other.name;
	commandString = other.commandString;
	parent = other.parent;

	return *this;
}

bool menu::MenuItem::parseElement(const std::string &source, size_t &position, std::string &destination, Error &error) {
	if(source[position] != APOSTROPHE) {
		error.syntaxError(position, APOSTROPHE);
		return false;
	}

	size_t beginPosition = ++position;

	while(source[position] != APOSTROPHE) {
		if(source[position] == NULL) { // end of string
			error.syntaxError(position, APOSTROPHE);
			return false;
		}

		++position;
	}

	destination = source.substr(beginPosition, position - beginPosition);
	++position;

	return true;
}

bool menu::MenuItem::parseCharacter(const std::string &source, size_t &position, const char character, Error &error) {
	if(source[position] != character) {
		error.syntaxError(position, character);
		return false;
	}

	++position;

	return true;
}

std::string menu::MenuItem::validateCommandString(const std::string commandString) {
	std::istringstream stream(commandString);
	std::string retVal;

	stream >> retVal;

	return retVal;
}

bool menu::MenuItem::checkKeywords(const std::string commandString) {
	if(commandString.empty() && parent != nullptr) { // root can be ''
		return false;
	}

	if(commandString == BACK_COMMAND || commandString == SEARCH_COMMAND || commandString == HELP_COMMAND) {
		return false;
	}

	return true;
}

bool menu::MenuItem::checkDuplicates(const std::string commandString) {
	if(parent == nullptr) {
		return true;
	}
	else {
		for(MenuItem* item : parent->items) {
			if(commandString == item->commandString) {
				return false;
			}
		}

		return true;
	}
}

std::string menu::MenuItem::exportItem(const MenuItem &item) {
	return item.exportItem();
}

menu::MenuItem* menu::MenuItem::importItem(const std::string &source, const Environment &environment, Error &error) {
	size_t position = 0;
	menu::MenuItem* item = nullptr;

	if(source[position] == LEFT_PARENTHESIS) {
		item = new menu::Menu(nullptr, source, position, environment, error);
	}
	else if(source[position] == LEFT_SQUARE_BRACKET) {
		item = new menu::MenuCommand(nullptr, source, position, environment, error);
	}
	else {
		error.syntaxError(position, {LEFT_PARENTHESIS, LEFT_SQUARE_BRACKET}); // expected ( or [
	}

	if(!error) {
		return item;
	}
	else {
		return nullptr;
	}
}