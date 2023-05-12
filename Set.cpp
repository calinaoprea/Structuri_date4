#include "Set.h"
#include "SetIterator.h"
#include <cmath>

Set::Set() {
    capacity = 4;
    _size = 0;
    prime = 3;
    table = new Node[capacity];
}

bool Set::add(TElem e) {
    if (_size * 2 >= capacity) {
        capacity *= 2;
        Node* newTable = new Node[capacity];
        for (int i = 0; i < capacity / 2; i++) {
            if (table[i].info != NULL_TELEM && !table[i].deleted) {
                int pos = findPos(table[i].info);
                newTable[pos].info = table[i].info;
            }
        }
        delete[] table;
        table = newTable;
    }

    int pos = findPos(e);
    if (table[pos].info != NULL_TELEM && !table[pos].deleted) {
        return false;
    }
    table[pos].info = e;
    table[pos].deleted = false;
    _size++; // increment the size
    return true;
}

bool Set::remove(TElem e) {
    int pos = findPos(e);
    if (table[pos].info == NULL_TELEM || table[pos].deleted) {
        return false;
    }
    table[pos].deleted = true;
    _size--; // decrement the size
    return true;
}

bool Set::search(TElem elem) const {
    int pos = findPos(elem);
    return (table[pos].info != NULL_TELEM && !table[pos].deleted);
}

int Set::size() const {
    return _size;
}

bool Set::isEmpty() const {
    return _size == 0;
}

Set::~Set() {
    delete[] table;
}

SetIterator Set::iterator() const {
    return SetIterator(*this);
}

int Set::hash1(TElem e) const {
    return abs(e % capacity);
}

int Set::hash2(TElem e) const {
    return abs(prime - e % prime);
}

int Set::findPos(TElem e) const {
    int pos = hash1(e);
    int i = 0;
    while (table[pos].info != e && table[pos].info != NULL_TELEM && i < capacity) {
        pos = (pos + i * hash2(e)) % capacity;
        i++;
    }
    return pos;
}