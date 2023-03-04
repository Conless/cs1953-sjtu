// sample
#include "ArrayList.hpp"

template<class T>
void printList(const ArrayList<T> &list) {
#ifdef USE_OS
    std::cout << list << "\n";
#else
    list.print();
    std::cout << "\n";
#endif
}

int main() {
    try {
        ArrayList<char> list_err(-1);
    } catch (error &e) {
        std::cout << e.toString() << std::endl;
    }
    ArrayList<int> list(5);
    try {
        list[-1];
    } catch (error &e) {
        std::cout << e.toString() << std::endl;
    }
    try {
        list[2000];
    } catch (error &e) {
        std::cout << e.toString() << std::endl;
    }
    
    for (int i = 0; i < list.size(); i++) list[i] = i;
    printList(list);
    ArrayList<int> temp = list;
    printList(temp);
    temp = list;
    list[3] = 721894;
    printList(temp);
    if (temp == list) std::cout << "true" << std::endl;
    
    int arr[5] = {4, 215, 12, 84, 76};
    const ArrayList<int> list_const(arr, 5);
    std::cout << list_const[3] << std::endl;
    printList(list_const);
    
    printList(list_const + list);
    
    return 0;
}
