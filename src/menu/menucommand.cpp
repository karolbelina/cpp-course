#include "menucommand.h"
#include "menu.h"
#include "constants.h"

#include <iostream>

MenuCommand::MenuCommand(std::string name, std::string commandString, Menu* parent, Command* command) : 
	MenuItem(name, commandString, parent), command(command) {}

MenuCommand::~MenuCommand() {
	delete command;
}

void MenuCommand::run() {
	if(command != nullptr) {
		command->runCommand();
	}
	else {
		std::cout << EMPTY_COMMAND_MESSAGE << std::endl;
	}
}

void MenuCommand::printLeaves() {
	std::cout << name << std::endl;
}