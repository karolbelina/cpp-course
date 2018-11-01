#pragma once

#include "command.h"
#include "error.h"
#include "menuitem.h"

namespace menu {
	class MenuCommand : public MenuItem {
	public:
		//friend class Menu; // accessing the private constructor
		friend MenuItem* importItem(const std::string &string);
		~MenuCommand();
		void run() override;

	private:
		// MenuCommand(std::string name, std::string commandString, std::string help, Menu* parent, Command* command);
		MenuCommand(Menu* parent, const std::string &source, size_t &position, Error &error);
		bool search(std::string &term, std::string path, std::ostream &stream) override;
		std::string getHelp() const override;
		std::string exportItem() const override;
		std::string help;
		Command* command;
	};
}