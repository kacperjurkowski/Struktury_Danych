#include <iostream>
#include "dynamic_array.hpp"

DynamicArray::DynamicArray() : array(nullptr), capacity(0), size(0) {}

DynamicArray::~DynamicArray() {
    delete[] array;
}

void DynamicArray::doubling() {
    //Jeśli tablica jest pusta, zaczynamy od capacity = 1, w przeciwnym razie podwajamy ją
    if(capacity == 0) {
        capacity = 1;
    } else {
        capacity *= 2;
    }

    //Alokacja nowej tablicy o pojemności capacity
    HeapNode* new_array = new HeapNode[capacity];

    //Pętla, która kopiuje elementy ze starej tablicy do nowej
    for(int i = 0; i < size; i++) {
        new_array[i] = array[i];
    }

    //Zwalnianie starej tablicy
    delete[] array;

    //Przypisanie kopii do starej tablicy
    array = new_array;
}

void DynamicArray::insert(int e, int p) {
    //Jeśli ilość elementów jest równy rozmiarowi tablicy, zwiększamy rozmiar tablicy
    if(size == capacity) {
        doubling();
    }
    
    array[size].value = e;
    array[size].priority = p;
    size++;
}

void DynamicArray::extract_max() {
    if(size == 0){
        return;
    }
    int maxIdx = 0;
    for(int i = 1; i < size; i++){
        if(array[i].priority > array[maxIdx].priority) {
            maxIdx = i;
        }
    }

    HeapNode temp = array[maxIdx];
    array[maxIdx] = array[size - 1];
    array[size - 1] = temp;
    size--;
}

void DynamicArray::peek() {
    if (size == 0){
        return;
    }

    //Wyświetla pierwszy element Kopca, bo zawsze będzie miał największy priorytet
    std::cout << "Element: " << array[0].value << "Priorytet: " << array[0].priority << std::endl;
}

int DynamicArray::return_size(){
    return size; //Zwraca rozmiar struktury
}

void DynamicArray::print(){
    if (size == 0){
        return;
    }

    for(int i  = 1; i < size; i++){
        std::cout << array[i].value << " " << array[i].priority << std::endl;
    }
}