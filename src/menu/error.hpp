#pragma once

#include <sstream>
#include <vector>

namespace menu
{
  class parse_error : public std::runtime_error
  {
  public:
    parse_error(const char* msg) : runtime_error(msg)
    {
    }
    parse_error(const std::string &msg) : runtime_error(msg)
    {
    }
  };
}