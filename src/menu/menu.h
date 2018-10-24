#include <vector>

#include "menuitem.h"
#include "command.h"

#pragma once

class Menu : public MenuItem {
public:
	Menu(const std::string name, const std::string commandString);
	~Menu();
	bool addMenu(std::string name, std::string commandString);
	bool addCommand(std::string name, std::string commandString, Command* command);
	bool removeItem(std::string commandString);
	void run();

private:
	bool checkCommandString(std::string commandString);
	std::vector<MenuItem*> items;
};