#include <iostream>

using namespace std;

class carta
{
private:
    
public:

    carta();
    int numero;
    int simbolo;
    bool descubierto;
    void setAtributos(int numero1,int simbolo1,bool descubierto1);
    ~carta();
};

carta::carta(/* args */)
{
    numero=0;
    simbolo=0;
}

void carta:: setAtributos(int numero1,int simbolo1,bool descubierto1){
   numero=numero1;
    simbolo=simbolo1;
    descubierto=descubierto1;  
}


carta::~carta()
{
}
