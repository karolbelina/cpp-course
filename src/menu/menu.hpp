#pragma once

#include "command.hpp"
#include "environment.hpp"
#include "error.hpp"
#include "menucommand.hpp"
#include "menuitem.hpp"

#include <vector>

namespace menu
{
  class Menu : public MenuItem
  {
  public:
    friend void MenuItem::parseAndValidateString(const std::string &, size_t &, std::string &, Menu*);
    friend static MenuItem* MenuItem::importItem(const std::string&, const Environment&);

    Menu() = delete;
    Menu(const Menu &other);
    ~Menu();
    Menu& operator=(const Menu &other);
    MenuItem* clone() const override;

    void run() override;

  private:
    Menu(Menu* parent, const std::string &source, size_t &position, const Environment &environment);

    Menu* getRoot();
    bool search(std::string &term, std::string path, std::ostream &stream, bool &separator) override;
    std::string getHelp() const override;
    std::string exportItem() const override;

    std::vector<MenuItem*> items;
  };
}