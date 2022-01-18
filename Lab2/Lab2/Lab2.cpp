#include <iostream>
#include <ctime> 

int N;

double fRand(const double MIN, const double MAX)
{
	double f = (double)rand() / (RAND_MAX + 1);
	return MIN + f * (MAX - MIN + 1.0);
}

void fMultiplication(double** A, double** B, double** C) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			C[i][j] = 0;
			for (int counter = 0; counter < N; counter++) {
				C[i][j] += A[i][counter] * B[counter][j];

			}
		}
	}
}

int main (){

	srand(static_cast<unsigned int>(time(0)));//получение текущего времени, преоразованию к типу int
	setlocale(LC_ALL, "Russian");

	const double MAX = 10.0;
	const double MIN = 0.0;

	std::cout << "Введите значение N";
	std::cin >> N;
	std::cout << "\n Массив A \n";

	double ** A = new double* [N];
	double ** B = new double* [N];
	double ** C = new double* [N];

	for (int i = 0; i < N; i++) {
		A[i] = new double[N];
		B[i] = new double[N];
		C[i] = new double[N];
		for (int j = 0; j < N; j++) {
			A[i][j] = fRand(MIN, MAX);
			B[i][j] = fRand(MIN, MAX);
			std::cout << A[i][j] << "  ";
		}
		std::cout << "\n";
	}

	std::cout << "\n Массив B \n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << B[i][j] << "  ";
		}
		std::cout << "\n";
	}

	std::cout << "\n Массив C \n";
	fMultiplication(A, B, C);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cout << C[i][j] << "  ";
		}
		std::cout << "\n";
	}
}
