#ifndef HASHTABLEAVL_HPP
#define HASHTABLEAVL_HPP

#include "HashAVLTree.hpp"

class HashTableAVL {
private:
    HashAVLTree* buckets;           //Tablica wskaźników (kubełków)
    int capacity;                   //Pojemność  
    int size;                       //Rozmiar

    //Funkcja mieszająca, decyduje do którego kubełka trafi element
    int hashFunction(int key) const {
        unsigned int u_key = (key < 0) ? -static_cast<long long>(key) : key;
        return u_key % capacity;
    }

public:
    HashTableAVL(int initialCapacity);
    ~HashTableAVL();

    void insert(int key, int value);        //Wstawianie
    bool remove(int key);                   //Usuwanie
    int* find(int key) const;               //Szukanie
    void display() const;                   //Wyświetlanie
    int getSize() const { return size; }    //Zwracanie rozmiaru
};

#endif  