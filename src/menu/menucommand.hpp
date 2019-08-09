#pragma once

#include "command.hpp"
#include "error.hpp"
#include "environment.hpp"
#include "menuitem.hpp"

#include <map>

namespace menu
{
  class MenuCommand : public MenuItem
  {
  public:
    friend class Menu; // accessing the private constructor
    friend static MenuItem* MenuItem::importItem(const std::string &, const Environment &);

    MenuCommand() = delete;
    MenuCommand(const MenuCommand &other);
    ~MenuCommand();
    MenuCommand& operator=(const MenuCommand &other);
    MenuItem* clone() const override;

    void run() override;

  private:
    MenuCommand(Menu* parent, const std::string &source, size_t &position, const Environment &environment);

    bool search(std::string &term, std::string path, std::ostream &stream, bool &separator) override;
    std::string getHelp() const override;
    std::string exportItem() const override;

    std::string help;
    Command* command;
  };
}