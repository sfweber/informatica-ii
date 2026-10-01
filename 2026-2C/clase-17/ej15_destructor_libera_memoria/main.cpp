#include <iostream>

class miClase
{
    int *data;
public:
    miClase ();
    ~miClase ();
};

miClase::miClase ()
{
    std::cout << "Estamos en el constructor\n";
    data = new int[20];          // el objeto adquiere el recurso al nacer
}

miClase::~miClase ()
{
    std::cout << "Estamos en el destructor\n";
    delete[] data;               // y lo libera al morir
}

void crearObjeto (void);

int main ()
{
    crearObjeto ();
    return 0;
}

void crearObjeto (void)
{
    miClase obj1;
}
