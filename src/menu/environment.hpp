#pragma once

#include "command.hpp"

#include <map>

namespace menu
{
  struct Environment
  {
    std::map<std::string, Command*> map;

    Environment(std::initializer_list<std::pair<const std::string, Command*>> list) : map(list)
    {
    }

    ~Environment()
    {
      for (std::pair<std::string, Command*> pair : map)
      {
        delete pair.second;
      };
    }
  };
}