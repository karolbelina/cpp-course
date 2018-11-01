#include "constants.h"
#include "menu.h"
#include "menuitem.h"

/*menu::MenuItem::MenuItem(const std::string name, const std::string commandString, Menu* parent) :
	name(name), commandString(commandString), parent(parent) {}*/

menu::MenuItem::MenuItem() {}

menu::MenuItem::~MenuItem() {}

/*MenuItem* MenuItem::importFromString(const std::string &source) { // CONST!!!!!!!1
	this->importFromString(source, 0);
}*/

menu::Menu* menu::MenuItem::getRoot() const {
	Menu* item = parent;

	while(item != nullptr) {
		item->parent;
	}

	return item;
}

bool menu::MenuItem::parseElement(const std::string &source, size_t &position, std::string &destination, Error &error) {
	if(source[position] != APOSTROPHE) {
		error.occur(position, APOSTROPHE);
		return false;
	}

	size_t beginPosition = ++position;

	while(source[position] != APOSTROPHE) {
		if(source[position] == NULL) { // end of string
			error.occur(position, APOSTROPHE);
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
		error.occur(position, character);
		return false;
	}

	++position;

	return true;
}
