#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) : relatie(r), inceputListaMare(nullptr) {};

void MDO::adauga(TCheie c, TValoare v) {
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

        /// aici trebuie modificat, nu este neaparat sa se adauge valoarea la
        /// sfarsitul listei
        /// doar cheile sunt ordonate in functie de relatia R
        while (curentListaMica != nullptr && curentListaMica->valoare < v) {
            anteriorListaMica = curentListaMica;
            curentListaMica = curentListaMica->urmator;
        }

        NodListaMica* nouNod = new NodListaMica;
        nouNod->valoare = v;

        if (anteriorListaMica == nullptr) {
            nouNod->urmator = curentListaMare->inceputListaMica;
            curentListaMare->inceputListaMica = nouNod;
        }
        else {
            nouNod->urmator = curentListaMica;
            anteriorListaMica->urmator = nouNod;
        }
    }
    else {
        NodListaMare* nouNodMare = new NodListaMare;
        nouNodMare->cheie = c;

        NodListaMica* nouNodMica = new NodListaMica;
        nouNodMica->valoare = v;

        nouNodMica->urmator = nullptr;
        nouNodMare->inceputListaMica = nouNodMica;

        if (anteriorListaMare == nullptr) 
        {
            nouNodMare->urmator = inceputListaMare;
            inceputListaMare = nouNodMare;
        }
        else 
        {
            nouNodMare->urmator = anteriorListaMare->urmator;
            anteriorListaMare->urmator = nouNodMare;
        }
    }
}


vector<TValoare> MDO::cauta(TCheie c) const {
    NodListaMare* curentListaMare = inceputListaMare;
    while (curentListaMare != nullptr) {
        if (curentListaMare->cheie == c) {
            NodListaMica* curentListaMica = curentListaMare->inceputListaMica;
            vector<TValoare> elemente;
            while (curentListaMica != nullptr) {
                elemente.push_back(curentListaMica->valoare);
                curentListaMica = curentListaMica->urmator;
            }
            return elemente;
        }
        curentListaMare = curentListaMare->urmator;
    }
    return vector<TValoare>();
}

bool MDO::sterge(TCheie c, TValoare v) {
    NodListaMare* curentListaMare = inceputListaMare;
    NodListaMare* anteriorListaMare = nullptr;

    while (curentListaMare != nullptr) {
        if (curentListaMare->cheie == c) {
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

int MDO::dim() const {
    NodListaMare* curentListaMare = inceputListaMare;
    int lg = 0;
    while (curentListaMare != nullptr) 
    {
        NodListaMica* curentListaMica = curentListaMare->inceputListaMica;
        while (curentListaMica != nullptr) 
        {
            curentListaMica = curentListaMica->urmator;
            lg++;
        }
        curentListaMare = curentListaMare->urmator;
    }
    return lg;
}

bool MDO::vid() const 
{
    return inceputListaMare == nullptr;
}

IteratorMDO MDO::iterator() const 
{
    return IteratorMDO(*this);
}

MDO::~MDO() 
{
    NodListaMare* curentListaMare = inceputListaMare;
    while (curentListaMare != nullptr) {
        NodListaMare* auxListaMare = curentListaMare;
        NodListaMica* curentListaMica = curentListaMare->inceputListaMica;
        while (curentListaMica != nullptr) {
            NodListaMica* auxListaMica = curentListaMica;
            curentListaMica = curentListaMica->urmator;
            delete auxListaMica;
        }
        curentListaMare = curentListaMare->urmator;
        delete auxListaMare;
    }
}
