#include <iostream>
#include "heap.hpp"

Heap::Heap() {}

Heap::~Heap() {}

void Heap::insert(int e, int p) {
    Element el = {p, e};                //Element priorytet z wartością
    data.addEnd(el);                    // Dodajemy na koniec tablicy dynamicznej
    heapify_up(data.getSize() - 1);     // Naprawa w górę
}

void Heap::heapify_up(int index){
    while (index > 0) {
        int parentIdx = (index - 1) / 2; //Znalezienie indeksu rodzica

        if (data.get(index).priority > data.get(parentIdx).priority) { //Element ma większy priorytet niż rodzic -> zamiana miejscami
            std::swap(data.get(index), data.get(parentIdx));
            index = parentIdx;  //Idziemy na pozycję rodzica i sprawdzamy w górę
        } else {
            break; //Jeżeli rodzic większy to przerywamy
        }
    }
}

void Heap::heapify_down(int index){
    int largest = index;            //Zakładamy na starcie, że rodzic pod danym indeksem jest największy
    int left = 2 * index + 1;       //Lewy syn
    int right = 2 * index + 2;      //Prawy syn
    int n = data.getSize();         //Aktualny rozmiar kopca

    //Jeśli lewy syn istnieje i ma większy priorytet to zapamiętujemy go jako największy
    if (left < n && data.get(left).priority > data.get(largest).priority)
        largest = left;

    //Jeśli prawy syn istnieje i ma większy priorytet to zapamiętujemy go jako największy
    if (right < n && data.get(right).priority > data.get(largest).priority)
        largest = right;

    //Jeśli największym elementem nie okazał się rodzic, tylko któryś z synów, robimy podmiankę
    if (largest != index) {
        std::swap(data.get(index), data.get(largest)); //Zamiana miejscami
        heapify_down(largest);                         //Idziemy rekurencyjnie niżej, żeby sprawdzić i naprawić resztę drzewa
    }
}

void Heap::extractMax() {
    if (data.getSize() == 0) {
        return;
    }

    // Zamiana korzenia z ostatnim elementem
    std::swap(data.get(0), data.get(data.getSize() - 1));
    data.removeEnd(); // Usunięcie starego maxa
    
    //Jeśli w kopcu zostały jeszcze jakieś elementy, musimy naprawić strukturę
    if (data.getSize() > 0) {
        heapify_down(0); // Naprawa od góry w dół
    }   
}

Element Heap::peek() {
    if (data.getSize() > 0) {
        return data.get(0); //Element maksymalny w kopcu zawsze leży pod indeksem 0
    }
    return {-1, -1}; //Jeśli kopiec jest pusty, zwracamy błąd
}

void Heap::decrease_key(int e, int p) {
    //Przeszukujemy pętlą cały kopiec, żeby znaleźć element o szukanej wartości
    for (int i = 0; i < data.getSize(); i++) {  
        if (data.get(i).value == e) {
            data.get(i).priority = p;   //Nadpisujemy jego stary priorytet nowym, mniejszym
            heapify_down(i); // Po zmniejszeniu element może "opadać" w dół
            return;
        }
    }
}

void Heap::increase_key(int e, int p) {
        //Przeszukujemy pętlą cały kopiec, żeby znaleźć element o szukanej wartości
    for (int i = 0; i < data.getSize(); i++) {
        if (data.get(i).value == e) {
            data.get(i).priority = p;   //Nadpisujemy jego stary priorytet nowym, większym
            heapify_up(i); // Po zwiększeniu element może "płynąć" w górę
            return;
        }
    }
}

void Heap::display() {
    //Pętla przechodząca przez wszystkie elementy i wyświetlająca je
    for (int i = 0; i < data.getSize(); ++i) {
        std::cout << "[" << data.get(i).priority << ":" << data.get(i).value << "] ";
    }
    std::cout << std::endl;
}