#include <string>

#pragma once

class MenuItem {
public:
	MenuItem(std::string name, std::string commandString);
	virtual ~MenuItem();
	virtual void run() = 0;
	virtual void printLeaves() = 0;
	std::string getName() const;
	std::string getCommand() const;

protected:
	std::string name;
	std::string commandString;
};