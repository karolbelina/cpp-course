#include <iostream>
#include <vector>

#include "menuitem.h"

#pragma once

class Menu : public MenuItem {
public:
	void run();

private:
	std::vector<MenuItem> menuItems; //*
};