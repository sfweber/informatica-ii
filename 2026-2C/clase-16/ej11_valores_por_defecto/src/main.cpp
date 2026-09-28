#include <iostream>
#include "fecha.h"

int main (void)
{
	cFecha c1 {17};
	cFecha c2;
	c1.imprimir ();
	c1.setFecha (10 , 05 , 1990);
	c1.imprimir ();
	return 0;
}

