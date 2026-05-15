#include "PriorityQueueArray.hpp"
#include <iostream>

PriorityQueueArray::PriorityQueueArray() {}

PriorityQueueArray::~PriorityQueueArray() {}

void PriorityQueueArray::insert(int e, int p) {
    //Tworzenie elementu i dodanie go na koniec tablicy
    Element el = {p, e};
    list.addEnd(el);
}

int PriorityQueueArray::extractMax() {
    //Sprawdzenie, czy tablica nie jest pusta
    if (list.getSize() == 0) {
        return -1;
    }

    int maxIdx = 0;
    //Pętla szukająca największego priorytetu
    for (int i = 1; i < list.getSize(); ++i) {
        if (list.get(i).priority > list.get(maxIdx).priority) {
            maxIdx = i;
        }
    }

    int result = list.get(maxIdx).value;
    //Usunięcie elementu z tablicy na wybranym miejscu
    list.removeAt(maxIdx);
    return result;
}

int PriorityQueueArray::peek() {
    if (list.getSize() == 0) {
        return -1;
    }
    
    int maxIdx = 0;
    //Pętla szukająca elementu o najwyższym priorytecie
    for (int i = 1; i < list.getSize(); ++i) {
        if (list.get(i).priority > list.get(maxIdx).priority) {
            maxIdx = i;
        }
    }
    return list.get(maxIdx).value;
}

void PriorityQueueArray::increase_key(int e, int p) { modifyKey(e, p); }
void PriorityQueueArray::decrease_key(int e, int p) { modifyKey(e, p); }

void PriorityQueueArray::modifyKey(int e, int p) {
    //Pętla szukająca elementu o podanej wartości
    for (int i = 0; i < list.getSize(); ++i) {
        if (list.get(i).value == e) {
            //Przypisanie nowego priorytetu
            list.get(i).priority = p;
            return;
        }
    }
}

void PriorityQueueArray::display() {
    //Pętla wypisująca elementy tablicy
    for (int i = 0; i < list.getSize(); ++i) {
        std::cout << "[" << list.get(i).priority << ":" << list.get(i).value << "] ";
    }
    std::cout << std::endl;
}

void PriorityQueueArray::clear() {
    //Wywołanie czyszczenia tablicy
    list.clear();
}