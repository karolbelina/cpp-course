#include "command.h"
#include "constants.h"
#include "converter.h"
#include "environment.h"
#include "menu.h"
#include "menucommand.h"
#include "menuitem.h"

std::string menu::exportItem(const MenuItem &item) {
	return item.exportItem();
}

menu::MenuItem* menu::importItem(const std::string &source, const Environment &environment, Error &error) {
	size_t position = 0;
	menu::MenuItem* item = nullptr;

	if(source[position] == LEFT_PARENTHESIS) {
		item = new menu::Menu(nullptr, source, position, environment, error);
	}
	else if(source[position] == LEFT_SQUARE_BRACKET) {
		item = new menu::MenuCommand(nullptr, source, position, environment, error);
	}
	else {
		error.syntaxError(position, {LEFT_PARENTHESIS, LEFT_SQUARE_BRACKET}); // expected ( or [
	}

	if(!error) {
		return item;
	}
	else {
		return nullptr;
	}
}