#include "SinglyLinkedList.hpp"

SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

SinglyLinkedList::~SinglyLinkedList() {
    clear();
}

// Czyszczenie listy
void SinglyLinkedList::clear() {
    while (head != nullptr) {
        removeFront();
    }
}

// Dodawanie na początek - O(1)
void SinglyLinkedList::addFront(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

// Dodawanie na koniec - O(1)
void SinglyLinkedList::addEnd(int value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

// Dodawanie w dowolne miejsce - O(n)
void SinglyLinkedList::addAt(int index, int value) {
    if (index <= 0) {
        addFront(value);
    } else if (index >= size) {
        addEnd(value);
    } else {
        Node* newNode = new Node(value);
        Node* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }
}

// Usuwanie z początku - O(1)
void SinglyLinkedList::removeFront() {
    if (head == nullptr) return;

    Node* temp = head;
    head = head->next;
    delete temp;
    size--;

    if (head == nullptr) tail = nullptr; // Obsługa listy jednoelementowej
}

// Usuwanie z końca - O(n)
void SinglyLinkedList::removeEnd() {
    if (head == nullptr) return;

    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        delete tail;
        tail = temp;
        tail->next = nullptr;
    }
    size--;
}

// Usuwanie z dowolnego miejsca - O(n)
void SinglyLinkedList::removeAt(int index) {
    if (index < 0 || index >= size) return;
    if (index == 0) {
        removeFront();
    } else if (index == size - 1) {
        removeEnd();
    } else {
        Node* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        size--;
    }
}

// Wyszukiwanie elementu - O(n)
bool SinglyLinkedList::find(int value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) return true;
        temp = temp->next;
    }
    return false;
}

// Wyświetlanie zawartości
void SinglyLinkedList::display() {
    if (head == nullptr) {
        std::cout << "Lista jest pusta." << std::endl;
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
}