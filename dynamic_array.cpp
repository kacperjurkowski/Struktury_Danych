#include <iostream>
#include "dynamic_array.hpp"

DynamicArray::DynamicArray(int initial_capacity) {
    capacity = initial_capacity;
    size = 0;
    array = new int[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] array;
}

void DynamicArray::doubling() {
    capacity *= 2;
    int* new_array = new int[capacity];

    for(int i = 0; i < size; i++) {
        new_array[i] = array[i];
    }

    delete[] array;
    array = new_array;
}

void DynamicArray::addFront(int value) {
    if(size == capacity) doubling();
    
    for(int i = size; i > 0; i--) {
        array[i] = array[i - 1];
    }
    
    array[0] = value;
    size++;
}

void DynamicArray::addEnd(int value) {
    if(size == capacity) doubling();
    array[size++] = value;
}

void DynamicArray::addAt(int index, int value) {
    if (size == capacity) doubling();

    for(int i = size; i > index; i--){
        array[i] = array[i - 1];
    }
    array[index] = value;
    size++;
}

void DynamicArray::removeFront(){
    if(size == 0) return;

    for(int i = 0; i < size - 1; i++){
        array[i] = array[i+1];
    }
    size--;
}

void DynamicArray::removeEnd() {
    if(size > 0){
        size--;
    }
}

void DynamicArray::removeAt(int index) {
    if (index < 0 || index >= size) return;

    for(int i = index; i < size - 1; i++){
        array[i] = array[i + 1];
    }
    size--;
}

int DynamicArray::search(int value){
    for(int i = 0; i < size; i++){
        if(array[i] == value) return i;
    }

    return -1;
}