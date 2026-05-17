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
    Element* new_array = new Element[capacity];

    //Pętla, która kopiuje elementy ze starej tablicy do nowej
    for(int i = 0; i < size; i++) {
        new_array[i] = array[i];
    }

    //Zwalnianie starej tablicy
    delete[] array;

    //Przypisanie kopii do starej tablicy
    array = new_array;
}

void DynamicArray::addEnd(Element value) {
    //Jeśli ilość elementów jest równy rozmiarowi tablicy, zwiększamy rozmiar tablicy
    if(size == capacity) {
        doubling();
    }
    //Dodanie elementu do tablicy na końcu
    array[size++] = value;
}

void DynamicArray::removeEnd() {
    //Sprawdzenie, czy tablica jest pusta
    if(size > 0){
        //Zmniejszenie ilości elementów o 1
        size--;
    }
}

void DynamicArray::removeAt(int index) {
    //Sprawdzenie, czy index znajduej się w przedziale
    if (index < 0 || index >= size) {
        return;
    }
    
    //Pętla przesuwająca elementy w lewo, nadpisująca usunięty rekord
    for(int i = index; i < size - 1; i++){
        array[i] = array[i + 1];
    }
    size--;
}

void DynamicArray::clear() {
    delete[] array;             //Zwolnienie pamięci na tablicę
    array = nullptr;            //Wyzerowanie wskaźnika
    size = 0;                   //Reset liczby elementów
    capacity = 0;               //Reset pojemności fizycznej
}