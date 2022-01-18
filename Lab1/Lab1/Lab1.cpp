#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <cstdio>

int main()
{
	srand(static_cast<unsigned int>(time(0)));//получение текущего времени, преоразованию к типу int
	setlocale(LC_ALL, "Russian");

	const int N = 3;
	const int MAX = 11;
	int array[N][N];
	int sum_upper = 0;
	int sum_lower = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			array[i][j] = rand() % MAX;
			printf ("%d   ",array[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < N; i++) {
		int s = 5;
		for (int j = 0; j < N; j++) {
			if (j + i > N-1 ) {
				sum_lower += array[i][j];
			}
			else if (j + i < N-1) {
				sum_upper += array[i][j];
			}
		}
	}
	printf("%d   ", sum_lower);
	printf("%d   ", sum_upper);
	if (sum_lower > sum_upper) {
		printf("Сумма элементов ниже главной диагонали больше на %d", sum_lower-sum_upper);
	}
	else if (sum_lower < sum_upper)
	{
		printf("Сумма элементов выше главной диагонали больше на %d", sum_upper-sum_lower);
	}
	else {
		printf("Суммы равны");
	}

}

