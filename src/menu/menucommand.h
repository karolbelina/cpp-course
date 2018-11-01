#pragma once

#include "command.h"
#include "error.h"
#include "menuitem.h"

namespace menu {
	class MenuCommand : public MenuItem {
	public:
		friend class Menu; // accessing the private constructor
		~MenuCommand();
		void run() override;

	private:
		MenuCommand(std::string name, std::string commandString, std::string help, Menu* parent, Command* command);
		// MenuCommand(std::string &source, size_t position, Menu* parent, Error &error);
		bool search(std::string &term, std::string path, std::ostream &stream) override;
		bool getHelp(std::string &destination) override;
		// static MenuCommand* importFromString(std::string &source, Error &error);
		std::string exportItem() const override;
		std::string help;
		Command* command;
	};
}