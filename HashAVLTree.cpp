#include "HashAVLTree.hpp"

//Konstruktor
HashAVLTree::HashAVLTree() : root(nullptr), size(0) {}

//Dekonstruktor
HashAVLTree::~HashAVLTree() {
    clear();
}

//Zwalnianie pamięci i wyzerowanie liczby elementów
void HashAVLTree::clear() {
    clearHelper(root);
    root = nullptr;
    size = 0;
}

//Metoda pomocnicza do zwalniania pamięci (usuwa lewe i prawe dzieci :DD)
void HashAVLTree::clearHelper(Node* node) {
    if (node != nullptr) {
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
}

//Metoda zwracająca wysokość węzła
int HashAVLTree::getHeight(Node* n) const {
    return (n == nullptr) ? 0 : n->height;
}

//Metoda badająca równowagę drzewa
int HashAVLTree::getBalanceFactor(Node* n) const {
    return (n == nullptr) ? 0 : getHeight(n->left) - getHeight(n->right);
}

//Metoda aktualizująca wysokość drzewa
void HashAVLTree::updateHeight(Node* n) {
    if (n != nullptr) {

        //Max wysokości od lewego skrzydła i wysokości od prawego skrzydła + 1 jako dodanie węzła
        n->height = 1 + std::max(getHeight(n->left), getHeight(n->right)); 
    }
}

//Metoda rotująca elementy, gdy lewe skrzydło stało się zbyt ciężkie
HashAVLTree::Node* HashAVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

//Metoda rotująca elementy, gdy prawe skrzydło stało się zbyt ciężkie
HashAVLTree::Node* HashAVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

//Metoda wstawiania (? jeżeli klucz istnieje to nadpisuje wartość : tworzy nowy węzeł i zwiększa size)
void HashAVLTree::insert(int key, int value) {
    bool isNew = false;
    root = insertHelper(root, key, value, isNew);
    if (isNew) {
        size++;
    }
}

//Metoda pomocnicza wstawiania
HashAVLTree::Node* HashAVLTree::insertHelper(Node* node, int key, int value, bool& isNew) {
    if (node == nullptr) {
        isNew = true;
        return new Node(key, value);
    }

    if (key < node->key) {
        node->left = insertHelper(node->left, key, value, isNew);
    } else if (key > node->key) {
        node->right = insertHelper(node->right, key, value, isNew);
    } else {
        node->value = value; // Aktualizacja istniejącego klucza
        isNew = false;
        return node;
    }

    updateHeight(node);                     //Aktualizacja wysokości rodzica
    int balance = getBalanceFactor(node);   //Sprawdzenie balansu rodzica

    //Ciężar ucieka do zewnątrz
    //Lewy-Lewy
    if (balance > 1 && key < node->left->key) return rotateRight(node);
    
    //Prawy-Prawy
    if (balance < -1 && key > node->right->key) return rotateLeft(node);

    //Ciężar ucieka do wewnątrz
    //Lewy-Prawy
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    //Prawy-Lewy
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

//Metoda usuwająca 
bool HashAVLTree::remove(int key) {
    bool isDeleted = false;
    root = removeHelper(root, key, isDeleted);
    if (isDeleted) {
        size--;
    }
    return isDeleted;
}

//Metoda szukająca najmniejszego klucza w poddrzewie
HashAVLTree::Node* HashAVLTree::getMinValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

//Metoda pomocnicza rozważająca trzy przypadki usuwania węzła
HashAVLTree::Node* HashAVLTree::removeHelper(Node* node, int key, bool& isDeleted) {
    if (node == nullptr) {
        isDeleted = false;
        return node;
    }

    if (key < node->key) {
        node->left = removeHelper(node->left, key, isDeleted);
    } else if (key > node->key) {
        node->right = removeHelper(node->right, key, isDeleted);
    } else {
        isDeleted = true;

        //Warunek, węzeł posiada co najwyżej 1 dziecko
        if ((node->left == nullptr) || (node->right == nullptr)) {

            //Jeśli lewe/prawe dziecko istnieje, przypisz je do wskaźnika
            Node* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {  //Jeżeli węzeł nie ma dzieci
                temp = node;
                node = nullptr;
            } else {                //Jeżeli węzeł ma 1 dziecko
                *node = *temp;      //Nadpisanie rodzica jego własnym dzieckiem
            }
            delete temp;            //Usunięcie starego syna

        //Warunek, węzeł ma 2 dzieci    
        } else {
            Node* temp = getMinValueNode(node->right);          //Szukanie najmniejszego elementu w prawym poddrzewie
            node->key = temp->key;                              //Nadpisanie klucza starego węzła
            node->value = temp->value;                          //Nadpisanie wartości starego węzła
            node->right = removeHelper(node->right, temp->key, isDeleted);
        }
    }

    if (node == nullptr) return node;

    updateHeight(node);
    int balance = getBalanceFactor(node);

    //Badanie drzewa za pomocą algorytmu balansu
    //Ciężar ucieka do zewnątrz
    //Lewy-Lewy
    if (balance > 1 && getBalanceFactor(node->left) >= 0) return rotateRight(node);
    //Prawy-Prawy
    if (balance < -1 && getBalanceFactor(node->right) <= 0) return rotateLeft(node);

    //Ciężar ucieka do wewnątrz
    //Lewy-Prawy
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    //Prawy-Lewy
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

//Metoda wyszukiwania klucza
int* HashAVLTree::find(int key) const {
    return findHelper(root, key);
}

int* HashAVLTree::findHelper(Node* node, int key) const {
    if (node == nullptr) return nullptr;                        //Szukanego klucza nie ma w tym miejscu
    if (key == node->key) return &(node->value);                //Jeżeli znajdzie pobiera adres wartości
    if (key < node->key) return findHelper(node->left, key);    //Jeżeli klucz jest mniejszy niż obecny -> findHelper dla lewego dziecka
    return findHelper(node->right, key);                        //findHelper dla prawego dziecka
}

//Metoda wyświetlająca drzewo
void HashAVLTree::display() const {
    if (root == nullptr) {
        std::cout << "puste";
        return;
    }
    displayHelper(root);
}

//Metoda pomocnicza do wyświetlania drzewa
void HashAVLTree::displayHelper(Node* node) const {
    if (node != nullptr) {
        std::cout << "[";
        displayHelper(node->left);
        std::cout << " (" << node->key << " => " << node->value << ") ";
        displayHelper(node->right);
        std::cout << "]";
    }
}