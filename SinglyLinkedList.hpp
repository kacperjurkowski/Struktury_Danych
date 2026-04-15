#ifndef SINGLYLINKEDLIST_HPP
#define SINGLYLINKEDLIST_HPP

#include <iostream>

// pojedynczy element listy
struct Node {
    int data;       // 4 bajtowa liczba
    Node* next;     // Wskaźnik na kolejny element

    Node(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;     // Wskaźnik na początek listy 
    Node* tail;     // Wskaźnik na koniec listy 
    int size;       // Przechowuje aktualny rozmiar listy

public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    // Dodawanie elementów
    void addFront(int value);
    void addBack(int value);
    void addAt(int index, int value);

    // Usuwanie elementów
    void removeFront();
    void removeBack();
    void removeAt(int index);

    // Pozostałe funkcje
    bool find(int value);
    void display();
    void clear();
    int getSize() const { return size; }
};

#endif