#pragma once

#include "menuitem.h"
#include "command.h"
#include "error.h"

namespace menu {
	class MenuCommand : public MenuItem {
	public:
		friend class Menu; // accessing the private constructor
		~MenuCommand();
		void run() override;
		std::string exportToString() override;
		// static MenuCommand* importFromString(std::string &source, Error &error);

	private:
		MenuCommand(std::string name, std::string commandString, std::string help, Menu* parent, Command* command);
		// MenuCommand(std::string &source, size_t position, Menu* parent, Error &error);
		bool search(std::string &term, std::string path, std::ostream &stream) override;
		bool getHelp(std::string &destination) override;
		std::string help;
		Command* command;
	};
}