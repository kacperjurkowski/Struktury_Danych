#include "SinglyLinkedList.hpp"

SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

SinglyLinkedList::~SinglyLinkedList() {
    clear();
}

// Czyszczenie listy
void SinglyLinkedList::clear() {
    while (head != nullptr) {
        removeFront();                          // Usuwa elementy aż do opróżnienia listy
    }
}

// Dodawanie na początek - O(1)
void SinglyLinkedList::addFront(int value) {
    Node* newNode = new Node(value);            // Alokacja nowego węzła
    if (head == nullptr) {
        head = tail = newNode;                  // Pierwszy element zostaje głową i ogonem
    } else {
        newNode->next = head;                   // Nowy wskazuje na obecną głowę
        head = newNode;                         // Aktualizacja głowy
    }
    size++;
}

// Dodawanie na koniec - O(1)
void SinglyLinkedList::addEnd(int value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;                  // Lista była pusta
    } else {
        tail->next = newNode;                   // Obecny ogon wskazuje na nowy element
        tail = newNode;                         // Nowy element staje się ogonem
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
            temp = temp->next;                  // Szukanie węzła przed miejscem wstawienia
        }
        newNode->next = temp->next;             // Nowy przejmuje resztę listy
        temp->next = newNode;                   // Węzeł przed wskazuje na nowy
        size++;
    }
}

// Usuwanie z początku - O(1)
void SinglyLinkedList::removeFront() {
    if (head == nullptr) return;

    Node* temp = head;
    head = head->next;                          // Głowa przeskakuje na następny element
    delete temp;                                // Usunięcie starej głowy
    size--;

    if (head == nullptr) tail = nullptr;        // Obsługa listy jednoelementowej
}

// Usuwanie z końca - O(n)
void SinglyLinkedList::removeEnd() {
    if (head == nullptr) return;

    if (head == tail) {
        delete head;
        head = tail = nullptr;                  // Usuwanie jedynego elementu
    } else {
        Node* temp = head;
        while (temp->next != tail) {
            temp = temp->next;                  // Szukanie przedostatniego elementu
        }
        delete tail;                            // Usunięcie ostatniego
        tail = temp;                            // Przedostatni staje się ogonem
        tail->next = nullptr;                   // Odcięcie starego ogona
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
            temp = temp->next;                  // Znalezienie węzła przed usuwanym
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;            // Pominięcie usuwanego węzła
        delete toDelete;                        // Zwolnienie pamięci
        size--;
    }
}

// Wyszukiwanie elementu - O(n)
bool SinglyLinkedList::find(int value) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) return true;   // Znaleziono wartość
        temp = temp->next;                      // Przejście do kolejnego węzła
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
        std::cout << temp->data << " -> ";      // Wypisanie danych
        temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
}