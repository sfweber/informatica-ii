int main ()
{
    int *ptr {new int};

    ptr = new int {0};           // el primer bloque queda perdido -> leak

    delete ptr;                  // solo libera el segundo
    return 0;
}
