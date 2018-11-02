#pragma once

#include "command.h"
#include "error.h"
#include "environment.h"
#include "menuitem.h"

#include <map>

namespace menu {
	class MenuCommand : public MenuItem {
	public:
		friend class Menu; // accessing the private constructor
		friend MenuItem* importItem(const std::string &source, const Environment &environment, Error &error);
		~MenuCommand();
		void run() override;

	private:
		// MenuCommand(std::string name, std::string commandString, std::string help, Menu* parent, Command* command);
		MenuCommand(Menu* parent, const std::string &source, size_t &position, const Environment &environment, Error &error);
		bool search(std::string &term, std::string path, std::ostream &stream) override;
		std::string getHelp() const override;
		std::string exportItem() const override;
		std::string help;
		Command* command;
	};
}