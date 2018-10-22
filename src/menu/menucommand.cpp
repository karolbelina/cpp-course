#include "menucommand.h"
#include "constants.h"

#include <iostream>

MenuCommand::MenuCommand(std::string name, std::string commandString, Command* command) : MenuItem(name, commandString), command(command) {}

void MenuCommand::run() {
	if(command != NULL) {
		command->runCommand();
	}
	else {
		std::cout << EMPTY_COMMAND_MESSAGE << std::endl;
	}
}