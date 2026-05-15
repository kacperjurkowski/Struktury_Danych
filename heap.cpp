#include <iostream>
#include "heap.hpp"

Heap::~Heap() {
    //delete[] array;
}

void Heap::insert(int e, int p) {
    data.insert(e, p);
    heapify_up(data.getSize() - 1);
}

void Heap::extract_max() {
    
}

void Heap::peek() {
    
}

void Heap::decrease_key(int e, int p) {
    
}

void Heap::increase_key(int e, int p) {
    
}
void Heap::return_size() {
    
}