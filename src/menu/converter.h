#pragma once

#include "menuitem.h"

#include <string>

namespace menu {
	std::string exportItem(const MenuItem &item);
	MenuItem* importItem(const std::string &string, Error &error);
}