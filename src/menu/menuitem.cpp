#include "menuitem.h"
#include "menu.h"

MenuItem::MenuItem(const std::string name, const std::string commandString, Menu* parent) : 
	name(name), commandString(commandString), parent(parent) {}

MenuItem::~MenuItem() {}

std::string MenuItem::getName() const {
	return name;
}

std::string MenuItem::getCommand() const {
	return commandString;
}