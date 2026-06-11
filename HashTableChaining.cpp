#include "HashTableChaining.hpp"
#include <iostream>

HashTableChaining::HashTableChaining(int initialCapacity) {
    capacity = (initialCapacity <= 0) ? 16 : initialCapacity;
    buckets = new HashLinkedList[capacity];
    size = 0;
}

HashTableChaining::~HashTableChaining() {
    delete[] buckets; // Wywołuje destruktory obiektów HashLinkedList
}

void HashTableChaining::insert(int key, int value) {
    int index = hashFunction(key);
    int oldSize = buckets[index].getSize();
    
    // Delegacja wstawiania do konkretnej listy
    buckets[index].insert(key, value);
    
    // Inkrementacja licznika globalnego tylko, gdy dodano nowy klucz
    int newSize = buckets[index].getSize();
    if (newSize > oldSize) {
        size++; 
    }
}

bool HashTableChaining::remove(int key) {
    int index = hashFunction(key);
    if (buckets[index].remove(key)) {
        size--;
        return true;
    }
    return false;
}

int* HashTableChaining::find(int key) {
    int index = hashFunction(key);
    return buckets[index].find(key); // Zwraca wskaźnik na wartość lub nullptr
}

void HashTableChaining::display() const {
    for (int i = 0; i < capacity; i++) {
        std::cout << "Kubelek [" << i << "]: ";
        buckets[i].display();
        std::cout << "\n";
    }
}