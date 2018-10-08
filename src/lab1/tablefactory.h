#include "table.h"

class TableFactory {
public:
	static Table* createDefaultTable(int &error);
	static Table* createTableFromParameters(std::string name, int tableLength, int &error);
	static Table* createTableFromTable(const Table &other, int &error);

private:
	static Table* checkErrors(Table* other, int &error);
};