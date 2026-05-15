#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H 

struct HeapNode {
        int priority;   //Klucz p
        int value;      //Element e
    };

class DynamicArray {
private:
    HeapNode* array; //wskaźnik na tablicę utworzoną dynamicznie
    int capacity; //rozmiar tablicy array
    int size; //liczba przechowywanych elementów

    void doubling();
public:
    DynamicArray(); //Konstruktor
    ~DynamicArray(); //Dekonstruktor

    void insert(int e, int p);          //Dodanie elementu e o priorytecie p
    void extract_max();                 //Usunięcie i zwrócenie elementu o największym priorytecie
    void peek();                        //Zwrócenie elementu o największym priorytecie,
    void decrease_key(int e, int p);    //Zmniejszenie priorytetu elementu e na p
    void increase_key(int e, int p);    //Zwiększenie priorytetu elementu e na p
    int return_size();                 //Zwrócenie rozmiaru
    void print();                       //Wyświetlenie kopca

    int getSize() const { return size; }
};

#endif