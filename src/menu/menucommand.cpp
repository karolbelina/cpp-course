#include "constants.h"
#include "menu.h"
#include "menucommand.h"

#include <iostream>
#include <sstream>

/*menu::MenuCommand::MenuCommand(std::string name, std::string commandString, std::string help, Menu* parent, Command* command) :
	MenuItem(name, commandString, parent), help(help), command(command) {}*/

menu::MenuCommand::~MenuCommand() {
	delete command;
}

void menu::MenuCommand::run() {
	if(command != nullptr) {
		command->runCommand();
	}
	else {
		std::cout << EMPTY_COMMAND_MESSAGE << std::endl;
	}
}

menu::MenuCommand::MenuCommand(Menu* parent, const std::string &source, size_t &position, Error &error) {
	this->parent = parent;

	if(!parseCharacter(source, position, LEFT_SQUARE_BRACKET, error) ||
		!parseElement(source, position, name, error) ||
		!parseCharacter(source, position, COMMA, error) ||
		!parseElement(source, position, commandString, error) ||
		!parseCharacter(source, position, COMMA, error) ||
		!parseElement(source, position, help, error) ||
		!parseCharacter(source, position, RIGHT_SQUARE_BRACKET, error)) {
		return;
	}

	command = new Command();
}

bool menu::MenuCommand::search(std::string &term, std::string path, std::ostream &stream) {
	std::string command = commandString;

	if(term == command) {
		stream << path << command;

		return true;
	}

	return false;
}

std::string menu::MenuCommand::getHelp() const {
	return help;
}

std::string menu::MenuCommand::exportItem() const {
	std::ostringstream stream;

	stream << LEFT_SQUARE_BRACKET << APOSTROPHE << name << APOSTROPHE << COMMA;
	stream << APOSTROPHE << commandString << APOSTROPHE << COMMA;
	stream << APOSTROPHE << help << APOSTROPHE << RIGHT_SQUARE_BRACKET;

	return stream.str();
}