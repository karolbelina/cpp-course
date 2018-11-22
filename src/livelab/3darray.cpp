#include "3darray.h"

bool createTable(int x, int y, int z, int**** table) {
	if(x > 0 && y > 0 && z > 0) {
		*table = new int**[x];

		for(int i = 0; i < x; i++) {
			(*table)[i] = new int*[y];

			for(int j = 0; j < y; j++) {
				(*table)[i][j] = new int[z];
			}
		}

		return true;
	}
	else {
		return false;
	}
}

bool changeTable(int oldX, int oldY, int oldZ, int newX, int newY, int newZ, int**** table) {
	int*** temp;

	if(createTable(newX, newY, newZ, &temp)) {
		for(int i = 0; i < newX && i < oldX; i++) {
			for(int j = 0; j < newY && j < oldY; j++) {
				for(int k = 0; k < newZ && k < oldZ; k++) {
					temp[i][j][k] = (*table)[i][j][k];
				}
			}
		}

		deleteTable(oldX, oldY, oldZ, *table);
		*table = temp;

		return true;
	}
	else {
		return false;
	}
}

void deleteTable(int x, int y, int z, int*** table) {
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			delete table[i][j];
		}

		delete table[i];
	}

	delete table;
}

void setValue(int x, int y, int z, int value, int*** table) {
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			for(int k = 0; k < z; k++) {
				table[i][j][k] = value;
			}
		}
	}
}

double getAverage(int x, int y, int z, int *** table) {
	int sum = 0;

	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			for(int k = 0; k < z; k++) {
				sum += table[i][j][k];
			}
		}
	}

	return (double)sum / x / y / z;
}