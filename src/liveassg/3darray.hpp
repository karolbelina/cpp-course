#pragma once

bool createTable(int x, int y, int z, int**** table);
bool changeTable(int oldX, int oldY, int oldZ, int newX, int newY, int newZ, int**** table);
void deleteTable(int x, int y, int z, int*** table);
void setValue(int x, int y, int z, int value, int*** table);
double getAverage(int x, int y, int z, int*** table);