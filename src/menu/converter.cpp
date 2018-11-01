#include "constants.h"
#include "converter.h"
#include "menu.h"
#include "menucommand.h"
#include "menuitem.h"

std::string menu::exportItem(const MenuItem &item) {
	return item.exportItem();
}

menu::MenuItem* menu::importItem(const std::string &source, Error &error) {
	size_t position = 0;
	menu::MenuItem* item = nullptr;

	if(source[position] == LEFT_PARENTHESIS) {
		item = new menu::Menu(nullptr, source, position, error);
	}
	else if(source[position] == LEFT_SQUARE_BRACKET) {
		item = new menu::MenuCommand(nullptr, source, position, error);
	}
	else {
		error.occur(position, LEFT_PARENTHESIS); // expected ( or [
	}

	if(!error.occured) {
		return item;
	}
	else {
		return nullptr;
	}
}