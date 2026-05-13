#ifndef PRIORITY_QUEUE_ARRAY_HPP
#define PRIORITY_QUEUE_ARRAY_HPP

#include "dynamic_array.hpp"

class PriorityQueueArray {
private:
    DynamicArray list;

public:
    PriorityQueueArray(); //Konstruktor
    ~PriorityQueueArray(); //Dekonstruktor

    void insert(int e, int p); //dodanie elementu do kolejki
    int extractMax(); //usunięcie elementu o najwyższym priorytecie
    int peek(); //podejrzenie maxa
    void modifyKey(int e, int p); //zmiana priorytetu
    int getSize() const { return list.getSize(); }

    void display(); //wyświetlenie
    void clear(); //wyczyszczenie
};

#endif