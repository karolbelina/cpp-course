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
