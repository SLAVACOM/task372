#pragma once


int task();

void readFromConsole(int& matrix_n, int& matrix_m);
void printConsole(double** matrix, int& matrix_n, int& matrix_m);
bool readFromFile(const char* input, int& matrix_n, int& matrix_m);

void writeToFile(const char* output, double** matrix, int& matrix_n, int& matrix_m);
void freeMatrix(double**& matrix, int& matrix_n);