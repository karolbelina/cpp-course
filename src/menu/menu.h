#include <vector>

#include "menuitem.h"
#include "command.h"

#pragma once

class Menu : public MenuItem {
public:
	Menu(std::string name, std::string commandString);
	~Menu();
	bool addMenu(std::string name, std::string commandString);
	bool addCommand(std::string name, std::string commandString, Command* command);
	bool removeItem(std::string commandString);
	void run() override;

private:
	bool checkCommandString(std::string commandString);
	std::vector<MenuItem*> items;
};