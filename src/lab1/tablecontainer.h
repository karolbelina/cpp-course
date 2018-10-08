#include <vector>

#include "table.h"
#include "error.h"

class TableContainer {
public:
	~TableContainer(); // kasuj tabelki z pamieci a pozniej wskazniki z wektora !!!!!!!!!!!!

	void addTable(std::string name, int tableLength, Error &error);
	void removeTable(int tableIndex, Error &error);
	void removeAllTables();
	void renameTable(int tableIndex, std::string name, Error &error);
	void resizeTable(int tableIndex, int tableLength, Error &error);
	void cloneTable(int tableIndex, Error &error);
	std::string getTableStatus(int tableIndex, Error &error);
	std::string getStatus();
	void editTable(int tableIndex, int cellIndex, int value, Error &error);
	int size();

private:
	std::vector<Table*> tables;
};