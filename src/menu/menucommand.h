#pragma once

#include "menuitem.h"
#include "command.h"

class MenuCommand : public MenuItem {
public:
	friend class Menu; // accessing the private constructor
	~MenuCommand();
	void run() override;
	bool search(std::string &term, std::string path, std::ostream &stream) override;
	bool getHelp(std::string &destination) override;
	std::string exportToString() override;
	
private:
	MenuCommand(std::string name, std::string commandString, std::string help, Menu* parent, Command* command);
	void importFromString(std::string &source, size_t position) override;
	std::string help;
	Command* command;
};