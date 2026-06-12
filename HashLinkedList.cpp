#include "HashLinkedList.hpp"

HashLinkedList::HashLinkedList() : head(nullptr), size(0) {}

HashLinkedList::~HashLinkedList() {
    clear();
}

void HashLinkedList::clear() {
    // Iteracyjne usuwanie wszystkich węzłów listy
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

void HashLinkedList::insert(int key, int value) {
    // Przeszukanie listy w celu aktualizacji istniejącego klucza
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->key == key) {
            temp->value = value;
            return;
        }
        temp = temp->next;
    }

    // Alokacja nowego węzła i wpięcie go na początek listy
    Node* newNode = new Node(key, value);
    newNode->next = head;
    head = newNode;
    size++;
}

bool HashLinkedList::remove(int key) {
    if (head == nullptr) return false;

    // Przypadek, gdy usuwany element jest na początku listy
    if (head->key == key) {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
        size--;
        return true;
    }

    // Szukanie elementu poprzedzającego element usuwany
    Node* temp = head;
    while (temp->next != nullptr && temp->next->key != key) {
        temp = temp->next;
    }

    // Usunięcie węzła ze środka lub końca listy
    if (temp->next != nullptr) {
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        size--;
        return true;
    }

    return false; 
}

int* HashLinkedList::find(int key) {
    // Liniowe przeszukiwanie listy w poszukiwaniu klucza
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->key == key) {
            return &(temp->value);
        }
        temp = temp->next;
    }
    return nullptr;
}

void HashLinkedList::display() const {
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << "(" << temp->key << " => " << temp->value << ") -> ";
        temp = temp->next;
    }
    std::cout << "nullptr";
}