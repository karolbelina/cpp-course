#include "menucommand.h"
#include "menu.h"
#include "constants.h"

#include <iostream>

MenuCommand::MenuCommand(std::string name, std::string commandString, std::string help, Menu* parent, Command* command) : 
	MenuItem(name, commandString, parent), help(help), command(command) {}

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

bool MenuCommand::search(std::string &term, std::string path, std::ostream &stream) {
	std::string command = getCommand();

	if(term == command) {
		stream << path << command;

		return true;
	}

	return false;
}

bool MenuCommand::getHelp(std::string &destination) {
	destination = help;

	return true;
}
