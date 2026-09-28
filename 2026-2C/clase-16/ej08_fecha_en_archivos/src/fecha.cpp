#include <iostream>
#include "fecha.h"


void cFecha::imprimir ()
{
    std::cout << dia << "/" << mes << "/" << anio << std::endl ;
}
void cFecha::setFecha (int day, int month, int year)
{
    if (day > 0 && day <= 31)
        dia = day;
    if (month > 0 && month <= 12)
        mes = month;
    if (year > 1960 && year < 2026)
        anio = year;
}