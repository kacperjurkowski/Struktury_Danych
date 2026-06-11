#ifndef CUCKOO_HASH_HPP
#define CUCKOO_HASH_HPP

#include <iostream>
#include <string>

class CuckooHash {
private:
    struct Entry {
        int key;
        std::string value;
        bool isOccupied;

        Entry() : key(0), value(""), isOccupied(false) {}
    };

    Entry* table1;      // Pierwsza alternatywna tablica
    Entry* table2;      // Druga alternatywna tablica
    int capacity;       // Rozmiar pojedynczej tablicy
    int size;           // Łączna liczba unikalnych elementów

    int hashSeed1;      // Losowy mnożnik dla pierwszej funkcji hashującej
    int hashSeed2;      // Losowy mnożnik dla drugiej funkcji hashującej

    int hash1(int key) const;
    int hash2(int key) const;

    void rehash();

public:
    CuckooHash();
    ~CuckooHash();

    // Zablokowanie kopiowania
    CuckooHash(const CuckooHash&) = delete;
    CuckooHash& operator=(const CuckooHash&) = delete;

    void insert(int key, const std::string& value);
    void remove(int key);
    bool find(int key, std::string& outValue) const;

    void display() const;
    int getSize() const { return size; }
    int getCapacity() const { return capacity * 2; } 
};

#endif