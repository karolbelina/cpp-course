#include "command.h"
#include "constants.h"

#include <iostream>

void menu::Command::runCommand() const {
	std::cout << DEFAULT_COMMAND_MESSAGE << std::endl;
}

menu::Command* menu::Command::clone() const {
	return new Command(*this);
}