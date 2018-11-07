#pragma once

#include "command.h"
#include "environment.h"
#include "error.h"
#include "menucommand.h"
#include "menuitem.h"

#include <vector>

namespace menu {
	class Menu : public MenuItem {
	public:
		friend bool MenuItem::checkDuplicates(const std::string);
		friend MenuItem* importItem(const std::string&, const Environment&, Error&);

		Menu() = delete;
		Menu(const Menu &other);
		~Menu();
		Menu& operator=(const Menu &other);
		MenuItem* clone() const override;

		void run() override;

	private:
		Menu(Menu* parent, const std::string &source, size_t &position, const Environment &environment, Error &error);

		Menu* getRoot();
		bool search(std::string &term, std::string path, std::ostream &stream, bool &separator) override;
		std::string getHelp() const override;
		std::string exportItem() const override;

		std::vector<MenuItem*> items;
	};
}