#include "constants.h"
#include "menu.h"
#include "menucommand.h"

#include <iostream>
#include <sstream>

menu::MenuCommand::MenuCommand(std::string name, std::string commandString, std::string help, Menu* parent, Command* command) :
	MenuItem(name, commandString, parent), help(help), command(command) {}

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

bool menu::MenuCommand::search(std::string &term, std::string path, std::ostream &stream) {
	std::string command = commandString;

	if(term == command) {
		stream << path << command;

		return true;
	}

	return false;
}

bool menu::MenuCommand::getHelp(std::string &destination) {
	destination = help;

	return true;
}

std::string menu::MenuCommand::exportItem() const {
	std::ostringstream stream;

	stream << LEFT_SQUARE_BRACKET << APOSTROPHE << name << APOSTROPHE << COMMA;
	stream << APOSTROPHE << commandString << APOSTROPHE << COMMA;
	stream << APOSTROPHE << help << APOSTROPHE << RIGHT_SQUARE_BRACKET;

	return stream.str();
}

/*MenuCommand* MenuCommand::importFromString(std::string &source, Error &error) {
	if(source[position] != LEFT_SQUARE_BRACKET) {
		// expected a [
		return;
	}

	++position;

	if(source[position] != APOSTROPHE) {
		// expected a '
		return;
	}

	size_t nameBeginPosition = ++position;

	while(source[position] != APOSTROPHE) {
		++position;
	}

	std::string name = source.substr(nameBeginPosition, position - nameBeginPosition);
	++position;

	if(source[position] != COMMA) {
		// expected a ,
		return;
	}

	++position;

	if(source[position] != APOSTROPHE) {
		// expected a '
		return;
	}

	size_t commandStringBeginPosition = ++position;

	while(source[position] != APOSTROPHE) {
		++position;
	}

	std::string commandString = source.substr(commandStringBeginPosition, position - commandStringBeginPosition);
	++position;

	if(source[position] != COMMA) {
		// expected a ,
		return;
	}

	++position;

	if(source[position] != APOSTROPHE) {
		// expected a '
		return;
	}

	size_t helpBeginPosition = ++position;

	while(source[position] != APOSTROPHE) {
		++position;
	}

	std::string help = source.substr(helpBeginPosition, position - helpBeginPosition);
	++position;

	if(source[position] != RIGHT_SQUARE_BRACKET) {
		// expected a ]
		return;
	}

	return new MenuCommand(name, commandString, help, parent, new Command());
}*/