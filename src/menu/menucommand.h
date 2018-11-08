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
		friend static MenuItem* MenuItem::importItem(const std::string &, const Environment &, Error &);

		MenuCommand() = delete;
		MenuCommand(const MenuCommand &other);
		~MenuCommand();
		MenuCommand& operator=(const MenuCommand &other);
		MenuItem* clone() const override;

		void run() override;

	private:
		MenuCommand(Menu* parent, const std::string &source, size_t &position, const Environment &environment, Error &error);

		bool search(std::string &term, std::string path, std::ostream &stream, bool &separator) override;
		std::string getHelp() const override;
		std::string exportItem() const override;
		void printTree(size_t currentRow, std::vector<std::vector<MenuItem*>> &rows);

		std::string help;
		Command* command;
	};
}