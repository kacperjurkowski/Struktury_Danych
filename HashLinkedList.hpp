#ifndef HASHLINKEDLIST_HPP
#define HASHLINKEDLIST_HPP

#include <iostream>

class HashLinkedList {
private:
    struct Node {
        int key;        
        int value;      
        Node* next;

        Node(int k, int v) : key(k), value(v), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    HashLinkedList();
    ~HashLinkedList();

    void insert(int key, int value);
    bool remove(int key);
    int* find(int key); 
    void display() const;
    void clear();
    int getSize() const { return size; }
};

#endif