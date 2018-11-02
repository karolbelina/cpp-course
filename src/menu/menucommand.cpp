#include "constants.h"
#include "menu.h"
#include "menucommand.h"

#include <iostream>
#include <sstream>

menu::MenuCommand::MenuCommand(const MenuCommand &other) : MenuItem(other), help(other.help), command(other.command->clone()) {}

menu::MenuCommand::~MenuCommand() {
	delete command;
}

menu::MenuCommand& menu::MenuCommand::operator=(const MenuCommand &other) {
	if(this == &other) {
		return *this;
	}

	MenuItem::operator=(other);

	help = other.help;
	command = other.command->clone();

	return *this;
}

menu::MenuItem* menu::MenuCommand::clone() const {
	return new MenuCommand(*this);
}

void menu::MenuCommand::run() {
	if(command != nullptr) {
		command->runCommand();
	}
	else {
		std::cout << EMPTY_COMMAND_MESSAGE << std::endl;
	}
}

menu::MenuCommand::MenuCommand(Menu* parent, const std::string &source, size_t &position, const Environment &environment, Error &error) {
	this->parent = parent;
	std::string environmentKey;

	if(!parseCharacter(source, position, LEFT_SQUARE_BRACKET, error) ||
		!parseElement(source, position, name, error) ||
		!parseCharacter(source, position, COMMA, error) ||
		!parseElement(source, position, commandString, error) ||
		!parseCharacter(source, position, COMMA, error) ||
		!parseElement(source, position, help, error) ||
		!parseCharacter(source, position, COMMA, error) ||
		!parseElement(source, position, environmentKey, error) ||
		!parseCharacter(source, position, RIGHT_SQUARE_BRACKET, error)) {
		return;
	}

	if(environment.map.find(environmentKey) != environment.map.end()) {
		command = environment.map.find(environmentKey)->second->clone();
	}
	else {
		command = new Command();
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