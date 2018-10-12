#include <iostream>

#pragma once

class Command {
public:
	virtual void runCommand() {
		std::cout << "default command" << std::endl;
	}
};