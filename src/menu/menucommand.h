#include "menuitem.h"
#include "command.h"

#pragma once

class MenuCommand : public MenuItem {
public:
	MenuCommand(const std::string name, const std::string commandString, Command* command);
	~MenuCommand();
	void run();

private:
	Command* command;
};