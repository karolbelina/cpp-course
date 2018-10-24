#include "menuitem.h"
#include "command.h"

#pragma once

class MenuCommand : public MenuItem {
public:
	MenuCommand(std::string name, std::string commandString, Command* command);
	~MenuCommand();
	void run() override;

private:
	Command* command;
};