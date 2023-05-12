#include "SetIterator.h"
#include "Set.h"
#include <exception>

SetIterator::SetIterator(const Set& s) : set(s) {
    currentPos = -1;
    next();
}

TElem SetIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return set.table[currentPos].info;
}

void SetIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    currentPos++;
    while (currentPos < set.capacity && (set.table[currentPos].info == NULL_TELEM || set.table[currentPos].deleted)) {
        currentPos++;
    }
}

bool SetIterator::valid() const {
    return currentPos < set.capacity && set.table[currentPos].info != NULL_TELEM && !set.table[currentPos].deleted;
}

void SetIterator::first() {
    currentPos = -1;
    next();
}