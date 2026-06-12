#include "HashTableAVL.hpp"
#include <iostream>

HashTableAVL::HashTableAVL(int initialCapacity) {
    capacity = (initialCapacity <= 0) ? 8 : initialCapacity;
    buckets = new HashAVLTree[capacity];
    size = 0;
}

HashTableAVL::~HashTableAVL() {
    delete[] buckets; 
}

//Metoda wstawiania elementu
void HashTableAVL::insert(int key, int value) {
    int index = hashFunction(key);                  //Numer kubełka
    int oldSize = buckets[index].getSize();         //Ilość elementów w drzewie
    
    buckets[index].insert(key, value);              //Wstawienie elementu do drzewa AVL
    
    int newSize = buckets[index].getSize();         //Pobranie rozmiaru drzewa i weryfikacja
    if (newSize > oldSize) {
        size++; 
    }
}

bool HashTableAVL::remove(int key) {
    int index = hashFunction(key);                  //Numer kubełka
    if (buckets[index].remove(key)) {               //Usuwanie w drzewie AVL i sprawdzenie wyniku operacji : zmniejszenie rozmiaru
        size--;
        return true;
    }
    return false;
}

//Metoda szukająca klucza w drzewie AVL
int* HashTableAVL::find(int key) const {
    int index = hashFunction(key);                  //Numer kubełka
    return buckets[index].find(key);                //Zwrócenie wyniku 
}

//Metoda wyświetlająca tablicę mieszającą
void HashTableAVL::display() const {
    for (int i = 0; i < capacity; i++) {
        std::cout << "Kubelek [" << i << "]: ";
        buckets[i].display();
        std::cout << "\n";
    }
}