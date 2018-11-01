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
	if(source[position] != LEFT_SQUARE_BRACKET) {
		error.occur(position, LEFT_SQUARE_BRACKET);
		return;
	}

	++position;

	if(source[position] != APOSTROPHE) {
		error.occur(position, APOSTROPHE);
		return;
	}

	size_t nameBeginPosition = ++position;

	while(source[position] != APOSTROPHE) {
		++position;
	}

	name = source.substr(nameBeginPosition, position - nameBeginPosition);
	++position;

	if(source[position] != COMMA) {
		error.occur(position, COMMA);
		return;
	}

	++position;

	if(source[position] != APOSTROPHE) {
		error.occur(position, APOSTROPHE);
		return;
	}

	size_t commandStringBeginPosition = ++position;

	while(source[position] != APOSTROPHE) {
		++position;
	}

	commandString = source.substr(commandStringBeginPosition, position - commandStringBeginPosition);
	++position;

	if(source[position] != COMMA) {
		error.occur(position, COMMA);
		return;
	}

	++position;

	if(source[position] != APOSTROPHE) {
		error.occur(position, APOSTROPHE);
		return;
	}

	size_t helpBeginPosition = ++position;

	while(source[position] != APOSTROPHE) {
		++position;
	}

	help = source.substr(helpBeginPosition, position - helpBeginPosition);
	++position;

	if(source[position] != RIGHT_SQUARE_BRACKET) {
		error.occur(position, RIGHT_SQUARE_BRACKET);
		return;
	}

	this->parent = parent;
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