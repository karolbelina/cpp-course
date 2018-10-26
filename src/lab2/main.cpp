#include "tablecontainer.h"
#include "menu.h"
#include "customcommands.h"
#include "constants.h"

#include <iostream>

int main() {
	TableContainer tableContainer;

	Menu menu;

	menu.addCommand(CREATE_TABLE_COMMAND_NAME, CREATE_TABLE_COMMAND_STRING, new CreateCommand(&tableContainer));
	menu.addCommand(REMOVE_TABLE_COMMAND_NAME, REMOVE_TABLE_COMMAND_STRING, new RemoveCommand(&tableContainer));
	menu.addCommand(REMOVE_ALL_TABLES_COMMAND_NAME, REMOVE_ALL_TABLES_COMMAND_STRING, new RemoveAllCommand(&tableContainer));
	menu.addCommand(RESIZE_TABLE_COMMAND_NAME, RESIZE_TABLE_COMMAND_STRING, new ResizeCommand(&tableContainer));
	menu.addCommand(RENAME_TABLE_COMMAND_NAME, RENAME_TABLE_COMMAND_STRING, new RenameCommand(&tableContainer));
	menu.addCommand(TABLE_STATUS_COMMAND_NAME, TABLE_STATUS_COMMAND_STRING, new StatusCommand(&tableContainer));
	menu.addCommand(STATUS_COMMAND_NAME, STATUS_COMMAND_STRING, new StatusAllCommand(&tableContainer));
	menu.addCommand(CLONE_TABLE_COMMAND_NAME, CLONE_TABLE_COMMAND_STRING, new CloneCommand(&tableContainer));
	menu.addCommand(EDIT_TABLE_COMMAND_NAME, EDIT_TABLE_COMMAND_STRING, new EditCommand(&tableContainer));
	Menu* subMenu = menu.addMenu(TEST_SUBMENU_NAME, TEST_SUBMENU_STRING);
	subMenu->addCommand(TEST_COMMAND_NAME, TEST_COMMAND_STRING, new Command());

	std::cout << TITLE_MESSAGE << std::endl;
	menu.run();
}