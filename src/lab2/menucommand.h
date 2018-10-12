#include "menuitem.h"
#include "command.h"

#pragma once

class MenuCommand : MenuItem {
public:
	void run() {

	}

private:
	Command* command;
};