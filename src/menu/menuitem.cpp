#include "menuitem.h"

MenuItem::MenuItem(std::string name, std::string commandString) : name(name), commandString(commandString) {}

std::string MenuItem::getName() const {
	return name;
}

std::string MenuItem::getCommand() const {
	return commandString;
}