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

menu::MenuCommand::MenuCommand(Menu* parent, const std::string &source, size_t &position, const Environment &environment) {
	this->parent = parent;
	std::string environmentKey;

	parseCharacter(source, position, LEFT_SQUARE_BRACKET);
	parseString(source, position, name);
	parseCharacter(source, position, COMMA);
	parseAndValidateString(source, position, commandString, parent);
	parseCharacter(source, position, COMMA);
	parseString(source, position, help);
	parseCharacter(source, position, COMMA);
	parseString(source, position, environmentKey);

	std::map<std::string, Command*>::const_iterator foundValue = environment.map.find(environmentKey);
	if(foundValue != environment.map.end()) {
		command = foundValue->second->clone();
	}

	parseCharacter(source, position, RIGHT_SQUARE_BRACKET);
}

bool menu::MenuCommand::search(std::string &term, std::string path, std::ostream &stream, bool &separator) {
	if(term == commandString) {
		if(separator) {
			stream << std::endl;
		}
		stream << path << commandString;
		separator = true;

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