#include <iostream>
#include <vector>

#include "menuitem.h"

#pragma once

class Menu : public MenuItem {
public:
	void run() {
		std::cout << name << std::endl;

		for(int i = 0; i < menuItems.size(); i++) {
			std::cout << "  " << menuItems[i].name << " (" << menuItems[i].command << std::endl;
		}


	}

private:
	std::vector<MenuItem> menuItems;
};