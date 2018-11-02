#pragma once

#include "command.h"
#include "menuitem.h"

#include <map>
#include <string>

namespace menu {
	std::string exportItem(const MenuItem &item);
	MenuItem* importItem(const std::string &source, const std::map<std::string, std::unique_ptr<menu::Command>> &environment, Error &error);
}