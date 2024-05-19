#include <regex>
#include <iostream>
#include "constants.h"

#include "utils.h"
#include <fstream>

using namespace std;

int task() {
	regex valid_input("^[01]$");
	
	string input;
	char in_option, out_option;
	int matrix_n, matrix_m;

	do {
		do {
			cout << "Введите '0' для ввода с консоли, '1' для ввода из файла: ";
			getline(cin, input);
		} while (!regex_match(input, valid_input));
		in_option = input[0];

		do {
			cout << "Введите '0' для вывода на консоль, '1' для вывода в файл: ";
			getline(cin, input);
		} while (!regex_match(input, valid_input));
		out_option = input[0];

		if (in_option == '0') {
			readFromConsole(matrix_n, matrix_m);
		}
		else if (in_option == '1') {
			if (!readFromFile(constants::input, matrix_n, matrix_m)) {
				return 1;
			}
		}

		double** matrix = new double* [matrix_n];
		for (int i{ 0 }; i < matrix_n; i++) {
			matrix[i] = new double[matrix_m];
		}
		
		for (int i{ 0 }; i < matrix_m; i++){
			matrix[0][i] = 2 * (i + 1) + 3;
		}
		
		if (matrix_n >= 2) {
			for (int i{ 0 }; i < matrix_m; i++){
				matrix[1][i] = (i + 1) - (3 / (2 + 1. / (i + 1)));
			}
		}

		for (int i{2}; i < matrix_n; i++) {
			for (int j{ 0 }; j < matrix_m; j++) {
				matrix[i][j] = matrix[i - 1][j] + matrix[i - 2][j];
			}
		}

		if (out_option == '0') {
			printConsole(matrix, matrix_n, matrix_m);
		}
		else if (out_option == '1'){
			writeToFile(constants::output, matrix, matrix_n, matrix_m);
		}

		freeMatrix(matrix, matrix_n);
		if (in_option == '0') {
			do {
				cout << "Введите '0' для повтора программы, '1' для завершения программы: ";
				getline(cin, input);
			} while (!regex_match(input, valid_input));
			in_option = input[0];
		}
	} while (in_option != '1');
	return 0;
}

void readFromConsole(int& matrix_n, int& matrix_m) {
	regex valid_number("[1-9][0-9]*");
	string input;

	do {
		cout << "Введите количесто строк (n): ";
		getline(cin, input);
	} while (!regex_match(input, valid_number));

	matrix_n = stoi(input);

	do {
		cout << "Введите количесто столбцов (m): ";
		getline(cin, input);
	} while (!regex_match(input, valid_number));
	matrix_m = stoi(input);
}

bool readFromFile(const char* input,  int& matrix_n, int& matrix_m) {
	ifstream file(input);

	if (!file.is_open()) {
		cerr << "Ошибка при открытии файла с входнымми данными" << endl;
		return false;
	}
	if (!(file >> matrix_n >> matrix_m)) {
		cerr << "Ошибка чтения файла с входнымми данными" << std::endl;
		file.close();
		return false;
	}
	char e;
	if (file >> e) {
		cerr << "Неверные данные в файле" << std::endl;
		file.close();
		return false;
	}

	return true;
}


void printConsole(double** matrix, int& matrix_n, int& matrix_m) {
	for (int i{ 0 }; i < matrix_n; i++) {
		for (int j{ 0 }; j < matrix_m; j++) {
			cout << matrix[i][j] << "  ";
		}
		cout << endl;
	}
}

void writeToFile(const char* output, double** matrix, int& matrix_n, int& matrix_m) {
	ofstream outputFile(output);
	if (!outputFile.is_open()) {
		cout << "Ошибка при открытии файла для записи" << endl;
	}
	else {
		for (int i{ 0 }; i < matrix_n; i++) {
			for (int j{ 0 }; j< matrix_m; j++) {
				outputFile << matrix[i][j] << "  ";
			}
			outputFile << endl;
		}
		cout << "Результат программы записан в файл: " << output << endl;

	}
	outputFile.close();
}


void freeMatrix(double**& matrix, int& matrix_n) {
	for (int i{ 0 }; i < matrix_n; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = nullptr;
}
