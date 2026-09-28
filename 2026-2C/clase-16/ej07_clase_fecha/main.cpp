#include <iostream>

class claseFecha
{
	int dia{};
	int mes{};
	int anio{};
public:
	void imprimir ()
	{
		std::cout << dia << "/" << mes << "/" << anio << std::endl ;
	}
	void setFecha (int day, int month, int year)
	{
		if (day > 0 && day <= 31)
			dia = day;
		if (month > 0 && month <= 12)
			mes = month;
		if (year > 1960 && year < 2026)
			anio = year;
	}
};

int main (void)
{
	claseFecha c1;
	c1.setFecha (100 , 05 , 1990);
	c1.imprimir ();
	return 0;
}

