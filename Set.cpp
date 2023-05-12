#include "Set.h"
#include "SetIterator.h"
#include <cmath>

Set::Set() {
    capacity = 4;
    _size = 0;
    prime = 3;
    table = new Node[capacity]();
}

bool Set::add(TElem e) {
    if (_size * 2 >= capacity) {
        int oldCapacity = capacity;
        capacity *= 2;
        Node* newTable = new Node[capacity]();
        for (int i = 0; i < oldCapacity; i++) {
            if (table[i].info != NULL_TELEM && !table[i].deleted) {
                int pos = findPos(table[i].info, newTable, capacity);
                newTable[pos].info = table[i].info;
            }
        }
        delete[] table;
        table = newTable;
    }

    int pos = findPos(e, table, capacity);
    if (table[pos].info == e && !table[pos].deleted) {
        return false;
    }
    if (table[pos].info != NULL_TELEM && table[pos].deleted) {
        _size--;
    }
    table[pos].info = e;
    table[pos].deleted = false;
    _size++;
    return true;
}


int Set::findPos(TElem e, const Node* table, int capacity) const {
    int i = 0;
    int pos = hash1(e) % capacity;
    int offset = hash2(e) % (capacity - 1) + 1; // ensure offset is non-zero and less than capacity
    while (i < capacity && table[pos].info != NULL_TELEM && table[pos].info != e) {
        i++;
        pos = (pos + offset) % capacity;
    }
    return pos;
}

bool Set::remove(TElem e) {
    int pos = findPos(e, table, capacity);
    if (table[pos].info == NULL_TELEM || table[pos].deleted) {
        return false;
    }
    table[pos].deleted = true;
    _size--; // decrement the size

    // Check if the table needs to be rehashed
    if (_size < capacity / 4) {
        rehash();
    }

    // Find and mark any other occurrences of the element in the table
    int i = 1;
    int prev_pos = pos;
    pos = (pos + i * hash2(e)) % capacity;
    while (i < capacity && table[pos].info != NULL_TELEM) {
        if (table[pos].info == e && !table[pos].deleted) {
            table[pos].deleted = true;
            _size--;
        }
        i++;
        pos = (pos + i * hash2(e)) % capacity;
    }

    return true;
}

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

void Set::rehash() {
    int new_capacity = 2 * capacity + 1;
    while (!isPrime(new_capacity)) {
        new_capacity += 2;
    }
    Node* new_table = new Node[new_capacity]; // allocate new table
    for (int i = 0; i < new_capacity; i++) {
        new_table[i].info = NULL_TELEM; // set all elements to null
        new_table[i].deleted = false;
    }
    for (int i = 0; i < capacity; i++) { // rehash old elements
        if (table[i].info != NULL_TELEM && !table[i].deleted) {
            int pos = findPos(table[i].info, new_table, new_capacity);
            new_table[pos].info = table[i].info;
            new_table[pos].deleted = false;
        }
    }
    capacity = new_capacity;
    delete[] table; // deallocate old table
    table = new_table; // update pointer
}

bool Set::search(TElem elem) const {
    int pos = findPos(elem, table, capacity);
    return (table[pos].info != NULL_TELEM && !table[pos].deleted && table[pos].info == elem);
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
