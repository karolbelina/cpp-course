#pragma once

#include "table.hpp"

#include <vector>

namespace table
{
  class TableContainer
  {
  public:
    ~TableContainer();

    void addTable(std::string name, size_t tableLength);
    void removeTable(size_t tableIndex);
    void removeAllTables();
    void renameTable(size_t tableIndex, std::string name);
    void resizeTable(size_t tableIndex, size_t tableLength);
    void cloneTable(size_t tableIndex);
    std::string getTableStatus(size_t tableIndex);
    std::string getStatus();
    void editTable(size_t tableIndex, size_t cellIndex, int value);
    size_t tableCount();

  private:
    Table* getTable(size_t tableIndex);
    std::vector<Table*> tables;
  };
}