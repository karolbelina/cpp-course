#include "constants.h"
#include "menu.h"
#include "menuitem.h"

menu::MenuItem::MenuItem()
{
}

menu::MenuItem::MenuItem(const MenuItem &other) :
  name(other.name), commandString(other.commandString), parent(other.parent)
{
}

menu::MenuItem::~MenuItem()
{
}

menu::MenuItem& menu::MenuItem::operator=(const MenuItem &other)
{
  if (this == &other)
  {
    return *this;
  }

  name = other.name;
  commandString = other.commandString;
  parent = other.parent;

  return *this;
}

std::string menu::MenuItem::exportItem(const MenuItem &item)
{
  return item.exportItem();
}

menu::MenuItem* menu::MenuItem::importItem(const std::string &source, const Environment &environment)
{
  size_t position = 0;
  menu::MenuItem* item = nullptr;

  if (source[position] == LEFT_PARENTHESIS)
  {
    item = new menu::Menu(nullptr, source, position, environment);
  }
  else if (source[position] == LEFT_SQUARE_BRACKET)
  {
    item = new menu::MenuCommand(nullptr, source, position, environment);
  }
  else
  {
    throw menu::parse_error("expected '(' or '[' on position " + std::to_string(position));
  }

  return item;
}

void menu::MenuItem::parseString(const std::string &source, size_t &position, std::string &destination)
{
  if (source[position] != APOSTROPHE)
  {
    throw menu::parse_error("expected an apostrophe on position " + std::to_string(position));
  }

  size_t beginPosition = ++position;

  while (source[position] != APOSTROPHE)
  {
    if (source[position] == NULL)
    { // end of string
      throw menu::parse_error("mismatched apostrophes");
    }

    ++position;
  }

  destination = source.substr(beginPosition, position - beginPosition);
  ++position;
}

void menu::MenuItem::parseAndValidateString(const std::string &source, size_t &position, std::string &destination, Menu* parent)
{
  std::string temp;
  parseString(source, position, temp);

  std::istringstream stream(temp);
  std::string validatedString;

  stream >> validatedString;

  if (validatedString.empty() && parent != nullptr)
  { // root can be ''
    throw menu::parse_error("empty element on position " + std::to_string(position - 1));
  }

  if (validatedString == BACK_COMMAND || validatedString == SEARCH_COMMAND || validatedString == HELP_COMMAND)
  {
    throw menu::parse_error("invalid element on position " + std::to_string(position - 1));
  }

  if (parent != nullptr)
  {
    for (MenuItem* item : parent->items)
    {
      if (validatedString == item->commandString)
      {
        throw menu::parse_error("duplicate element on position " + std::to_string(position - 1));
      }
    }
  }

  destination = validatedString;
}

void menu::MenuItem::parseCharacter(const std::string &source, size_t &position, const char character)
{
  if (source[position] != character)
  {
    throw menu::parse_error("expected '" + std::string(1, character) + "' on position " + std::to_string(position));
  }

  ++position;
}