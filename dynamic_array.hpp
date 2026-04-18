#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H 

class DynamicArray {
private:
    int* array; //wskaźnik na tablicę utworzoną dynamicznie
    int capacity; //rozmiar tablicy array
    int size; //liczba przechowywanych elementów

    void doubling();
public:
    DynamicArray(); //Konstruktor
    ~DynamicArray(); //Dekonstruktor

    void addFront(int value); //dodanie na początek
    void addEnd(int value); //dodanie na koniec
    void addAt(int index, int value); //dodanie losowo
    
    void removeFront(); //usunięcie z poczatku
    void removeEnd(); //usunięcie z końca
    void removeAt(int index); //usunięcie losowo

    bool find(int value); //zwrócenie elementu na pozycji i
    void print(); //wyświetlenie

    int getSize() const { return size; }
};

#endif