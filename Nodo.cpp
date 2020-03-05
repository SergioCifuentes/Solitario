
#include <iostream>
#include "carta.cpp"
using namespace std;

class Nodo
{
    public:

    carta cartaNueva;
    Nodo *prev;
    Nodo *next;
    
private:
    friend class LinkedList;
};