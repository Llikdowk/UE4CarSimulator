#include <iostream>

template<typename T> 
T add(T a) {
    return a;
}

template<typename T, typename... Args>
T add(T first, Args... tail) {
    return first + add(tail...);
}

int main() {

    std::cout << add(5, 5, 5, 5) << std::endl;

    int x;
    std::cin >> x;
    return 0;
}