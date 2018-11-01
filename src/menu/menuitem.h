#pragma once

#include "error.h"

#include <string>

namespace menu {
	class Menu;

	class MenuItem {
	public:
		MenuItem(std::string name, std::string commandString, Menu* parent);
		// MenuItem(std::string &source, size_t position, Menu* parent, Error &error);
		virtual ~MenuItem();
		virtual void run() = 0;
		virtual std::string exportToString() = 0;
		// static MenuItem* importFromString(std::string &source);
		std::string getName() const;
		std::string getCommand() const;
		Menu* getParent() const;
		Menu* getRoot() const;

	protected:
		virtual bool search(std::string &term, std::string path, std::ostream &stream) = 0;
		virtual bool getHelp(std::string &destination) = 0;
		std::string name;
		std::string commandString;
		Menu* parent;
	};
}