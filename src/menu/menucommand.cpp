#include "menucommand.h"
#include "constants.h"

void MenuCommand::run() {
	if(command != NULL) {
		command->runCommand();
	}
	else {
		std::cout << EMPTY_COMMAND_MESSAGE << std::endl;
	}
}