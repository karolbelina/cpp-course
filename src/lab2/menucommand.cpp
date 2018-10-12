#include "menucommand.h"

void MenuCommand::run() {
	if(command != NULL) {
		command->runCommand;
	}
	else {
		std::cout << "empty command" << std::endl;
	}
}