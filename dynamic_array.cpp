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

void DynamicArray::addFront(Element value) {
    //Jeśli ilość elementów jest równy rozmiarowi tablicy, zwiększamy rozmiar tablicy
    if(size == capacity) {
        doubling();
    }
    
    //Przesunięcie wszystkich elementów w prawo zaczynając od końca
    for(int i = size; i > 0; i--) {
        array[i] = array[i - 1];
    }
    
    //Dodanie nowego elementu na początek
    array[0] = value;
    //Zwiększenie ilości elementów o 1
    size++;
}

void DynamicArray::addEnd(Element value) {
    //Jeśli ilość elementów jest równy rozmiarowi tablicy, zwiększamy rozmiar tablicy
    if(size == capacity) {
        doubling();
    }
    //Dodanie elementu do tablicy na końcu
    array[size++] = value;
}

void DynamicArray::addAt(int index, Element value) {
    //Jeśli ilość elementów jest równy rozmiarowi tablicy, zwiększamy rozmiar tablicy
    if (size == capacity) {
        doubling();
    }
    //Przesunięcie wszystkich elementów w prawo zaczynając od końca, aż po miejsce, w które zostało losowo wybrane
    for(int i = size; i > index; i--){
        array[i] = array[i - 1];
    }
    //Dodanie elementu do tablicy na losowo wygenerowanym miejscu
    array[index] = value;
    //Zwiększenie ilości elementów o 1
    size++;
}

void DynamicArray::removeFront(){
    //Sprawdzenie, czy tablica jest pusta
    if(size > 0) {
        //Pętla przechodząca przez elementy tablicy, aż po ilość elementów - 1
        for(int i = 0; i < size - 1; i++){
            //Nadpisanie poprzednich elementów następnymi
            array[i] = array[i+1];
        }
        //Zmniejszenie ilości elementów o 1
        size--;
    }
}

void DynamicArray::removeEnd() {
    //Sprawdzenie, czy tablica jest pusta
    if(size > 0){
        //Zmniejszenie ilości elementów o 1
        size--;
    }
}

// ============DODAĆ KOMENTARZ================
void DynamicArray::removeAt(int index) {
    
    if (index < 0 || index >= size) {
        return;
    }

    for(int i = index; i < size - 1; i++){
        array[i] = array[i + 1];
    }
    size--;
}

bool DynamicArray::find(int value){
    //Pętla, przechodząca przez wszystkie elementy tablicy
    for(int i = 0; i < size; i++){
        //Warunek zwracający prawdę, jeżeli znajdzie element w tablicy
        if(array[i].value == value) { // Sprawdzamy pole value w strukturze Element
            return true;
        }
    }
    return false;
}

void DynamicArray::clear() {
    delete[] array;
    array = nullptr;
    size = 0;
    capacity = 0;
}