#include "IteratorMDO.h"
#include "MDO.h"
IteratorMDO::IteratorMDO(const MDO& d) : dict(d) 
{
    // constructorul clasei iterator
    // 0(1)


    iteratorListaMare = dict.inceputListaMare;
    if (iteratorListaMare != nullptr)
        iteratorListaMica = iteratorListaMare->inceputListaMica;
}

void IteratorMDO::prim()
{
    // mutam iteratorul la primul element din container
    // 0(1)

    iteratorListaMare = dict.inceputListaMare; 
    if (iteratorListaMare != nullptr) 
        iteratorListaMica = iteratorListaMare->inceputListaMica; 
    else
        iteratorListaMica = nullptr;
}

void IteratorMDO::urmator() 
{
    // mutam iteratorul la urmatorul element
    // daca am ajuns la finalul unei liste mici, trecem la urmatorul nod in lista mare
    // O(1)

    if (iteratorListaMare != nullptr)
        if (iteratorListaMica->urmator != nullptr)
            iteratorListaMica = iteratorListaMica->urmator;
        else 
        {
            iteratorListaMare = iteratorListaMare->urmator;
            if (iteratorListaMare != nullptr) 
                iteratorListaMica = iteratorListaMare->inceputListaMica;
        }
}

bool IteratorMDO::valid() const 
{
    // verificam daca iteratorul este valid
    // 0(1)
    // valid() <- true, daca ambii iteratori sunt diferiti de pointerul nul
    //         <- false, in caz contrar

    return iteratorListaMare != nullptr && iteratorListaMica != nullptr;
}

TElem IteratorMDO::element() const 
{
    // returnam elementul curent
    // 0(1)
    // element() <- perechea <TCheie, TValoare>, daca iteratorul este valid
    //           <- perechea <-1, -1> in caz contrar

    if (valid()) 
        return pair<TCheie, TValoare>(iteratorListaMare->cheie, iteratorListaMica->valoare);
    return pair<TCheie, TValoare>(-1, -1);
}
