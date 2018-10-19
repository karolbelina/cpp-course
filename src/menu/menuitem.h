#include <string>

#pragma once

class MenuItem {
public:
	virtual void run() = 0;
	std::string getName();
	std::string getCommand();

protected:
	std::string name;
	std::string command;
};