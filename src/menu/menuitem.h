#pragma once

#include "error.h"

#include <string>

namespace menu {
	class Menu;

	class MenuItem {
	public:
		friend class Menu; // accessing fields directly without the use of getters which may be visible to the user
		friend std::string exportItem(const MenuItem &item);
		MenuItem(std::string name, std::string commandString, Menu* parent);
		// MenuItem(std::string &source, size_t position, Menu* parent, Error &error);
		virtual ~MenuItem();
		virtual void run() = 0;
		// static MenuItem* importFromString(std::string &source);

	protected:
		Menu* getParent() const;
		Menu* getRoot() const;
		virtual bool search(std::string &term, std::string path, std::ostream &stream) = 0;
		virtual bool getHelp(std::string &destination) = 0;
		virtual std::string exportItem() const = 0;
		std::string name;
		std::string commandString;
		Menu* parent;
	};
}