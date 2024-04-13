#include "IteratorMDO.h"
#include "MDO.h"
IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
    // Initialize the iterator to point to the beginning of the MDO
    iteratorListaMare = dict.inceputListaMare;
    if (iteratorListaMare != nullptr) {
        // If the MDO is not empty, initialize the iterator for the first key
        iteratorListaMica = iteratorListaMare->inceputListaMica;
    }
}

void IteratorMDO::prim() {
    // Move the iterator to the first key-value pair
    iteratorListaMare = dict.inceputListaMare;
    if (iteratorListaMare != nullptr) {
        iteratorListaMica = iteratorListaMare->inceputListaMica;
    }
}

void IteratorMDO::urmator() {
    if (iteratorListaMare != nullptr) {
        if (iteratorListaMica != nullptr && iteratorListaMica->urmator != nullptr) {
            // Move to the next element in the current list associated with the key
            iteratorListaMica = iteratorListaMica->urmator;
        }
        else {
            // If there are no more elements in the current list, move to the next key
            iteratorListaMare = iteratorListaMare->urmator;
            if (iteratorListaMare != nullptr) {
                iteratorListaMica = iteratorListaMare->inceputListaMica;
            }
        }
    }
}

bool IteratorMDO::valid() const {
    // Check if the iterator is currently pointing to a valid key-value pair
    return iteratorListaMare != nullptr && iteratorListaMica != nullptr;
}

TElem IteratorMDO::element() const {
    // Return the key-value pair pointed to by the iterator
    if (valid()) 
        return pair<TCheie, TValoare>(iteratorListaMare->cheie, iteratorListaMica->valoare);

    // Return a default pair if the iterator is not valid
    return pair<TCheie, TValoare>(-1, -1);
}
