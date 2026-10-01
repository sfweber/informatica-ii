#include <iostream>
#include <cstdlib>

// malloc reserva bytes; new construye un objeto.
class miClase
{
public:
    miClase ()  { std::cout << "constructor\n"; }
    ~miClase () { std::cout << "destructor\n"; }
};

int main ()
{
    std::cout << "--- malloc / free ---\n";
    miClase *p1 = (miClase *) malloc (sizeof (miClase));
    free (p1);

    std::cout << "--- new / delete ---\n";
    miClase *p2 = new miClase;
    delete p2;
    return 0;
}
