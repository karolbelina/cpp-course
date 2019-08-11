#include "constants.hpp"
#include "table.hpp"
#include "tablecontainer.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

void getLine(std::istringstream &stream)
{
  std::string input;

  std::cout << PROMPT_MESSAGE;

  std::getline(std::cin, input);
  stream.clear();
  stream.str(input);
}

bool nextInt(std::istringstream &stream, int &destination, std::string noParameterString, std::string invalidParameterString)
{
  if (stream >> destination)
  {
    return true;
  }
  else if (stream.eof())
  {
    if (noParameterString != "")
    {
      std::cout << noParameterString << std::endl;
    }
  }
  else
  {
    if (invalidParameterString != "")
    {
      std::cout << invalidParameterString << std::endl;
    }
  }

  return false;
}

bool nextUnsignedInt(std::istringstream &stream, size_t &destination, std::string noParameterString, std::string invalidParameterString, std::string negativeParameterString)
{
  int temporary;

  if (stream >> temporary)
  {
    if (temporary >= 0)
    {
      destination = temporary;
      return true;
    }
    else
    {
      if (negativeParameterString != "")
      {
        std::cout << negativeParameterString << std::endl;
      }
    }
  }
  else if (stream.eof())
  {
    if (noParameterString != "")
    {
      std::cout << noParameterString << std::endl;
    }
  }
  else
  {
    if (invalidParameterString != "")
    {
      std::cout << invalidParameterString << std::endl;
    }
  }

  return false;
}

void nextString(std::istringstream &stream, std::string &destination)
{
  stream >> destination;
}

int main()
{
  table::TableContainer tableContainer;
  std::string input;
  std::istringstream inputStream;
  std::string command;

  std::cout << TITLE_MESSAGE << std::endl;
  std::cout << HELP_MESSAGE << std::endl;

  while (command != QUIT_COMMAND)
  {
    getLine(inputStream);
    nextString(inputStream, command);

    if (command == CREATE_COMMAND)
    {
      size_t amount;

      if (nextUnsignedInt(inputStream, amount, NO_PARAMETERS_MESSAGE, INVALID_AMOUNT_MESSAGE, AMOUNT_GREATER_THAN_ZERO_MESSAGE))
      {
        size_t iterator = 0;

        if (amount > 0)
        {
          while (iterator < amount)
          {
            size_t index = tableContainer.tableCount();

            std::cout << ENTER_TABLE_NAME_MESSAGE << index << COLON << std::endl;

            std::string name;
            getLine(inputStream);
            nextString(inputStream, name);

            std::cout << ENTER_TABLE_LENGTH_MESSAGE << index << COLON << std::endl;

            size_t length;
            getLine(inputStream);

            if (nextUnsignedInt(inputStream, length, NO_PARAMETERS_MESSAGE, INVALID_TABLE_LENGTH_MESSAGE, NEGATIVE_TABLE_LENGTH_MESSAGE))
            {
              try
              {
                tableContainer.addTable(name, length);

                iterator++;
                std::cout << CREATED_TABLE_MESSAGE << std::endl;
              }
              catch (const std::exception &e)
              {
                std::cerr << e.what() << std::endl;
              }
            }
          }
        }
        else
        {
          std::cout << AMOUNT_GREATER_THAN_ZERO_MESSAGE << std::endl;
        }
      }
    }
    else if (command == REMOVE_COMMAND)
    {
      size_t tableIndex;

      if (nextUnsignedInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, EMPTY_STRING, NEGATIVE_TABLE_INDEX_MESSAGE))
      {
        try
        {
          tableContainer.removeTable(tableIndex);

          std::cout << REMOVED_TABLE_MESSAGE << tableIndex << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cerr << e.what() << std::endl;
        }
      }
      else
      {
        inputStream.clear();

        std::string allFlag;
        nextString(inputStream, allFlag);

        if (allFlag == ALL_COMMAND)
        {
          tableContainer.removeAllTables();

          std::cout << REMOVED_ALL_TABLES_MESSAGE << std::endl;
        }
        else
        {
          std::cout << INVALID_COMMAND_MESSAGE << std::endl;
        }
      }
    }
    else if (command == RESIZE_COMMAND)
    {
      size_t tableIndex;

      if (nextUnsignedInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, INVALID_TABLE_INDEX_MESSAGE, NEGATIVE_TABLE_INDEX_MESSAGE))
      {
        size_t tableLength;

        if (nextUnsignedInt(inputStream, tableLength, NO_SECOND_PARAMETER_MESSAGE, INVALID_TABLE_LENGTH_MESSAGE, NEGATIVE_TABLE_LENGTH_MESSAGE))
        {
          try
          {
            tableContainer.resizeTable(tableIndex, tableLength);

            std::cout << TABLE_LENGTH_MESSAGE << tableIndex << SET_TO_MESSAGE << tableLength << std::endl;
          }
          catch (const std::exception &e)
          {
            std::cerr << e.what() << std::endl;
          }
        }
      }
    }
    else if (command == RENAME_COMMAND)
    {
      size_t tableIndex;

      if (nextUnsignedInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, INVALID_TABLE_INDEX_MESSAGE, NEGATIVE_TABLE_INDEX_MESSAGE))
      {
        std::string name;

        nextString(inputStream, name);

        try
        {
          tableContainer.renameTable(tableIndex, name);

          std::cout << TABLE_NAME_MESSAGE << tableIndex << SET_TO_MESSAGE << name << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cerr << e.what() << std::endl;
        }
      }
    }
    else if (command == STATUS_COMMAND)
    {
      size_t tableIndex;

      if (nextUnsignedInt(inputStream, tableIndex, EMPTY_STRING, EMPTY_STRING, NEGATIVE_TABLE_INDEX_MESSAGE))
      {
        try
        {
          std::cout << tableContainer.getTableStatus(tableIndex) << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cerr << e.what() << std::endl;
        }
      }
      else
      {
        std::cout << tableContainer.getStatus() << std::endl;
      }
    }
    else if (command == CLONE_COMMAND)
    {
      size_t tableIndex;

      if (nextUnsignedInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, INVALID_TABLE_INDEX_MESSAGE, NEGATIVE_TABLE_INDEX_MESSAGE))
      {
        try
        {
          tableContainer.cloneTable(tableIndex);

          std::cout << CLONED_TABLE_MESSAGE << tableIndex << std::endl;
        }
        catch (const std::exception &e)
        {
          std::cerr << e.what() << std::endl;
        }
      }
    }
    else if (command == EDIT_COMMAND)
    {
      size_t tableIndex;

      if (nextUnsignedInt(inputStream, tableIndex, NO_PARAMETERS_MESSAGE, INVALID_TABLE_INDEX_MESSAGE, NEGATIVE_TABLE_INDEX_MESSAGE))
      {
        size_t cellIndex;

        if (nextUnsignedInt(inputStream, cellIndex, NO_SECOND_AND_THIRD_PARAMETER_MESSAGE, INVALID_CELL_INDEX_MESSAGE, NEGATIVE_CELL_INDEX_MESSAGE))
        {
          int value;

          if (nextInt(inputStream, value, NO_THIRD_PARAMETER_MESSAGE, INVALID_VALUE_MESSAGE))
          {
            try
            {
              tableContainer.editTable(tableIndex, cellIndex, value);

              std::cout << CELL_VALUE_MESSAGE << cellIndex << OF_TABLE_MESSAGE << tableIndex << SET_TO_MESSAGE << value << std::endl;
            }
            catch (const std::exception &e)
            {
              std::cerr << e.what() << std::endl;
            }
          }
        }
      }
    }
    else if (command == HELP_COMMAND)
    {
      std::cout << HELP_MESSAGE << std::endl;
    }
    else if (command != QUIT_COMMAND)
    {
      std::cout << INVALID_COMMAND_MESSAGE << std::endl;
    }
  }
}