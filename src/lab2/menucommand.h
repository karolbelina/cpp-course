#include "menuitem.h"
#include "command.h"

#pragma once

class MenuCommand : public MenuItem {
public:
	void run();

private:
	Command* command;
};