#include "menuitem.h"

MenuItem::MenuItem(const std::string name, const std::string commandString) : name(name), commandString(commandString) {}

MenuItem::~MenuItem() {}

std::string MenuItem::getName() const {
	return name;
}

std::string MenuItem::getCommand() const {
	return commandString;
}