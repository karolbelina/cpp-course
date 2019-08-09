#pragma once

#include "command.hpp"
#include "environment.hpp"
#include "error.hpp"

#include <map>
#include <string>

#include <string>

namespace menu
{
  class Menu;

  class MenuItem
  {
  public:
    friend class Menu; // accessing fields directly without the use of getters which may be visible to the user

    MenuItem();
    MenuItem(const MenuItem &other);
    virtual ~MenuItem();
    MenuItem& operator=(const MenuItem &other);
    virtual MenuItem* clone() const = 0;

    virtual void run() = 0;

    static std::string exportItem(const MenuItem &item);
    static MenuItem* importItem(const std::string &source, const Environment &environment);

  protected:
    virtual bool search(std::string &term, std::string path, std::ostream &stream, bool &separator) = 0;
    virtual std::string getHelp() const = 0;
    virtual std::string exportItem() const = 0;

    static void parseString(const std::string &source, size_t &position, std::string &destination);
    static void parseAndValidateString(const std::string &source, size_t &position, std::string &destination, Menu* parent);
    static void parseCharacter(const std::string &source, size_t &position, const char character);

    std::string name;
    std::string commandString;
    Menu* parent;
  };
}