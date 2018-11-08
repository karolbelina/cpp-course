#pragma once

#include "command.h"
#include "environment.h"
#include "error.h"

#include <map>
#include <string>

#include <string>

namespace menu {
	class Menu;

	class MenuItem {
	public:
		friend class Menu; // accessing fields directly without the use of getters which may be visible to the user
		//friend std::string exportItem(const MenuItem &);

		MenuItem();
		MenuItem(const MenuItem &other);
		virtual ~MenuItem();
		MenuItem& operator=(const MenuItem &other);
		virtual MenuItem* clone() const = 0;

		virtual void run() = 0;

		static std::string exportItem(const MenuItem &item);
		static MenuItem* importItem(const std::string &source, const Environment &environment, Error &error);

	protected:
		virtual bool search(std::string &term, std::string path, std::ostream &stream, bool &separator) = 0;
		virtual std::string getHelp() const = 0;
		virtual std::string exportItem() const = 0;
		virtual void printTree(size_t currentRow, std::vector<std::vector<MenuItem*>> &rows) = 0;

		static bool parseElement(const std::string &source, size_t &position, std::string &destination, Error &error);
		static bool parseCharacter(const std::string &source, size_t &position, const char character, Error &error);
		static std::string validateCommandString(std::string commandString);
		bool checkKeywords(std::string commandString);
		bool checkDuplicates(std::string commandString);

		std::string name;
		std::string commandString;
		Menu* parent;
	};
}