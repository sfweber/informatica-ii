#ifndef FECHA_H
#define FECHA_H

class cFecha
{
	int dia{};
	int mes{};
	int anio{};
public:
	cFecha ();
	cFecha (int, int, int);
	void imprimir () ;
	void setFecha (int , int , int );
};

#endif //FECHA_H