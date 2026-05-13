#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H 

// Struktura elementu kolejki
struct Element {
    int priority; 
    int value;    
};

class DynamicArray {
private:
    Element* array; //wskaźnik na tablicę utworzoną dynamicznie
    int capacity; //rozmiar tablicy array
    int size; //liczba przechowywanych elementów

    void doubling();
public:
    DynamicArray(); //Konstruktor
    ~DynamicArray(); //Dekonstruktor

    void addFront(Element value); //dodanie na początek
    void addEnd(Element value); //dodanie na koniec
    void addAt(int index, Element value); //dodanie losowo
    
    void removeFront(); //usunięcie z poczatku
    void removeEnd(); //usunięcie z końca
    void removeAt(int index); //usunięcie losowo

    bool find(int value); //zwrócenie elementu na pozycji i
    
    // Metody pomocnicze dla kolejki
    Element& get(int index) { return array[index]; }
    int getSize() const { return size; }
    void clear();
};

#endif