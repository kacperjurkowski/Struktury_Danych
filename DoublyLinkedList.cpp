#include "DoublyLinkedList.hpp"

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

// Czyszczenie listy
void DoublyLinkedList::clear() {
    while (head != nullptr) {
        removeFront();                          // Czyści listę element po elemencie
    }
}

// Dodawanie na początek - O(1)
void DoublyLinkedList::addFront(int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;                   // Nowy wskazuje na starą głowę
        head->prev = newNode;                   // Stara głowa wskazuje wstecz na nowy
        head = newNode;                         // Aktualizacja głowy
    }
    size++;
}

// Dodawanie na koniec - O(1)
void DoublyLinkedList::addEnd(int value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;                   // Nowy wskazuje wstecz na stary ogon
        tail->next = newNode;                   // Stary ogon wskazuje w przód na nowy
        tail = newNode;                         // Aktualizacja ogona
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
            temp = temp->next;                  // Idziemy do elementu na indeksie
        }

        newNode->next = temp;                   // Nowy wskazuje w przód na temp
        newNode->prev = temp->prev;             // Nowy przejmuje lewego sąsiada temp
        temp->prev->next = newNode;             // Lewy sąsiad wskazuje na nowy
        temp->prev = newNode;                   // Temp wskazuje wstecz na nowy
        size++;
    }
}

// Usuwanie z początku - O(1)
void DoublyLinkedList::removeFront() {
    if (head == nullptr) return;

    Node* temp = head;
    head = head->next;                          // Głowa przesuwa się do przodu

    if (head!=nullptr) {
        head->prev = nullptr;                   // Odpięcie wskaźnika wstecznego nowej głowy
    } else {
        tail = nullptr;                         // Lista stała się pusta
    }

    delete temp;
    size--;
}

// Usuwanie z końca - O(n)
void DoublyLinkedList::removeEnd() {
    if(tail == nullptr) return;

    Node* temp = tail;
    tail = tail->prev;                          // Ogon cofa się do tyłu

    if(tail != nullptr){
        tail->next = nullptr;                   // Odpięcie wskaźnika w przód nowego ogona
    } else {
        head = nullptr;                         // Lista stała się pusta
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
            temp = temp->next;                  // Znalezienie konkretnego węzła
        }

        temp->prev->next = temp->next;          // Sąsiad z lewej pomija temp
        temp->next->prev = temp->prev;          // Sąsiad z prawej pomija temp

        delete temp;                            // Usunięcie węzła
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
        std::cout << temp->data << " -> ";      // Wypisanie danych
        temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
}