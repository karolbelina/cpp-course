#include <vector>

#include "menuitem.h"

#pragma once

class Menu : public MenuItem {
public:
	Menu(std::string name, std::string commandString, std::vector<MenuItem*> menuItems);
	void run();

private:
	std::vector<MenuItem*> menuItems;
};