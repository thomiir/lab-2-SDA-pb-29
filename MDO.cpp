#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r)
{
    // constructorul clasei MDO
    // 0(1)

    relatie = r;
    inceputListaMare = nullptr;
    lg = 0;
}

void MDO::adauga(TCheie c, TValoare v) 
{
    // adaugam un element in container
    // caz favorabil (O(1)): cheia este pe prima pozitie in lista mare
    // caz defavorabil (O(n)): cheia nu exista in lista mare
    // caz mediu (O(n))

    NodListaMare* curentListaMare = inceputListaMare;
    NodListaMare* anteriorListaMare = nullptr;

    while (curentListaMare != nullptr && !relatie(c, curentListaMare->cheie)) 
    {
        anteriorListaMare = curentListaMare;
        curentListaMare = curentListaMare->urmator;
    }

    if (curentListaMare != nullptr && curentListaMare->cheie == c) 
    {
        NodListaMica* curentListaMica = curentListaMare->inceputListaMica;
        NodListaMica* anteriorListaMica = nullptr;
        NodListaMica* nodNou = new NodListaMica;
        nodNou->valoare = v;

        if (anteriorListaMica == nullptr) 
        {
            nodNou->urmator = curentListaMare->inceputListaMica;
            curentListaMare->inceputListaMica = nodNou;
        }
        else 
        {
            nodNou->urmator = curentListaMica;
            anteriorListaMica->urmator = nodNou;
        }
    }
    
    else 
    {
        NodListaMare* nodNouListaMare = new NodListaMare;
        nodNouListaMare->cheie = c;

        NodListaMica* nodNouListaMica = new NodListaMica;
        nodNouListaMica->valoare = v;

        nodNouListaMica->urmator = nullptr;
        nodNouListaMare->inceputListaMica = nodNouListaMica;

        if (anteriorListaMare == nullptr) 
        {
            nodNouListaMare->urmator = inceputListaMare;
            inceputListaMare = nodNouListaMare;
        }
        else 
        {
            nodNouListaMare->urmator = anteriorListaMare->urmator;
            anteriorListaMare->urmator = nodNouListaMare;
        }
    }
    lg++;
}


vector<TValoare> MDO::cauta(TCheie c) const 
{
    // cautam si returnam lista de elemente retinuta la o anumita cheie
    // caz favorabil (O(n)): elementul este pe prima pozitie in lista mare
    // caz defavorabil (O(dim+n)): elementul este pe ultima pozitie in lista mare
    // caz mediu (O(dim+n))
    // cauta (TCheie c) <- vectorul de elemente, daca cheia c exista in dictionar
    //                  <- vectorul vid, in caz contrar

    NodListaMare* curentListaMare = inceputListaMare;
    while (curentListaMare != nullptr) 
    {
        if (curentListaMare->cheie == c) 
        {
            NodListaMica* curentListaMica = curentListaMare->inceputListaMica;
            vector<TValoare> elemente;
            while (curentListaMica != nullptr) 
            {
                elemente.push_back(curentListaMica->valoare);
                curentListaMica = curentListaMica->urmator;
            }
            return elemente;
        }
        curentListaMare = curentListaMare->urmator;
    }
    return vector<TValoare>();
}

bool MDO::sterge(TCheie c, TValoare v) 
{
    // stergem perechea <TCheie, TValoare> din container
    // caz favorabil (O(1)): elementul este pe prima pozitie in lista mare, pe prima 
    //                       pozitie in lista mica
    // caz defavorabil (O(dim+n)): elementul este pe ultima pozitie in lista 
    //                             mare, pe ultima pozitie in lista mica
    // caz mediu (O(dim+n)) 
    // sterge (TCheie c, TValoare v) <- true, daca s-a sters un element din container
    //                               <- false, in caz contrar

    NodListaMare* curentListaMare = inceputListaMare;
    NodListaMare* anteriorListaMare = nullptr;

    while (curentListaMare != nullptr) 
    {
        if (curentListaMare->cheie == c) 
        {
            NodListaMica* curentListaMica = curentListaMare->inceputListaMica;
            NodListaMica* anteriorListaMica = nullptr;
            while (curentListaMica != nullptr) 
            {
                if (curentListaMica->valoare == v) 
                {
                    if (anteriorListaMica == nullptr)
                        curentListaMare->inceputListaMica = curentListaMica->urmator;
                    else
                        anteriorListaMica->urmator = curentListaMica->urmator;
                    delete curentListaMica;

                    if (curentListaMare->inceputListaMica == nullptr) 
                    {
                        if (anteriorListaMare == nullptr)
                            inceputListaMare = curentListaMare->urmator;
                        else
                            anteriorListaMare->urmator = curentListaMare->urmator;
                        delete curentListaMare;
                    }
                    lg--;
                    return true;
                }
                anteriorListaMica = curentListaMica;
                curentListaMica = curentListaMica->urmator;
            }
        }
        anteriorListaMare = curentListaMare;
        curentListaMare = curentListaMare->urmator;
    }
    return false;
}

int MDO::dim() const 
{
    // calculam si returnam dimensiunea containerului
    // 0(1)
    // dim() <- numarul de elemente din container

    return lg;
}

bool MDO::vid() const 
{
    // verificam daca containerul este vid
    // 0(1)
    // vid() <- true, daca inceputul listei mari este pointerul nul
    //       <- false, altfel

    return inceputListaMare == nullptr;
}

IteratorMDO MDO::iterator() const 
{
    // returnam un iterator pe container
    // 0(1)

    return IteratorMDO(*this);
}

MDO::~MDO() 
{
    // destructorul clasei MDO
    // eliberam spatiul alocat nodurilor din liste
    // 0(dim)

    NodListaMare* curentListaMare = inceputListaMare;
    while (curentListaMare != nullptr) 
    {
        NodListaMica* curentListaMica = curentListaMare->inceputListaMica;
        while (curentListaMica != nullptr) 
        {
            NodListaMica* auxListaMica = curentListaMica;
            curentListaMica = curentListaMica->urmator;
            delete auxListaMica;
        }
        NodListaMare* auxListaMare = curentListaMare;
        curentListaMare = curentListaMare->urmator;
        delete auxListaMare;
    }
}
