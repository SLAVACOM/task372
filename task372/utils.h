#pragma once


int task();

void readFromConsole(int& matrix_n, int& matrix_m);
void printConsole(int** matrix, int& matrix_n, int& matrix_m);
bool readFromFile(const char* input, int& matrix_n, int& matrix_m);

void writeToFile(const char* output, int** matrix, int& matrix_n, int& matrix_m);
void freeMatrix(int**& matrix, int& matrix_n);