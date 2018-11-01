#include "converter.h"
#include "menu.h"
#include "menuitem.h"

std::string menu::exportItem(const MenuItem &item) {
	return item.exportItem();
}

menu::MenuItem* menu::importItem(const std::string &string) {
	return new menu::Menu();
}