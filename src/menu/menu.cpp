#include "menu.h"
#include "constants.h"

#include <iostream>
#include <string>

Menu::Menu(std::string name, std::string commandString, std::vector<MenuItem*> menuItems) : MenuItem(name, commandString) {
	this->menuItems = menuItems;
}

Menu::~Menu() {
	int size = menuItems.size();
	for(int i = 0; i < size; i++) {
		delete menuItems[i];
	}
}

void Menu::run() {
	std::cout << name << std::endl;

	for(int i = 0; i < menuItems.size(); i++) {
		std::cout << std::string(PADDING, SPACE);
		std::cout << menuItems[i]->getName() << SPACE << OPEN_PARENTHESIS << menuItems[i]->getCommand() << CLOSE_PARENTHESIS << std::endl;
	}

	std::string input;
	bool retryInput = true;

	do {
		std::cout << PROMPT << SPACE;
		std::getline(std::cin, input);

		if(input != BACK_COMMAND) {
			bool foundValidCommand = false;

			for(int i = 0; i < menuItems.size(); i++) {
				if(input == menuItems[i]->getCommand()) {
					menuItems[i]->run();

					foundValidCommand = true;
				}
			}

			if(!foundValidCommand) {
				std::cout << INVALID_COMMAND_MESSAGE << std::endl;
			}
		}
		else {
			bool retryInput = false;
		}
	} while(retryInput);
}