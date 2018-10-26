#include <vector>

#include "menuitem.h"
#include "menucommand.h"
#include "command.h"

#pragma once

class Menu : public MenuItem {
public:
	Menu();
	~Menu();
	Menu* addMenu(std::string name, std::string commandString);
	MenuCommand* addCommand(std::string name, std::string commandString, Command* command);
	bool removeItem(std::string commandString);
	void run() override;
	void printLeaves() override;

private:
	Menu(std::string name, std::string commandString, Menu* parent);
	bool checkCommandString(std::string commandString);
	std::vector<MenuItem*> items;
};