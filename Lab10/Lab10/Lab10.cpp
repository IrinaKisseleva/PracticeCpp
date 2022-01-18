#include <vector>
#include <iostream>
#include <algorithm>


template<typename T>
class SortedVector : public std::vector<T> {
public:
	SortedVector(std::initializer_list<T> init_list) : std::vector<T>(init_list) { // принимаем список инициализации и вызываем базовый класс
		std::sort(std::vector<T>::begin(), std::vector<T>::end());
	}
};

int main() {
	SortedVector<int>({ 2, 1, 5, 4});

	return 0;
}