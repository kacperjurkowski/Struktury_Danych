#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include <iostream>

// pojedynczy element listy
struct Node {
    int data;       // 4 bajtowa liczba
    Node* next;     // Wskaźnik na kolejny element
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;     // Wskaźnik na początek listy 
    Node* tail;     // Wskaźnik na koniec listy 
    int size;       // Przechowuje aktualny rozmiar listy

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    // Dodawanie elementów
    void addFront(int value);
    void addEnd(int value);
    void addAt(int index, int value);

    // Usuwanie elementów
    void removeFront();
    void removeEnd();
    void removeAt(int index);

    // Pozostałe funkcje
    bool find(int value);
    void display();
    void clear();
    int getSize() const { return size; }
};

#endif