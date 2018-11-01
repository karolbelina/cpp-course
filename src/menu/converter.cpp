#include "converter.h"
#include "menu.h"
#include "menucommand.h"
#include "menuitem.h"

std::string menu::exportItem(const MenuItem &item) {
	return item.exportItem();
}

menu::MenuItem* menu::importItem(const std::string &string) {
	Error error;
	size_t position = 0;
	menu::MenuItem* item = new menu::Menu(nullptr, string, position, error);

	if(!error.occured) {
		return item;
	}
	else {
		return nullptr;
	}
}