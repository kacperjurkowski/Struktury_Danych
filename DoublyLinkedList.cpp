#include "DoublyLinkedList.hpp"

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

// Czyszczenie listy
void DoublyLinkedList::clear() {
    while (head != nullptr) {
        removeFront();
    }
}

// Dodawanie na początek - O(1)
void DoublyLinkedList::addFront(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

// Dodawanie na koniec - O(1)
void DoublyLinkedList::addEnd(int value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

// Dodawanie w dowolne miejsce - O(n)
void DoublyLinkedList::addAt(int index, int value) {
    if (index <= 0) {
        addFront(value);
    } else if (index >= size) {
        addEnd(value);
    } else {
        Node* newNode = new Node(value);
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }

        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
        size++;
    }
}

// Usuwanie z początku - O(1)
void DoublyLinkedList::removeFront() {
    if (head == nullptr) return;

    Node* temp = head;
    head = head->next;

    if (head!=nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }

    delete temp;
    size--;

}

// Usuwanie z końca - O(n)
void DoublyLinkedList::removeEnd() {
    if(tail == nullptr) return;

    Node* temp = tail;
    tail = tail->prev;

    if(tail != nullptr){
        tail->next = nullptr;
    } else {
        head = nullptr;
    }

    delete temp;
    size--;
}

// Usuwanie z dowolnego miejsca - O(n)
void DoublyLinkedList::removeAt(int index) {
    if (index < 0 || index >= size) return;
    if (index == 0) {
        removeFront();
    } else if (index == size - 1) {
        removeEnd();
    } else {
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        delete temp;
        size--;
    }
}

// Wyszukiwanie elementu - O(n)
bool DoublyLinkedList::find(int value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) return true;
        temp = temp->next;
    }
    return false;
}

// Wyświetlanie zawartości
void DoublyLinkedList::display() {
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