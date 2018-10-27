#pragma once

#include <vector>

#include "menuitem.h"
#include "menucommand.h"
#include "command.h"

class Menu : public MenuItem {
public:
	Menu();
	~Menu();
	Menu* addMenu(std::string name, std::string commandString);
	MenuCommand* addCommand(std::string name, std::string commandString, std::string help, Command* command);
	bool removeItem(std::string commandString);
	void run() override;
	bool search(std::string &term, std::string path, std::ostream &stream) override;
	bool getHelp(std::string &destination) override;

private:
	Menu(std::string name, std::string commandString, Menu* parent);
	std::string validateCommandString(std::string commandString);
	bool checkKeywords(std::string commandString);
	bool checkDuplicates(std::string commandString);
	std::vector<MenuItem*> items;
};