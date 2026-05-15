#ifndef HEAP_H
#define HEAP_H
#include "dynamic_array.hpp"

class Heap {

private:
    DynamicArray data;

public:
    Heap();     //Konstruktor
    ~Heap();    //Dekonstruktor

    void insert(int e, int p);          //Dodanie elementu e o priorytecie p
    void extractMax();                 //Usunięcie i zwrócenie elementu o największym priorytecie
    Element peek();                        //Zwrócenie elementu o największym priorytecie,
    void decrease_key(int e, int p);    //Zmniejszenie priorytetu elementu e na p
    void increase_key(int e, int p);    //Zwiększenie priorytetu elementu e na p
    int return_size() const { return data.getSize(); }              //Zwrócenie rozmiaru
    void display();                       //Wyświetlenie kopca

    void heapify_up(int index);                  //
    void heapify_down(int index);                //

};


#endif 