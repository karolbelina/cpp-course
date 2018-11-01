#pragma once

#include "command.h"
#include "error.h"
#include "menucommand.h"
#include "menuitem.h"

#include <vector>

namespace menu {
	class Menu : public MenuItem {
	public:
		Menu();
		~Menu();
		Menu* addMenu(std::string name, std::string commandString);
		MenuCommand* addCommand(std::string name, std::string commandString, std::string help, Command* command);
		bool removeItem(std::string commandString);
		void run() override;
		std::string exportToString() override;
		// static Menu* importFromString(std::string &source, Error &error);

	private:
		Menu(std::string name, std::string commandString, Menu* parent);
		// Menu(std::string &source, size_t position, Menu* parent, Error &error);
		std::string validateCommandString(std::string commandString);
		bool checkKeywords(std::string commandString);
		bool checkDuplicates(std::string commandString);
		bool search(std::string &term, std::string path, std::ostream &stream) override;
		bool getHelp(std::string &destination) override;
		std::vector<MenuItem*> items;
	};
}