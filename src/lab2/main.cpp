#include "tablecontainer.h"
#include "menuitem.h"
#include "menucommand.h"
#include "menu.h"
#include "command.h"
#include "customcommands.h"

#include <iostream>
#include <vector>

int main() {
	TableContainer tableContainer;

	std::vector<MenuItem*> menuItems;
	menuItems.push_back(new MenuCommand("create table", "create", new CreateCommand(&tableContainer)));
	menuItems.push_back(new MenuCommand("remove table", "remove", new RemoveCommand(&tableContainer)));
	menuItems.push_back(new MenuCommand("resize table", "resize", new ResizeCommand(&tableContainer)));
	menuItems.push_back(new MenuCommand("rename table", "rename", new RenameCommand(&tableContainer)));
	menuItems.push_back(new MenuCommand("table status", "status", new StatusCommand(&tableContainer)));
	menuItems.push_back(new MenuCommand("clone table", "clone", new CloneCommand(&tableContainer)));
	menuItems.push_back(new MenuCommand("edit table", "edit", new EditCommand(&tableContainer)));

	Menu menu("Main menu", "main", menuItems);

	menu.run();
}