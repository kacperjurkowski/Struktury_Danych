#ifndef HASHAVLTREE_HPP
#define HASHAVLTREE_HPP

#include <iostream>

class HashAVLTree {
private:
    struct Node {
        int key;        //Klucz
        int value;      //Wartość przypisana do klucza
        Node* left;     //Lewe poddrzewo
        Node* right;    //Prawe poddrzewo
        int height;     //Wysokość drzewa

        Node(int k, int v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;         //Korzeń drzewa w tym kubełku
    int size;           //Liczba elementów w tym kubełku

    //Pomocnicze funkcje prywatne
    int getHeight(Node* n) const;
    int getBalanceFactor(Node* n) const;
    void updateHeight(Node* n);

    //Rotacje mechanizmu AVL
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);

    //Rdzeń operacji słownikowych
    Node* insertHelper(Node* node, int key, int value, bool& isNew);
    Node* removeHelper(Node* node, int key, bool& isDeleted);
    Node* getMinValueNode(Node* node);
    
    //Funkcje pomocnicze
    int* findHelper(Node* node, int key) const;
    void displayHelper(Node* node) const;
    void clearHelper(Node* node);

public:
    HashAVLTree();                          //Konstruktor
    ~HashAVLTree();                         //Dekonstruktor

    void insert(int key, int value);        //Wstawianie
    bool remove(int key);                   //Usuwanie
    int* find(int key) const;               //Szukanie
    void display() const;                   //Wyświetlanie
    void clear();                           //Zwalnianie pamięci
    
    int getSize() const { return size; }    //Zwracanie liczby elementów
};

#endif