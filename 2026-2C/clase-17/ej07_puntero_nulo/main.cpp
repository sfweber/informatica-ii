#include <iostream>

int main ()
{
    int *ptr {nullptr};

    if (!ptr)
        ptr = new int {8};

    std::cout << "ptr: " << ptr << "\t*ptr: " << *ptr << '\n';

    delete ptr;
    ptr = nullptr;
    return 0;
}
