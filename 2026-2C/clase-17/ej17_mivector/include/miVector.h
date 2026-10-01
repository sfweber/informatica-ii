#ifndef MIVECTOR_H
#define MIVECTOR_H

class miVector 
{
private:
    int* n_vector {nullptr} ;
    int n_tam ;
public:
    miVector (int);
    ~miVector ();
    void setValor (int valor , int pos);
    int getValor (int pos);
    int getTam (void);

};

#endif 