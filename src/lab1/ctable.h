#include <string>
#include <vector>

class CTable {
private:
	std::string name;
	int* array;
	int arraySize;

public:
	CTable(int* state);
	CTable(std::string name, int tableLength, int* state);
	CTable(const CTable &other);
	~CTable();
	void setName(std::string name);
	void setTableLength(int tableLength, int *state);
	void setElement(int offset, int value, int *state);
	int getElement(int offset, int *state);
	CTable clone();
	void setTable(const CTable &other);
	std::string getStatus();
};