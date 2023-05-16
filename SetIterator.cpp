#include "SetIterator.h"
#include "Set.h"

//Best case: O(1)
//Worst case: O(n)
//Overall case: O(n)
SetIterator::SetIterator(const Set& m) : set(m)
{
    //TODO - Implementation
    if (set.size() == 0)
        this->currentPosition = -1;
    else
        first();
}

//Best case: O(1)
//Worst case: O(n)
//Overall case: O(n)
void SetIterator::first() {
    //TODO - Implementation
    this->currentPosition = 0;
    while (!valid())
        this->currentPosition++;
}

//Best case: O(1)
//Worst case: O(n)
//Overall case: O(n)
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

//Best case: O(1)
//Worst case: O(1)
//Overall case: O(1)
TElem SetIterator::getCurrent()
{
    //TODO - Implementation
    if (valid())
        return set.hashTable[currentPosition];
    else
        throw exception();
}

//Best case: O(1)
//Worst case: O(1)
//Overall case: O(1)
bool SetIterator::valid() const {
    //TODO - Implementation
    return (this->currentPosition < set.capacity && set.hashTable[currentPosition] != NULL_TELEM && set.hashTable[currentPosition] != DELETED_TELEM&&this->currentPosition>=0);
}
