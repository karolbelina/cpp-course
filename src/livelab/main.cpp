#include "3darray.h"

int main() {
	int*** table;

	createTable(0, 5, 6, &table);
	createTable(3, 5, 6, &table);
	setValue(3, 5, 6, 55, table);

	table[0][4][5] = 0;
	getAverage(3, 5, 6, table);

	changeTable(3, 5, 6, 1, 2, 3, &table);
	getAverage(1, 2, 3, table);

	setValue(1, 2, 3, 0, table);
	table[0][1][1] = 6;

	getAverage(1, 2, 3, table);
	deleteTable(1, 2, 3, table);
}