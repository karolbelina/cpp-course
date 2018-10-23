#include <vector>

#include "menuitem.h"

#pragma once

class Menu : public MenuItem {
public:
	Menu(const std::string name, const std::string commandString, const std::vector<MenuItem*> menuItems);
	~Menu();
	void run();

private:
	std::vector<MenuItem*> menuItems;
};