#include <iostream>
#include <functional>
#include <cmath>

// https://tfetimes.com/c-function-composition/

template <typename T>
T identity(T x) {
    return x;
}

int main() {
	std::cout << identity(0.5) << std::endl;

	return 0;
}
