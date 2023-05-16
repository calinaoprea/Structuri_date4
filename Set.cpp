#include "Set.h"
#include "SetIterator.h"

//Best case: O(1) - constant time complexity
//Worst case: O(1) - constant time complexity
//Overall case: O(1) - constant time complexity
Set::Set() {
    //TODO - Implementation
    this->length = 0;
    this->all = 0;
    this->capacity = 17;
    this->hashTable = new TElem[17];
    for (int i = 0; i < 17; i++)
        this->hashTable[i] = NULL_TELEM;
    this->MAXloadFactor = 0.75;
}

//Best case: O(1) - constant time complexity
//Worst case: O(sqrt(x)) - square root of x time complexity (when x is a large prime number)
//Overall case: O(sqrt(x)) - square root of x time complexity
bool isPrime(int x) {
    if (x < 2 || x>2 && x % 2 == 0)
        return false;
    for (int d = 3; d * d <= x; d += 2)
        if (x % d == 0)
            return false;
    return true;
}

//Best case: O(1) - constant time complexity
//Worst case: O(x*sqrt(x)) - x times square root of x time complexity (when x is a large prime number)
//Overall case: O(x*sqrt(x)) - x times square root of x time complexity
int Set::getLargestPrime(int x) {
    x++;
    while (!isPrime(x))
        x++;
    return x;
}

//Best case: O(1) - constant time complexity
//Worst case: O(1) - constant time complexity
//Overall case: O(1) - constant time complexity
int Set::h1(TElem e) const {
    return abs(e) % this->capacity;
}

//Best case: O(1) - constant time complexity
//Worst case: O(1) - constant time complexity
//Overall case: O(1) - constant time complexity
int Set::h2(TElem e) const {
    return 1 + (abs(e) % (this->capacity - 1));
}

//Best case: O(capacity) - linear time complexity (when the hash table is already at maximum capacity)
//Worst case: O(capacity^2) - quadratic time complexity (when all elements in the hash table collide and need to be rehashed to the new capacity)
//Overall case: O(capacity^2) - quadratic time complexity
void Set::resize() {
    int prime = getLargestPrime(this->capacity*2);
    int old_capacity = this->capacity;
    this->capacity = prime;
    TElem* newTable = new TElem[prime];
    for (int index = 0; index < prime; index++)
        newTable[index] = NULL_TELEM;
    for (int index = 0; index < old_capacity; index++) {
        if (this->hashTable[index] != NULL_TELEM) {
            int hash1 = h1(this->hashTable[index]);
            int hash2 = h2(this->hashTable[index]);
            int count = 0;
            int position = (hash1 + count * hash2) % this->capacity;
            while (newTable[position] != NULL_TELEM) {
                count++;
                position = (hash1 + count * hash2) % this->capacity;
            }
            newTable[position] = this->hashTable[index];
        }
    }
    delete[] this->hashTable;
    this->hashTable = newTable;
}
// Theta(capacity)


//Best case: O(1) - constant time complexity (when the element is the first element in the hash table)
//Worst case: O(capacity) - linear time complexity (when the element is the last element in the hash table)
//Overall case: O(capacity) - linear time complexity
bool Set::add(TElem elem) {
    //TODO - Implementation
    //if the hash is full we resize
    double loadFacor = (double)this->all / this->capacity;
    if (loadFacor >= this->MAXloadFactor)
        resize();
    int hash1 = h1(elem);
    int hash2 = h2(elem);
    int count = 0;
    int position = (hash1+count*hash2)%this->capacity;
    //if the element is already in the hash we return false
    if (search(elem))
        return false;
    //otherwise we add the element
    while (this->hashTable[position] != NULL_TELEM) {
        count++;
        position = (hash1 + count * hash2) % this->capacity;
    }
    this->hashTable[position] = elem;
    this->length++;
    this->all++;
    return true;
}

//Best case: O(1) - constant time complexity (when the element is the first element in the hash table)
//Worst case: O(capacity) - linear time complexity (when the element is the last element in the hash table)
//Overall case: O(capacity) - linear time complexity
bool Set::remove(TElem elem) {
    //TODO - Implementation
    int hash1 = h1(elem);
    int hash2 = h2(elem);
    int count = 0;
    int position = (hash1 + count * hash2) % this->capacity;
    int initialPosition = -1111111;
    while (this->hashTable[position] != NULL_TELEM && count<this->capacity) {
        if (this->hashTable[position] == elem) {
            this->hashTable[position] = DELETED_TELEM;
            this->length--;
            return true;
        }
        if (initialPosition == -1111111)
            initialPosition = position;
        count++;
        position = (hash1 + count * hash2) % this->capacity;
    }
    return false;
}

//Best case: O(1) - constant time complexity (when the element is the first element in the hash table)
//Worst case: O(capacity) - linear time complexity (when the element is the last element in the hash table)
//Overall case: O(capacity) - linear time complexity
bool Set::search(TElem elem) const {
    //TODO - Implementation
    int hash1 = h1(elem);
    int hash2 = h2(elem);
    int count = 0;
    int position = (hash1 + count * hash2) % this->capacity;
    int initialPosition = -1111111;
    while (this->hashTable[position] != NULL_TELEM && count<this->capacity) {
        if (this->hashTable[position] == elem) {
            return true;
        }
        if (initialPosition == -1111111)
            initialPosition = position;
        count++;
        position = (hash1 + count * hash2) % this->capacity;
    }
    return false;
}

//Best case: O(1)
//Worst case: O(1)
//Overall case: O(1)
int Set::size() const {
    //TODO - Implementation
    return this->length;
}
// Theta(1)

//Best case: O(1)
//Worst case: O(1)
//Overall case: O(1)
bool Set::isEmpty() const {
    //TODO - Implementation
    return (this->length == 0);
}
// Theta(1)


Set::~Set() {
    //TODO - Implementation
    delete[] this->hashTable;
}


SetIterator Set::iterator() const {
    return SetIterator(*this);
}
// Theta(1)

