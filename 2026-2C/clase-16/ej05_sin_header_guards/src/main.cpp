#include <iostream>
#include "suma.h"
#include "producto.h"

int main()
{
    std::cout << "2 x 3 = " << producto (2,3) << '\n';
    std::cout << "2 + 3 = " << suma (2,3) << '\n';
    return 0;
}
