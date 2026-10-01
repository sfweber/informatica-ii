#include <iostream>

int main ()
{
    int *ptr {new int {5}};
    std::cout << "ptr: " << ptr << "\t*ptr: " << *ptr << '\n';

    delete ptr;
    ptr = nullptr;               // ahora el error deja de ser silencioso

    std::cout << "\nVamos otra vez:\n"
              << "ptr: " << ptr << "\t*ptr: " << *ptr << '\n';   // se cae (segfault), a proposito
    return 0;
}
