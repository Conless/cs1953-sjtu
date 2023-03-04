#include <iostream>

void debugPrint() { std::cout << std::endl; }

template <typename Type, typename... Types> void debugPrint(Type arg, Types ...args) {
    std::cout << arg << " ";
    debugPrint(args...);
}