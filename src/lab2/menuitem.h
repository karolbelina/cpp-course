#include <string>

#pragma once

class MenuItem {
public:
	friend class Menu;
	virtual void run() = 0;

protected:
	std::string name;
	std::string command;
};