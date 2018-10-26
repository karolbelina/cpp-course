#include "menuitem.h"
#include "command.h"

#pragma once

class MenuCommand : public MenuItem {
public:
	~MenuCommand();
	void run() override;
	void printLeaves() override;
	friend class Menu; // accessing the private constructor

private:
	MenuCommand(std::string name, std::string commandString, Menu* parent, Command* command);
	Command* command;
};