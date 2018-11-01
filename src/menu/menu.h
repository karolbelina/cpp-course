#pragma once

#include "command.h"
#include "error.h"
#include "menucommand.h"
#include "menuitem.h"

#include <vector>

namespace menu {
	class Menu : public MenuItem {
	public:
		friend MenuItem* importItem(const std::string &string);
		Menu();
		~Menu();
		// Menu* addMenu(std::string name, std::string commandString);
		// MenuCommand* addCommand(std::string name, std::string commandString, std::string help, Command* command);
		// bool removeItem(std::string commandString);
		void run() override;

	private:
		// Menu(std::string name, std::string commandString, Menu* parent);
		Menu(Menu* parent, const std::string &source, size_t &position, Error &error);
		std::string validateCommandString(std::string commandString);
		bool checkKeywords(std::string commandString);
		bool checkDuplicates(std::string commandString);
		bool search(std::string &term, std::string path, std::ostream &stream) override;
		std::string getHelp() const override;
		std::string exportItem() const override;
		std::vector<MenuItem*> items;
	};
}