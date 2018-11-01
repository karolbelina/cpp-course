#include "command.h"
#include "constants.h"

#include <iostream>

void menu::Command::runCommand() {
	std::cout << DEFAULT_COMMAND_MESSAGE << std::endl;
}