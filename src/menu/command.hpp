#pragma once

namespace menu
{
  class Command
  {
  public:
    virtual Command* clone() const;
    virtual void runCommand() const;
  };
}