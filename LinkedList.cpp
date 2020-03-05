#include <iostream>
#include "Nodo.cpp"
using namespace std;

class LinkedList
{
private:
    Nodo *header;
    Nodo *trailer;

public:
    LinkedList(/* args */);
    ~LinkedList();
    carta getFront() const;
    carta getBack() const;
    int getNumeroDeElementos() const;
    carta getCartaPorIndice(int indice) const;
    int getIndiceDescubierto(int numero);
    void addBack(carta carta);
    void printFront();
    void removeBack();
    void descubirBack();
};

LinkedList::LinkedList(/* args */)
{
    header = new Nodo;
    trailer = new Nodo;
    header->next = trailer;
    trailer->prev = header;
    header->prev = NULL;
    trailer->next = NULL;
}

carta LinkedList::getFront() const
{
    return header->next->cartaNueva;
}

carta LinkedList::getBack() const
{
    return trailer->prev->cartaNueva;
}

int LinkedList::getNumeroDeElementos() const
{
    Nodo *nd = header->next;
    int aux = 0;
    while (nd != trailer)
    {
        nd = nd->next;
        aux = aux + 1;
    }
    return aux;
}

carta LinkedList::getCartaPorIndice(int indice) const
{
    Nodo *nd = header;
    for (int i = 0; i < indice; i++)
    {
        nd = nd->next;
    }

    return nd->cartaNueva;
}

int LinkedList::getIndiceDescubierto(int numero)
{
    Nodo *nd = header->next;
    int aux = 0;
    while (nd != trailer)
    {
        aux = aux + 1;
        cout << "  ";
        cout << nd->cartaNueva.numero;
        cout << aux;
        cout << " \n ";
        if (nd->cartaNueva.numero == numero & nd->cartaNueva.descubierto == true)
        {
            return aux;
        }
        nd = nd->next;
    }
    return 0;
}

void LinkedList::addBack(carta carta)
{
    Nodo *nd = new Nodo;
    nd->cartaNueva = carta;
    nd->next = trailer;
    nd->prev = trailer->prev;
    trailer->prev->next = nd;
    trailer->prev = nd;
}

void LinkedList::removeBack()
{
    Nodo *nd = trailer->prev->prev;

    trailer->prev = nd;
    nd->next = trailer;
}
void LinkedList ::descubirBack()
{
    Nodo *nd = trailer->prev;
    nd->cartaNueva.descubierto = true;
}

void LinkedList::printFront()
{
    Nodo *nd = header->next;
    while (nd != trailer)
    {
        cout << nd->cartaNueva.numero << " ";
        nd = nd->next;
    }
}
LinkedList::~LinkedList()
{
    while (header->next != trailer)
    {
        removeBack();
    }
    delete header;
    delete trailer;
}