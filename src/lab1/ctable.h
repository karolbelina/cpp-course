#include <string>

class CTable {
private:
	std::string name;
	int* array;

public:
	CTable();
	CTable(std::string name, int tableLength);
	CTable(CTable &other);
	~CTable();
	void setName(std::string name);
	void setTableLength(int tableLength, int *success);
	void setElement(int index, int value, int *success);
	int getElement(int offset, int *success);
	CTable clone();
	void setTable(CTable &other);
	std::string getStatus();
};