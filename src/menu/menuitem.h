#include <string>

#pragma once

class MenuItem {
public:
	virtual void run() = 0;
	std::string getName() const;
	std::string getCommand() const;

protected:
	std::string name;
	std::string command;
};