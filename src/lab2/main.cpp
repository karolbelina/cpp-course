#include "tablecontainer.h"
#include "menu.h"
#include "customcommands.h"

#include <iostream>

int main() {
	TableContainer tableContainer;

	Menu menu("main menu", "main");

	menu.addCommand("create table", "create", new CreateCommand(&tableContainer));
	menu.addCommand("remove table", "remove", new RemoveCommand(&tableContainer));
	menu.addCommand("remove all tables", "removeall", new RemoveAllCommand(&tableContainer));
	menu.addCommand("resize table", "resize", new ResizeCommand(&tableContainer));
	menu.addCommand("rename table", "rename", new RenameCommand(&tableContainer));
	menu.addCommand("table status", "status", new StatusCommand(&tableContainer));
	menu.addCommand("status", "statusall", new StatusAllCommand(&tableContainer));
	menu.addCommand("clone table", "clone", new CloneCommand(&tableContainer));
	menu.addCommand("edit table", "edit", new EditCommand(&tableContainer));

	std::cout << "table creator v1.1" << std::endl;
	menu.run();
}