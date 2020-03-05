#include <iostream>
#include <cstdlib>
#include "LinkedList.cpp"



using namespace std;
void empezarJuego();
int main()
{

    bool seguiJugando = true;
    while (seguiJugando)
    {
        cout << "[1] Nuevo Juego \n[2] Salir \n";

        int opcion;
        cin >> opcion;
        switch (opcion)
        {
        case 1:

            empezarJuego();
            break;

        case 2:
            seguiJugando = false;
            break;

        default:
            break;
        }
    }

    return 0;
}




void generarCartasAlAzar(carta cartas1[]);
void dibujarTablero(LinkedList lli[], LinkedList lls[], LinkedList llf[]);
void pedirMovimiento(bool &salir, LinkedList lls[], LinkedList llf[], LinkedList lli[]);
bool verificarTerminado(LinkedList llf[]);
void borrarListas(LinkedList lls[], LinkedList llf[], LinkedList lli[]);
void empezarJuego()
{
    carta cartas[52];
    generarCartasAlAzar(cartas);

    //listas inferiores
    LinkedList ll[7];
    int aux = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            if (j == i)
            {
                cartas[aux].descubierto = true;
            }

            ll[i].addBack(cartas[aux]);
            aux++;
        }
    }

    //lista Superior
    LinkedList llS[2];
    for (int i = aux; i < 52; i++)
    {
        llS[0].addBack(cartas[aux]);
        aux++;
    }
    //Listas finales
    LinkedList llF[4];

    bool salir = false;
    while (true)
    {
        dibujarTablero(ll, llS, llF);
        pedirMovimiento(salir, llS, llF, ll);
        if (salir)
        {
            cout << "\n";
            cout << "Perdiste" << endl;
            //borrarListas(llS, llF, ll);
            break;
        }
        else if (verificarTerminado(llF))
        {
            //borrarListas(llS, llF, ll);
            cout << "\n";
            cout << "FELIIDADES Ganaste!!!" << endl;

            break;
        }
    }
}
void borrarListas(LinkedList lls[], LinkedList llf[], LinkedList lli[])
{
    for (int i = 0; i < 2; i++)
    {
        lls[i].~LinkedList();
    }
    for (int i = 0; i < 7; i++)
    {
        llf[i].~LinkedList();
    }
    for (int i = 0; i < 4; i++)
    {
        lli[i].~LinkedList();
    }
}

bool verificarTerminado(LinkedList listaF[])
{
    bool verificado = true;
    for (size_t i = 0; i < 4; i++)
    {
        if (listaF[i].getNumeroDeElementos() < 13)
        {
            verificado = false;
        }
    }
    return verificado;
}

int regresarNumDeLetra(char letra);
void subirCarta(LinkedList llf[], char columna, LinkedList &llARemover);
bool verificarSimbolosContrarios(int sim1, int sim2);
void dibujarNumero(int numero1);
int regresarNumeroDeSimbolo(char sim);
void dibujarSimbolo(int numero);

void pedirMovimiento(bool &salir, LinkedList lls[], LinkedList llf[], LinkedList lli[])
{
    char primero;
    char segundo;

    cout << "[v] Verificar Carta \n";
    cout << "[q] Quit \n";
    cout << "Elija la lista de la cual quiere mover \n";
    cin >> primero;
    switch (primero)
    {
    case 'a':
        if (lls[0].getNumeroDeElementos() > 0)
        {
            carta cartaAux = lls[0].getBack();
            cartaAux.descubierto = true;

            lls[1].addBack(cartaAux);
            lls[0].removeBack();
        }
        else if (lls[1].getNumeroDeElementos() > 0)
        {
            int auxLongitud = lls[1].getNumeroDeElementos();
            for (int i = 0; i < auxLongitud; i++)
            {
                carta car = lls[1].getBack();
                car.descubierto = false;
                lls[0].addBack(car);
                lls[1].removeBack();
            }
        }

        break;
    case 'q':
        salir = true;

        break;
    case 'v':
            cout << "\nElija la pila\n";    
            cin >> segundo;
            int elemento;
                cout << "Ingrese el numero de la Pila#";
                cin>>elemento;
            cout<<"\n La carta es: ";
                cout<< lli[regresarNumDeLetra(segundo)-1].getCartaPorIndice(elemento).numero;
            dibujarSimbolo(lli[regresarNumDeLetra(segundo)-1].getCartaPorIndice(elemento).simbolo);    
            cout<<"\n";
        break;

    default:
        cout << "\nElija a El destino de su carta\n";
        cin >> segundo;
        switch (segundo)
        {
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            if (primero == 'b')
            {
                subirCarta(llf, segundo, lls[1]);
            }
            else if (primero == '1' || primero == '2' || primero == '3' || primero == '4' || primero == '5' || primero == '6' || primero == '7')
            {

                subirCarta(llf, segundo, lli[regresarNumDeLetra(primero) - 1]);
            }
            else
            {
                cout << "Movimiento Invalido\n";
            }

            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':

            if (primero == 'b' && lls[1].getNumeroDeElementos() > 0)
            {
                if (lli[regresarNumDeLetra(segundo) - 1].getNumeroDeElementos() > 0)
                {
                    if (lli[regresarNumDeLetra(segundo) - 1].getBack().numero - 1 == lls[1].getBack().numero)
                    {
                        if (verificarSimbolosContrarios(lli[regresarNumDeLetra(segundo) - 1].getBack().simbolo, lls[1].getBack().simbolo))
                        {
                            carta caAux = lls[1].getBack();
                            lli[regresarNumDeLetra(segundo) - 1].addBack(caAux);
                            lls[1].removeBack();
                        }
                        else
                        {
                            cout << "Movimiento Invalido(Mismo Color)\n";
                        }
                    }
                    else
                    {
                        cout << "Movimiento Invalido (";
                        dibujarNumero(lli[regresarNumDeLetra(segundo) - 1].getBack().numero - 1);
                        cout << " Esperado)\n";
                    }
                }
                else
                {
                    if (lls[1].getBack().numero == 13)
                    {
                        carta caAux = lls[1].getBack();
                        lli[regresarNumDeLetra(segundo) - 1].addBack(caAux);
                        lls[1].removeBack();
                    }
                    else
                    {
                        cout << "Movimiento Invalido ('K' necesario) \n";
                    }
                }
            }
            else
            {
                int elemento;
                cout << "Ingrese el numero de la Pila#";
                cout << primero << endl;
                char aux;

                cin >> aux;
                if (aux=='1')
                {
                    elemento=10;
                }else{
                     elemento = regresarNumeroDeSimbolo(aux);
                }
                
               
                int numeroEnPila = lli[regresarNumDeLetra(primero) - 1].getIndiceDescubierto(elemento);
                if (numeroEnPila != 0)
                {
                    if (lli[regresarNumDeLetra(segundo) - 1].getNumeroDeElementos() > 0)
                    {
                        if (lli[regresarNumDeLetra(segundo) - 1].getBack().numero - 1 == lli[regresarNumDeLetra(primero) - 1].getCartaPorIndice(numeroEnPila).numero)
                        {

                            if (verificarSimbolosContrarios(lli[regresarNumDeLetra(segundo) - 1].getBack().simbolo, lli[regresarNumDeLetra(primero) - 1].getCartaPorIndice(numeroEnPila).simbolo))
                            {
                                for (int i = numeroEnPila; i <= lli[regresarNumDeLetra(primero) - 1].getNumeroDeElementos(); i++)
                                {
                                    carta caAux = lli[regresarNumDeLetra(primero) - 1].getCartaPorIndice(i);
                                    lli[regresarNumDeLetra(segundo) - 1].addBack(caAux);
                                }
                                int tama = lli[regresarNumDeLetra(primero) - 1].getNumeroDeElementos();
                                for (int i = numeroEnPila; i <= tama; i++)
                                {
                                    lli[regresarNumDeLetra(primero) - 1].removeBack();
                                }
                                if (lli[regresarNumDeLetra(primero) - 1].getNumeroDeElementos() > 0)
                                {
                                    lli[regresarNumDeLetra(primero) - 1].descubirBack();
                                }
                            }
                            else
                            {
                                cout << "Movimiento Invalido(Mismo Color)\n";
                            }
                        }
                        else
                        {
                            cout << "Movimiento Invalido (";
                            dibujarNumero(lli[regresarNumDeLetra(segundo) - 1].getBack().numero - 1);
                            cout << " Esperado)\n";
                        }
                    }
                    else
                    {
                        if (lli[regresarNumDeLetra(primero) - 1].getCartaPorIndice(numeroEnPila).numero == 13)
                        {

                            for (int i = numeroEnPila; i <= lli[regresarNumDeLetra(primero) - 1].getNumeroDeElementos(); i++)
                            {
                                carta caAux = lli[regresarNumDeLetra(primero) - 1].getCartaPorIndice(i);
                                lli[regresarNumDeLetra(segundo) - 1].addBack(caAux);
                            }
                            int tama = lli[regresarNumDeLetra(primero) - 1].getNumeroDeElementos();
                            for (int i = numeroEnPila; i <= tama; i++)
                            {
                                lli[regresarNumDeLetra(primero) - 1].removeBack();
                            }

                            if (lli[regresarNumDeLetra(primero) - 1].getNumeroDeElementos() > 0)
                            {
                                lli[regresarNumDeLetra(primero) - 1].descubirBack();
                            }
                        }
                        else
                        {
                            cout << "Movimiento Invalido ('K' necesario) \n";
                        }
                    }
                }
                else
                {
                    cout << "Movimiento Invalido(Carta No Existente)";
                }
            }

            break;
        default:
            break;
        }
        break;
    }
}
bool verificarSimbolosContrarios(int sim1, int sim2)
{
    int suma = sim1 + sim2;
    if (suma == 3 || suma == 5 || suma == 7)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void subirCarta(LinkedList llf[], char columna, LinkedList &llARemover)
{
    carta car = llARemover.getBack();
    if (llf[regresarNumDeLetra(columna)].getNumeroDeElementos() + 1 == car.numero)
    {
        if (llf[regresarNumDeLetra(columna)].getNumeroDeElementos() > 0)
        {
            if (llf[regresarNumDeLetra(columna)].getBack().simbolo == llARemover.getBack().simbolo)
            {

                llf[regresarNumDeLetra(columna)].addBack(car);
                llARemover.removeBack();

                llARemover.descubirBack();
            }
            else
            {
                cout << "Movimiento Invalido (Simbolos no Concuerda)\n";
            }
        }
        else
        {

            llf[regresarNumDeLetra(columna)].addBack(car);
            llARemover.removeBack();

            llARemover.descubirBack();
        }
    }
    else
    {
        cout << "Movimiento Invalido\n";
    }
}
int regresarNumDeLetra(char letra)
{
    switch (letra)
    {
    case 'a':
    case 'c':
    case '0':
        return 0;
    case 'b':
    case 'd':
    case '1':
        return 1;
    case 'e':
    case '2':
        return 2;
    case 'f':
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    }
}
void generarCartasAlAzar(carta cartas1[])
{
    srand(time(NULL));
    for (int i = 1; i <= 4; i++)
    {

        for (int j = 1; j <= 13; j++)
        {
            bool asignado = true;
            while (asignado)
            {
                int num;
                
                num = rand() % 52;

                if (cartas1[num].numero == 0)
                {

                    cartas1[num].setAtributos(j, i, false);
                    asignado = false;
                }
            }
        }
    }
}


void dibujarTablero(LinkedList lli[], LinkedList lls[], LinkedList llf[])
{
    //Superior
    lls[0].getBack().numero;

    cout << "Li[a] Li[b]         Li[c] Li[d] Li[e] Li[f]" << endl;

    for (size_t i = 0; i < 2; i++)
    {
        cout << "[";
        if (lls[i].getBack().numero != 0)
        {
            if (lls[i].getBack().descubierto)
            {

                dibujarNumero(lls[i].getBack().numero);
                dibujarSimbolo(lls[i].getBack().simbolo);
            }
            else
            {
                cout << "???";
            }
        }
        else
        {
            cout << "   ";
        };
        cout << "] ";
    }
    //Final
    cout << "        ";
    for (int i = 0; i < 4; i++)
    {
        cout << "[";
        if (llf[i].getBack().numero != 0)
        {
            dibujarNumero(llf[i].getBack().numero);
            dibujarSimbolo(llf[i].getBack().simbolo);
        }
        else
        {
            cout << "   ";
        };
        cout << "] ";
    }
    cout << "\n";

    //Inferior

    int mayor = lli[0].getNumeroDeElementos();
    cout << "\n";

    for (int i = 1; i < 7; i++)
    {

        if (mayor < lli[i].getNumeroDeElementos())
        {
            mayor = lli[i].getNumeroDeElementos();
        }
    }
    for (int i = 1; i <= mayor; i++)
    {
        if (i == 1)
        {
            cout << "Li[1]  Li[2]  Li[3]  Li[4]  Li[5]  Li[6]  Li[7]\n";
        }

        for (int j = 0; j < 7; j++)
        {

            if (lli[j].getNumeroDeElementos() >= i)
            {
                cout << "[";
                carta carSig = lli[j].getCartaPorIndice(i);

                if (carSig.descubierto)
                {

                    dibujarNumero(carSig.numero);
                    dibujarSimbolo(carSig.simbolo);
                }
                else
                {
                    cout << "???";
                }
                cout << "]  ";
            }
            else
            {
                if (i == 1)
                {
                    cout << "[   ]  ";
                }
                else
                {
                    cout << "       ";
                }
            }
        }
        cout << "\n";
    }
}

void dibujarSimbolo(int numero)
{
    switch (numero)
    {
    case 1:
        cout << "♥";
        break;

    case 2:
        cout << "♣";
        break;
    case 3:
        cout << "♦";
        break;
    case 4:
        cout << "♠";
        break;
    default:
        break;
    }
}
int regresarNumeroDeSimbolo(char sim)
{
    switch (sim)
    {
    case 'A':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case '1':
        return 10;

    case 'J':
        return 11;

    case 'Q':
        return 12;

    case 'K':
        return 13;
    default:
        int au = (int)sim;
        return sim;
    }
}
void dibujarNumero(int numero1)
{
    switch (numero1)
    {
    case 1:
        cout << " A";
        break;

    case 10:
        cout << "10";
        break;
    case 11:
        cout << " J";
        break;
    case 12:
        cout << " Q";
        break;

    case 13:
        cout << " K";
        break;
    default:
        cout << " ";
        cout << numero1;

        break;
    }
}