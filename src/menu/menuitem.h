#pragma once

#include <string>

class Menu;

class MenuItem {
public:
	MenuItem(std::string name, std::string commandString, Menu* parent);
	virtual ~MenuItem();
	virtual void run() = 0;
	virtual bool search(std::string &term, std::string path, std::ostream &stream) = 0;
	virtual bool getHelp(std::string &destination) = 0;
	virtual std::string exportToString() = 0;
	void importFromString(std::string &source);
	std::string getName() const;
	std::string getCommand() const;
	Menu* getParent() const;
	Menu* getRoot() const;

protected:
	virtual void importFromString(std::string &source, size_t position) = 0;
	std::string name;
	std::string commandString;
	Menu* parent;
};