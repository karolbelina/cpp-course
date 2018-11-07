#include "command.h"
#include "constants.h"
#include "converter.h"
#include "customcommands.h"
#include "environment.h"
#include "error.h"
#include "menu.h"
#include "tablecontainer.h"

#include <iostream>

int main() {
	table::TableContainer tableContainer;

	const std::string string = "('Main menu','main';['Create table','create','Create a table','CreateCommand'],['Remove table','remove','This is a help string','RemoveCommand'],['Remove all tables','removeall','','RemoveAllCommand'],['Resize table','resize','','ResizeCommand'],['Rename table','rename','','RenameCommand'],['Table status','status','','StatusCommand'],['Status','statusall','','StatusAllCommand'],['Clone table','clone','','CloneCommand'],['Edit table','edit','','EditCommand'],('test','test';['create','create','','CreateCommand']))";
	menu::Environment environment = {
		{"CreateCommand", new CreateCommand(&tableContainer)},
		{"RemoveCommand", new RemoveCommand(&tableContainer)},
		{"RemoveAllCommand", new RemoveAllCommand(&tableContainer)},
		{"ResizeCommand", new ResizeCommand(&tableContainer)},
		{"RenameCommand", new RenameCommand(&tableContainer)},
		{"StatusCommand", new StatusCommand(&tableContainer)},
		{"StatusAllCommand", new StatusAllCommand(&tableContainer)},
		{"CloneCommand", new CloneCommand(&tableContainer)},
		{"EditCommand", new EditCommand(&tableContainer)}
	};
	menu::Error error;

	std::cout << TITLE_MESSAGE << std::endl;
	menu::MenuItem* menu = menu::importItem(string, environment, error);
	if(!error) {
		menu->run();
	}
	else {
		std::cout << error << std::endl;
	}
}