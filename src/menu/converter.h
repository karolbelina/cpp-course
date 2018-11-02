#pragma once

#include "command.h"
#include "environment.h"
#include "menuitem.h"

#include <map>
#include <string>

namespace menu {
	std::string exportItem(const MenuItem &item);
	MenuItem* importItem(const std::string &source, const Environment &environment, Error &error);
}