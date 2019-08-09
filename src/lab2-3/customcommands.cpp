#include "constants.hpp"
#include "customcommands.hpp"
#include "error.hpp"

#include <iostream>
#include <sstream>

static void getStringFromUserInput(std::string &destination)
{
  std::cout << PROMPT << SPACE;

  std::getline(std::cin, destination);
}

static bool getIntFromUserInput(int &destination)
{
  std::cout << PROMPT << SPACE;

  std::string input;
  std::getline(std::cin, input);
  std::istringstream stream(input);

  return static_cast<bool>(stream >> destination);
}

static bool getUnsignedIntFromUserInput(size_t &destination)
{
  std::cout << PROMPT << SPACE;

  std::string input;
  int temporary;
  std::getline(std::cin, input);
  std::istringstream stream(input);

  if (stream >> temporary)
  {
    if (temporary >= 0)
    {
      destination = temporary;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

CustomCommand::CustomCommand(table::TableContainer* tableContainer) : Command(), tableContainer(tableContainer)
{
}

menu::Command* CustomCommand::clone() const
{
  return new CustomCommand(*this);
}

CreateCommand::CreateCommand(table::TableContainer* tableContainer) : CustomCommand(tableContainer)
{
}

menu::Command* CreateCommand::clone() const
{
  return new CreateCommand(*this);
}

void CreateCommand::runCommand() const
{
  std::cout << ENTER_THE_AMOUNT_MESSAGE << COLON << std::endl;

  size_t amount;

  if (getUnsignedIntFromUserInput(amount))
  {
    size_t i = 0;

    if (amount > 0)
    {
      while (i < amount)
      {
        size_t index = tableContainer->tableCount();

        std::cout << ENTER_THE_NAME_OF_TABLE_MESSAGE << SPACE << HASH << index << COLON << std::endl;

        std::string name;
        getStringFromUserInput(name);

        std::cout << ENTER_THE_LENGTH_OF_TABLE_MESSAGE << SPACE << HASH << index << COLON << std::endl;

        size_t length;

        if (getUnsignedIntFromUserInput(length))
        {
          try
          {
            tableContainer->addTable(name, length);

            i++;
            std::cout << TABLE_CREATED_SUCCESSFULLY_MESSAGE << std::endl;
          }
          catch (const std::exception &e)
          {
            std::cerr << e.what() << std::endl;
          }
        }
        else
        {
          std::cout << INVALID_TABLE_LENGTH_MESSAGE << std::endl;
        }
      }
    }
    else
    {
      std::cout << AMOUNT_MUST_BE_GREATER_THAN_ZERO_MESSAGE << std::endl;
    }
  }
  else
  {
    std::cout << INVALID_AMOUNT_MESSAGE << std::endl;
  }
}

RemoveCommand::RemoveCommand(table::TableContainer* tableContainer) : CustomCommand(tableContainer)
{
}

menu::Command* RemoveCommand::clone() const
{
  return new RemoveCommand(*this);
}

void RemoveCommand::runCommand() const
{
  std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

  size_t tableIndex;

  if (getUnsignedIntFromUserInput(tableIndex))
  {
    try
    {
      tableContainer->removeTable(tableIndex);

      std::cout << REMOVED_TABLE_MESSAGE << SPACE << HASH << tableIndex << std::endl;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
  }
  else
  {
    std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
  }
}

RemoveAllCommand::RemoveAllCommand(table::TableContainer* tableContainer) : CustomCommand(tableContainer)
{
}

menu::Command* RemoveAllCommand::clone() const
{
  return new RemoveAllCommand(*this);
}

void RemoveAllCommand::runCommand() const
{
  tableContainer->removeAllTables();

  std::cout << REMOVED_ALL_TABLES_MESSAGE << std::endl;
}

ResizeCommand::ResizeCommand(table::TableContainer* tableContainer) : CustomCommand(tableContainer)
{
}

menu::Command* ResizeCommand::clone() const
{
  return new ResizeCommand(*this);
}

void ResizeCommand::runCommand() const
{
  std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

  size_t tableIndex;

  if (getUnsignedIntFromUserInput(tableIndex))
  {
    std::cout << ENTER_THE_TABLE_LENGTH_MESSAGE << COLON << std::endl;

    size_t tableLength;

    if (getUnsignedIntFromUserInput(tableLength))
    {
      try
      {
        tableContainer->resizeTable(tableIndex, tableLength);

        std::cout << THE_LENGTH_OF_TABLE_MESSAGE << SPACE << HASH << tableIndex << SPACE << HAS_BEEN_SET_TO_MESSAGE << SPACE << tableLength << std::endl;
      }
      catch (const std::exception &e)
      {
        std::cerr << e.what() << std::endl;
      }
    }
    else
    {
      std::cout << INVALID_TABLE_LENGTH_MESSAGE << std::endl;
    }
  }
  else
  {
    std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
  }
}

RenameCommand::RenameCommand(table::TableContainer* tableContainer) : CustomCommand(tableContainer)
{
}

menu::Command* RenameCommand::clone() const
{
  return new RenameCommand(*this);
}

void RenameCommand::runCommand() const
{
  std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

  size_t tableIndex;

  if (getUnsignedIntFromUserInput(tableIndex))
  {
    std::cout << ENTER_THE_TABLE_NAME_MESSAGE << COLON << std::endl;

    std::string name;
    getStringFromUserInput(name);

    try
    {
      tableContainer->renameTable(tableIndex, name);

      std::cout << THE_NAME_OF_TABLE_MESSAGE << SPACE << HASH << tableIndex << SPACE << HAS_BEEN_SET_TO_MESSAGE << SPACE << name << std::endl;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
  }
  else
  {
    std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
  }
}

StatusCommand::StatusCommand(table::TableContainer* tableContainer) : CustomCommand(tableContainer)
{
}

menu::Command* StatusCommand::clone() const
{
  return new StatusCommand(*this);
}

void StatusCommand::runCommand() const
{
  std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

  size_t tableIndex;

  if (getUnsignedIntFromUserInput(tableIndex))
  {
    try
    {
      std::cout << tableContainer->getTableStatus(tableIndex) << std::endl;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
  }
  else
  {
    std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
  }
}

StatusAllCommand::StatusAllCommand(table::TableContainer* tableContainer) : CustomCommand(tableContainer)
{
}

menu::Command* StatusAllCommand::clone() const
{
  return new StatusAllCommand(*this);
}

void StatusAllCommand::runCommand() const
{
  std::cout << tableContainer->getStatus() << std::endl;
}

CloneCommand::CloneCommand(table::TableContainer* tableContainer) : CustomCommand(tableContainer)
{
}

menu::Command* CloneCommand::clone() const
{
  return new CloneCommand(*this);
}

void CloneCommand::runCommand() const
{
  std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

  size_t tableIndex;

  if (getUnsignedIntFromUserInput(tableIndex))
  {
    try
    {
      tableContainer->cloneTable(tableIndex);

      std::cout << CLONED_TABLE_MESSAGE << SPACE << HASH << tableIndex << std::endl;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
  }
  else
  {
    std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
  }
}

EditCommand::EditCommand(table::TableContainer* tableContainer) : CustomCommand(tableContainer)
{
}

menu::Command* EditCommand::clone() const
{
  return new EditCommand(*this);
}

void EditCommand::runCommand() const
{
  std::cout << ENTER_THE_TABLE_INDEX_MESSAGE << COLON << std::endl;

  size_t tableIndex;

  if (getUnsignedIntFromUserInput(tableIndex))
  {
    std::cout << ENTER_THE_CELL_INDEX_MESSAGE << COLON << std::endl;

    size_t cellIndex;

    if (getUnsignedIntFromUserInput(cellIndex))
    {
      std::cout << ENTER_THE_VALUE_MESSAGE << COLON << std::endl;

      int value;

      if (getIntFromUserInput(value))
      {
        try
        {
          tableContainer->editTable(tableIndex, cellIndex, value);

          std::cout << THE_VALUE_OF_CELL_MESSAGE << SPACE << HASH << cellIndex << SPACE << OF_TABLE_MESSAGE << SPACE << HASH;
          std::cout << tableIndex << SPACE << HAS_BEEN_SET_TO_MESSAGE << SPACE << value << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cerr << e.what() << std::endl;
        }
      }
      else
      {
        std::cout << INVALID_VALUE_MESSAGE << std::endl;
      }
    }
    else
    {
      std::cout << INVALID_CELL_INDEX_MESSAGE << std::endl;
    }
  }
  else
  {
    std::cout << INVALID_TABLE_INDEX_MESSAGE << std::endl;
  }
}