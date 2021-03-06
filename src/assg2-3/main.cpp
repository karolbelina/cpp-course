#include "constants.hpp"
#include "customcommands.hpp"
#include "environment.hpp"
#include "error.hpp"
#include "menuitem.hpp"
#include "tablecontainer.hpp"

#include <iostream>

int main()
{
  table::TableContainer tableContainer;

  const std::string string = "('Main menu','main';['Create table','create','Create a table','CreateCommand'],['Remove table','remove','This is a help string','RemoveCommand'],['Remove all tables','removeall','','RemoveAllCommand'],['Resize table','resize','','ResizeCommand'],['Rename table','rename','','RenameCommand'],['Table status','status','','StatusCommand'],['Status','statusall','','StatusAllCommand'],['Clone table','clone','','CloneCommand'],['Edit table','edit','','EditCommand'],('test','test';['create','create','','CreateCommand']),('B','B';('D','D';),('E','E';)),('C','C';('F','F';)))";
  const menu::Environment environment = {
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

  std::cout << TITLE_MESSAGE << std::endl;
  try
  {
    menu::MenuItem::importItem(string, environment)->run();
  }
  catch (const menu::parse_error &e)
  {
    std::cerr << e.what() << std::endl;
  }
}