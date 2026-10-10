#ifndef MISTRING_H
#define MISTRING_H

class miString
{
private:
    char* m_texto {nullptr};
    int m_largo ;                    // cantidad de caracteres, sin contar el '\0'

public:
    miString (const char*);
    ~miString ();
    void imprimir (void);
    char getCaracter (int);
    void cargar (const char*);
    int getLargo (void);
    void agregar (const char*);
};

#endif
