#include "menuitem.h"
#include "menu.h"

menu::MenuItem::MenuItem(const std::string name, const std::string commandString, Menu* parent) :
	name(name), commandString(commandString), parent(parent) {}

menu::MenuItem::~MenuItem() {}

/*MenuItem* MenuItem::importFromString(const std::string &source) { // CONST!!!!!!!1
	this->importFromString(source, 0);
}*/

std::string menu::MenuItem::getName() const {
	return name;
}

std::string menu::MenuItem::getCommand() const {
	return commandString;
}

menu::Menu* menu::MenuItem::getParent() const {
	return parent;
}

menu::Menu* menu::MenuItem::getRoot() const {
	Menu* item = getParent();

	while(item != nullptr) {
		item->getParent();
	}

	return item;
}