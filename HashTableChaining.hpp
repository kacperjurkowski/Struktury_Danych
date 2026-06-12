#ifndef HASHTABLECHAINING_HPP
#define HASHTABLECHAINING_HPP

#include "HashLinkedList.hpp"

class HashTableChaining {
private:
    HashLinkedList* buckets; 
    int capacity;            
    int size;                

    int hashFunction(int key) const {
        unsigned int u_key = (key < 0) ? -static_cast<long long>(key) : key;
        return u_key % capacity;
    }

public:
    HashTableChaining(int initialCapacity);
    ~HashTableChaining();

    void insert(int key, int value);
    bool remove(int key);
    int* find(int key);
    void display() const;
    int getSize() const { return size; }
};

#endif