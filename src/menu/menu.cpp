#include "constants.h"
#include "menu.h"
#include "menucommand.h"

#include <iostream>
#include <sstream>
#include <string>

menu::Menu::Menu(const Menu &other) : MenuItem(other)
{
  for (MenuItem* item : other.items)
  {
    items.push_back(item->clone());
  }
}

menu::Menu::~Menu()
{
  for (MenuItem* item : items)
  {
    delete item;
  }
}

menu::Menu& menu::Menu::operator=(const Menu &other)
{
  if (this == &other)
  {
    return *this;
  }

  MenuItem::operator=(other);

  for (MenuItem* item : items)
  {
    delete item;
  }

  items.clear();

  for (MenuItem* item : other.items)
  {
    items.push_back(item->clone());
  }

  return *this;
}

menu::MenuItem* menu::Menu::clone() const
{
  return new Menu(*this);
}

bool menu::Menu::search(std::string &term, const std::string path, std::ostream &stream, bool &separator)
{
  std::string currentPath = path + commandString + SLASH;
  bool foundCommands = false;

  for (MenuItem* item : items)
  {
    if (item->search(term, currentPath, stream, separator))
    {
      foundCommands = true;
    }
  }

  return foundCommands;
}

std::string menu::Menu::getHelp() const
{
  return std::string();
}

std::string menu::Menu::exportItem() const
{
  std::ostringstream stream;

  stream << LEFT_PARENTHESIS << APOSTROPHE << name << APOSTROPHE << COMMA;
  stream << APOSTROPHE << commandString << APOSTROPHE << SEMICOLON;

  std::string separator = std::string();
  for (MenuItem* item : items)
  {
    stream << separator << item->exportItem();
    separator = COMMA;
  }

  stream << RIGHT_PARENTHESIS;

  return stream.str();
}

void menu::Menu::run()
{
  bool retryInput = true;

  do
  {
    std::cout << std::endl << name << std::endl;
    std::cout << std::string(PADDING, SPACE);
    std::cout << BACK_COMMAND << std::endl;
    for (MenuItem* item : items)
    {
      std::cout << std::string(PADDING, SPACE);
      std::cout << item->name << SPACE << LEFT_PARENTHESIS << item->commandString << RIGHT_PARENTHESIS << std::endl;
    }
    std::cout << PROMPT << SPACE;

    std::string input;
    std::getline(std::cin, input);

    if (input != BACK_COMMAND)
    {
      bool foundValidCommand = false;

      std::istringstream stream(input);
      std::string command;
      stream >> command;

      if (command == SEARCH_COMMAND)
      {
        std::string parameter;
        stream >> parameter;

        std::ostringstream output;
        bool separator = false;

        if (getRoot()->search(parameter, std::string(), output, separator))
        {
          std::cout << output.str() << std::endl;
        }
        else
        {
          std::cout << NO_MATCHES_MESSAGE << std::endl;
        }

        foundValidCommand = true;
      }
      else if (command == HELP_COMMAND)
      {
        std::string parameter;
        stream >> parameter;

        bool foundCommand = false;
        for (MenuItem* item : items)
        {
          if (parameter == item->commandString)
          {
            std::string help = item->getHelp();

            if (!help.empty())
            {
              foundCommand = true;
              std::cout << help << std::endl;
            }
          }
        }

        if (!foundCommand)
        {
          std::cout << NO_HELP_AVAILABLE_MESSAGE << std::endl;
        }

        foundValidCommand = true;
      }
      else
      {
        for (MenuItem* item : items)
        {
          if (input == item->commandString)
          {
            item->run();

            foundValidCommand = true;
          }
        }
      }

      if (!foundValidCommand)
      {
        std::cout << INVALID_COMMAND_MESSAGE << std::endl;
      }
    }
    else
    {
      retryInput = false;
    }
  }
  while (retryInput);
}

menu::Menu::Menu(Menu* parent, const std::string &source, size_t &position, const Environment &environment)
{
  this->parent = parent;
  std::string temporaryCommandString;

  parseCharacter(source, position, LEFT_PARENTHESIS);
  parseString(source, position, name);
  parseCharacter(source, position, COMMA);
  parseAndValidateString(source, position, commandString, parent);
  parseCharacter(source, position, SEMICOLON);

  while (source[position] == LEFT_PARENTHESIS || source[position] == LEFT_SQUARE_BRACKET)
  {
    if (source[position] == LEFT_PARENTHESIS)
    {
      items.push_back(new Menu(this, source, position, environment));
    }
    else if (source[position] == LEFT_SQUARE_BRACKET)
    {
      items.push_back(new MenuCommand(this, source, position, environment));
    }

    if (source[position] == RIGHT_PARENTHESIS)
    {
      ++position;
      return;
    }
    else if (source[position] == COMMA)
    {
      ++position;
    }
    else
    {
      throw menu::parse_error("expected ')' or ',' on position " + std::to_string(position));
    }

    if (source[position] != LEFT_PARENTHESIS && source[position] != LEFT_SQUARE_BRACKET)
    {
      throw menu::parse_error("expected '(' or '[' on position " + std::to_string(position));
    }
  }

  if (source[position] == RIGHT_PARENTHESIS)
  {
    ++position;
    return;
  }
  else
  {
    throw menu::parse_error("expected ')', '(' or '[' on position " + std::to_string(position));
  }
}

menu::Menu* menu::Menu::getRoot()
{
  Menu* item = parent;

  if (item == nullptr)
  {
    return this;
  }

  while (item != nullptr)
  {
    item->parent;
  }

  return item;
}