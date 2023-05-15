#include "SetIterator.h"
#include "Set.h"


SetIterator::SetIterator(const Set& m) : set(m)
{
    //TODO - Implementation
    if (set.size() == 0)
        this->currentPosition = -1;
    else
        first();
}


void SetIterator::first() {
    //TODO - Implementation
    this->currentPosition = 0;
    while (!valid())
        this->currentPosition++;
}


void SetIterator::next() {
    //TODO - Implementation
    if (valid()) {
        this->currentPosition++;
        while (!valid() && this->currentPosition < set.capacity)
            this->currentPosition++;
    }
    else
        throw exception();
}

TElem SetIterator::getCurrent()
{
    //TODO - Implementation
    if (valid())
        return set.hashTable[currentPosition];
    else
        throw exception();
}

bool SetIterator::valid() const {
    //TODO - Implementation
    return (this->currentPosition < set.capacity && set.hashTable[currentPosition] != NULL_TELEM && set.hashTable[currentPosition] != DELETED_TELEM&&this->currentPosition>=0);
}


