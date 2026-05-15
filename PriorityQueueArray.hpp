#ifndef PRIORITY_QUEUE_ARRAY_HPP
#define PRIORITY_QUEUE_ARRAY_HPP

#include "dynamic_array.hpp"

class PriorityQueueArray {
private:
    DynamicArray list;

public:
    PriorityQueueArray();                           //Konstruktor
    ~PriorityQueueArray();                          //Dekonstruktor

    void insert(int e, int p);                      //Dodanie elementu do kolejki
    int extractMax();                               //Usunięcie elementu o najwyższym priorytecie
    Element peek();                                     //Podejrzenie maxa

    void increase_key(int e, int p);
    void decrease_key(int e, int p);
    void modifyKey(int e, int p);                   //Zmiana priorytetu
    int return_size() const { return list.getSize(); }

    void display();                                 //wyświetlenie
    void clear();                                   //wyczyszczenie
};

#endif