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