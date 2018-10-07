#include <string>

class Table {
public:
	Table();
	Table(std::string name, int tableLength, int* error);
	Table(const Table &other);
	~Table();

	void setName(std::string name);
	void setTableLength(int tableLength, int* error);
	void setElement(int offset, int value, int* error);
	int getElement(int offset, int* error);
	Table* clone();
	void setTable(const Table &other);
	std::string getStatus();

private:
	std::string name;
	int* array;
	int arraySize;
};