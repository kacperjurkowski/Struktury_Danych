#include <iostream>
#include "heap.hpp"

Heap::Heap() {}

Heap::~Heap() {}

void Heap::insert(int e, int p) {
    Element el = {p, e};
    data.addEnd(el);                    // Dodajemy na koniec tablicy dynamicznej
    heapify_up(data.getSize() - 1);     // Naprawa w górę
}

void Heap::heapify_up(int index){
    while (index > 0) {
        int parentIdx = (index - 1) / 2;
        if (data.get(index).priority > data.get(parentIdx).priority) {
            std::swap(data.get(index), data.get(parentIdx));
            index = parentIdx;
        } else break;
    }
}

void Heap::heapify_down(int index){
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int n = data.getSize();

    if (left < n && data.get(left).priority > data.get(largest).priority)
        largest = left;

    if (right < n && data.get(right).priority > data.get(largest).priority)
        largest = right;

    if (largest != index) {
        std::swap(data.get(index), data.get(largest));
        heapify_down(largest);
    }
}

void Heap::extractMax() {
    if (data.getSize() == 0) {
        return;
    }

    // Zamiana korzenia z ostatnim elementem
    std::swap(data.get(0), data.get(data.getSize() - 1));
    data.removeEnd(); // Usunięcie starego maxa
    
    if (data.getSize() > 0) {
        heapify_down(0); // Naprawa od góry w dół
    }   
}

int Heap::peek() {
    if (data.getSize() > 0) {
        return data.get(0).value;
    }
    return -1;
}

void Heap::decrease_key(int e, int p) {
    for (int i = 0; i < data.getSize(); i++) {
        if (data.get(i).value == e) {
            data.get(i).priority = p;
            heapify_down(i); // Po zmniejszeniu element może "opadać" w dół
            return;
        }
    }
}

void Heap::increase_key(int e, int p) {
    for (int i = 0; i < data.getSize(); i++) {
        if (data.get(i).value == e) {
            data.get(i).priority = p;
            heapify_up(i); // Po zwiększeniu element może "płynąć" w górę
            return;
        }
    }
}

void Heap::display() {
    for (int i = 0; i < data.getSize(); ++i) {
        std::cout << "[" << data.get(i).priority << ":" << data.get(i).value << "] ";
    }
    std::cout << std::endl;
}