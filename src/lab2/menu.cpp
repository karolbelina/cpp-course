#include "menu.h"

void Menu::run() {
	std::cout << name << std::endl;

	for(int i = 0; i < menuItems.size(); i++) {
		std::cout << "  " << menuItems[i].name << " (" << menuItems[i].command << ")" << std::endl;
	}

	std::string input;
	bool retryInput = true;

	do {
		std::getline(std::cin, input);

		if(input != "back") {
			bool foundValidCommand = false;

			for(int i = 0; i < menuItems.size(); i++) {
				if(input == menuItems[i].command) {
					menuItems[i].run();

					foundValidCommand = true;
				}
			}

			if(!foundValidCommand) {
				std::cout << "invalid command" << std::endl;
			}
		}
		else {
			bool retryInput = false;
		}
	} while(retryInput);
}
