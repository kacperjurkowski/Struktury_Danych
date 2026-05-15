#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H 

// Struktura elementu kolejki
struct Element {
    int priority; 
    int value;    
};

class DynamicArray {
private:
    Element* array;                 //Wskaźnik na tablicę utworzoną dynamicznie
    int capacity;                   //Rozmiar tablicy array
    int size;                       //Liczba przechowywanych elementów

    void doubling();
public:
    DynamicArray();                 //Konstruktor
    ~DynamicArray();                //Dekonstruktor

    void addEnd(Element value);     //Dodanie na koniec
    void removeEnd();               //Usunięcie z końca
    void removeAt(int index);       //Usunięcie losowo

    // Metody pomocnicze dla kolejki
    Element& get(int index) { return array[index]; }
    int getSize() const { return size; }
    void clear();
};

#endif