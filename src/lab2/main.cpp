#include "command.h"
#include "constants.h"
#include "converter.h"
#include "customcommands.h"
#include "error.h"
#include "menu.h"
#include "tablecontainer.h"

#include <iostream>

int main() {
	table::TableContainer tableContainer;

	//menu::Menu menu;

	/*menu.addCommand(CREATE_TABLE_COMMAND_NAME, CREATE_TABLE_COMMAND_STRING, "", new CreateCommand(&tableContainer));
	menu.addCommand(REMOVE_TABLE_COMMAND_NAME, REMOVE_TABLE_COMMAND_STRING, "", new RemoveCommand(&tableContainer));
	menu.addCommand(REMOVE_ALL_TABLES_COMMAND_NAME, REMOVE_ALL_TABLES_COMMAND_STRING, "", new RemoveAllCommand(&tableContainer));
	menu.addCommand(RESIZE_TABLE_COMMAND_NAME, RESIZE_TABLE_COMMAND_STRING, "", new ResizeCommand(&tableContainer));
	menu.addCommand(RENAME_TABLE_COMMAND_NAME, RENAME_TABLE_COMMAND_STRING, "", new RenameCommand(&tableContainer));
	menu.addCommand(TABLE_STATUS_COMMAND_NAME, TABLE_STATUS_COMMAND_STRING, "", new StatusCommand(&tableContainer));
	menu.addCommand(STATUS_COMMAND_NAME, STATUS_COMMAND_STRING, "", new StatusAllCommand(&tableContainer));
	menu.addCommand(CLONE_TABLE_COMMAND_NAME, CLONE_TABLE_COMMAND_STRING, "", new CloneCommand(&tableContainer));
	menu.addCommand(EDIT_TABLE_COMMAND_NAME, EDIT_TABLE_COMMAND_STRING, "", new EditCommand(&tableContainer));
	menu::Menu* subMenu = menu.addMenu(TEST_SUBMENU_NAME, TEST_SUBMENU_STRING);
	subMenu->addCommand(TEST_COMMAND_NAME, TEST_COMMAND_STRING, "", new menu::Command());*/

	//std::cout << menu::exportItem(menu) << std::endl;

	const std::string string = "('Main menu','';['Create table','create','','CreateCommand'],['Remove table','remove','','RemoveCommand'],['Remove all tables','removeall','','RemoveAllCommand'],['Resize table','resize','','ResizeCommand'],['Rename table','rename','','RenameCommand'],['Table status','status','','StatusCommand'],['Status','statusall','','StatusAllCommand'],['Clone table','clone','','CloneCommand'],['Edit table','edit','','EditCommand'])";
	std::map<std::string, std::unique_ptr<menu::Command>> environment;
	environment["CreateCommand"] = std::make_unique<CreateCommand>(&tableContainer);
	environment["RemoveCommand"] = std::make_unique<RemoveCommand>(&tableContainer);
	environment["RemoveAllCommand"] = std::make_unique<RemoveAllCommand>(&tableContainer);
	environment["ResizeCommand"] = std::make_unique<ResizeCommand>(&tableContainer);
	environment["RenameCommand"] = std::make_unique<RenameCommand>(&tableContainer);
	environment["StatusCommand"] = std::make_unique<StatusCommand>(&tableContainer);
	environment["StatusAllCommand"] = std::make_unique<StatusAllCommand>(&tableContainer);
	environment["CloneCommand"] = std::make_unique<CloneCommand>(&tableContainer);
	environment["EditCommand"] = std::make_unique<EditCommand>(&tableContainer);
	menu::Error error;

	std::cout << TITLE_MESSAGE << std::endl;
	menu::importItem(string, environment, error)->run();
}