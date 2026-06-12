#include "CuckooHash.hpp"
#include <cstdlib>
#include <ctime>

CuckooHash::CuckooHash() {
    capacity = 8;
    size = 0;
    table1 = new Entry[capacity];
    table2 = new Entry[capacity];

    // Generator
    std::srand(std::time(nullptr));
    hashSeed1 = std::rand() % 97 + 7;
    hashSeed2 = std::rand() % 97 + 13;
}

CuckooHash::CuckooHash(int dummyCapacity) : CuckooHash() {}

CuckooHash::~CuckooHash() {
    delete[] table1;
    delete[] table2;
}

int CuckooHash::hash1(int key) const {
    int h = (key * hashSeed1) % capacity;
    return (h < 0) ? h + capacity : h;
}

int CuckooHash::hash2(int key) const {
    int h = (key * hashSeed2) % capacity;
    // Korekta przesunięcia indeksu zapobiega identycznym wynikom dla małych kluczy
    return ((h + 3) % capacity + capacity) % capacity;
}

void CuckooHash::rehash() {
    int oldCapacity = capacity;
    Entry* oldTable1 = table1;
    Entry* oldTable2 = table2;

    // Alokacja nowych tablic o podwojonym rozmiarze
    capacity *= 2;
    table1 = new Entry[capacity];
    table2 = new Entry[capacity];
    size = 0; 

    // Losowanie nowych seedów w celu zmiany mapowania indeksów
    hashSeed1 = std::rand() % 97 + 7;
    hashSeed2 = std::rand() % 97 + 13;

    // Przepisanie dotychczasowych elementów do nowej struktury
    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable1[i].isOccupied) insert(oldTable1[i].key, oldTable1[i].value);
        if (oldTable2[i].isOccupied) insert(oldTable2[i].key, oldTable2[i].value);
    }

    delete[] oldTable1;
    delete[] oldTable2;
}

void CuckooHash::insert(int key, int value) {
    // Obsługa aktualizacji wartości, jeśli klucz już istnieje w tablicy
    int existingValue;
    if (find(key, existingValue)) {
        if (table1[hash1(key)].isOccupied && table1[hash1(key)].key == key) table1[hash1(key)].value = value;
        else table2[hash2(key)].value = value;
        return;
    }

    int currentKey = key;
    int currentValue = value;
    int maxLoops = capacity * 2;

    // Pętla wyszukiwania miejsca i eksmisji
    for (int loop = 0; loop < maxLoops; loop++) {
        // Próba zapisu w pierwszej tablicy
        int idx1 = hash1(currentKey);
        if (!table1[idx1].isOccupied) {
            table1[idx1].key = currentKey;
            table1[idx1].value = currentValue;
            table1[idx1].isOccupied = true;
            size++;
            return;
        }
        // Wypchnięcie starego elementu z pierwszej tablicy
        int tempKey = table1[idx1].key;
        int tempValue = table1[idx1].value;
        table1[idx1].key = currentKey; table1[idx1].value = currentValue;
        currentKey = tempKey; currentValue = tempValue;

        // Próba zapisu wyeksmitowanego elementu w drugiej tablicy
        int idx2 = hash2(currentKey);
        if (!table2[idx2].isOccupied) {
            table2[idx2].key = currentKey;
            table2[idx2].value = currentValue;
            table2[idx2].isOccupied = true;
            size++;
            return;
        }
        // Wypchnięcie starego elementu z drugiej tablicy
        tempKey = table2[idx2].key;
        tempValue = table2[idx2].value;
        table2[idx2].key = currentKey; table2[idx2].value = currentValue;
        currentKey = tempKey; currentValue = tempValue;
    }

    // Wykryto cykl (brak wolnego miejsca): wymuszone wstawienie na losowy indeks
    int forcedIdx = hash1(currentKey);
    int tempKey = table1[forcedIdx].key;
    int tempValue = table1[forcedIdx].value;
    
    table1[forcedIdx].key = currentKey; table1[forcedIdx].value = currentValue;
    size++; // Element fizycznie zajął slot, więc zwiększamy rozmiar przed rehashem

    // Powiększenie tablicy i ponowne wstawienie ostatniego wypchniętego elementu
    rehash();
    insert(tempKey, tempValue); 
}

void CuckooHash::remove(int key) {
    int idx1 = hash1(key), idx2 = hash2(key);
    // Sprawdzenie obu potencjalnych pozycji
    if (table1[idx1].isOccupied && table1[idx1].key == key) { table1[idx1].isOccupied = false; size--; }
    else if (table2[idx2].isOccupied && table2[idx2].key == key) { table2[idx2].isOccupied = false; size--; }
}

bool CuckooHash::find(int key, int& outValue) const {
    int idx1 = hash1(key), idx2 = hash2(key);
    // Weryfikacja obecności klucza na obu możliwych pozycjach indeksowych
    if (table1[idx1].isOccupied && table1[idx1].key == key) { outValue = table1[idx1].value; return true; }
    if (table2[idx2].isOccupied && table2[idx2].key == key) { outValue = table2[idx2].value; return true; }
    return false;
}

void CuckooHash::display() const {
    for (int t = 1; t <= 2; t++) {
        std::cout << "--- TABLICA " << t << " ---\n";
        for (int i = 0; i < capacity; i++) {
            Entry e = (t == 1) ? table1[i] : table2[i];
            if (e.isOccupied) std::cout << "[" << i << "]: (" << e.key << " => " << e.value << ")\n";
            else std::cout << "[" << i << "]: EMPTY\n";
        }
    }
}   