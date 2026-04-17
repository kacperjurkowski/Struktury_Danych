#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <fstream>
#include <vector>
#include <numeric>
#include <string>

#include "dynamic_array.hpp"
#include "SinglyLinkedList.hpp"

using namespace std;
using namespace std::chrono;

void generujDane(DynamicArray &da, int quantity) {
    for (int i = 0; i < quantity; i++) {
        da.addEnd(rand() % 10000); // Losowe liczby od 0 do 9999
    }
    cout << "Wygenerowano " << quantity << " elementow.\n";
}

template <typename T>
void runResearch(string fileName, string structureName) {
    ofstream file(fileName, ios::app);
    int rozmiary[] = {5000, 10000, 20000, 40000, 60000, 80000, 100000, 120000};
    int seedy[] = {1670, 42, 123, 2024, 67, 888, 55, 99, 1010, 11};

    for (int n : rozmiary) {
        vector<long long> wynikiDlaRozmiaru;

        for (int s : seedy) {
            T ds;
            srand(s);
            for (int i = 0; i < n; i++) ds.addEnd(rand() % 10000);

            auto start = high_resolution_clock::now();
            ds.addFront(rand() % 10000); // Badana operacja
            auto stop = high_resolution_clock::now();

            wynikiDlaRozmiaru.push_back(duration_cast<nanoseconds>(stop - start).count());
        }

        // Obliczamy średnią z 10 seedów dla danego rozmiaru N
        long long srednia = accumulate(wynikiDlaRozmiaru.begin(), wynikiDlaRozmiaru.end(), 0LL) / wynikiDlaRozmiaru.size();
        
        cout << structureName << " (N=" << n << "): " << srednia << " ns" << endl;
        file << structureName << ";" << n << ";" << srednia << "\n";
    }
    file.close();
}

int main() {
    srand(1670);
    int wybor, wyborP1, wyborP2, wyborP3;
    DynamicArray da;
    SinglyLinkedList sll;
    high_resolution_clock::time_point start, end;

    do {
        cout << "--- HUB PROJEKTOWY: STRUKTURY DANYCH ---\n";
        cout << "1. Tablica Dynamiczna\n";
        cout << "2. Lista Jednokierunkowa\n";
        cout << "3. Lista Dwukierunkowa\n";
        cout << "4. Automatyczne Badania\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> wybor;

        if(wybor == 1){
            do {
                system("cls");
                cout << "--- TABLICA DYNAMICZNA ---\n";
                cout << "1. Generuj losowe dane\n";
                cout << "2. Dodanie na poczatek (addFront)\n";
                cout << "3. Dodanie na koniec (addEnd)\n";
                cout << "4. Dodanie losowo (addAt)\n";
                cout << "5. Usuwanie z poczatku (removeFront)\n";
                cout << "6. Usuwanie z konca (removeEnd)\n";
                cout << "7. Usuwanie losowo (removeAt)\n";
                cout << "8. Przeszukiwanie (search)\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborP1;

                switch(wyborP1){
                    case 1: int quantity;
                        cout << "Ile elementow wygenerowac? ";
                        cin >> quantity;

                        start = high_resolution_clock::now();
                        generujDane(da, quantity); 
                        end = high_resolution_clock::now();
                        
                        break;
                    case 2: 
                        start = high_resolution_clock::now();
                        da.addFront(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 3: 
                        start = high_resolution_clock::now();
                        da.addEnd(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 4: 
                        start = high_resolution_clock::now();
                        da.addAt(0, rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 5: 
                        start = high_resolution_clock::now();
                        da.removeFront(); 
                        end = high_resolution_clock::now();
                        break;
                    case 6: 
                        start = high_resolution_clock::now();
                        da.removeEnd(); 
                        end = high_resolution_clock::now();
                        break;
                    case 7: 
                        start = high_resolution_clock::now();
                        da.removeAt(0); 
                        end = high_resolution_clock::now();
                        break;
                    case 8: 
                        start = high_resolution_clock::now();
                        da.search(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;        
                }

                if (wyborP1 != 0 && wyborP1 != 8) {
                    auto duration = duration_cast<nanoseconds>(end - start);
                    cout << "\nCzas wykonania operacji: " << duration.count() << " ns\n";
                    system("pause");
                }
            } while (wyborP1 != 0);
        }

        if(wybor == 2){
            do {
                system("cls");
                cout << "--- LISTA JEDNOKIERUNKOWA ---\n";
                cout << "1. Generuj losowe dane\n";
                cout << "2. Dodanie na poczatek (addFront)\n";
                cout << "3. Dodanie na koniec (addEnd)\n";
                cout << "4. Dodanie losowo (addAt)\n";
                cout << "5. Usuwanie z poczatku (removeFront)\n";
                cout << "6. Usuwanie z konca (removeEnd)\n";
                cout << "7. Usuwanie losowo (removeAt)\n";
                cout << "8. Przeszukiwanie (search)\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborP2;

                switch(wyborP2){
                    case 1: int quantity;
                        cout << "Ile elementow wygenerowac? ";
                        cin >> quantity;

                        start = high_resolution_clock::now();
                        generujDane(da, quantity); 
                        end = high_resolution_clock::now();
                        
                        break;
                    case 2: 
                        start = high_resolution_clock::now();
                        sll.addFront(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 3: 
                        start = high_resolution_clock::now();
                        sll.addEnd(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 4: 
                        start = high_resolution_clock::now();
                        sll.addAt(0, rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 5: 
                        start = high_resolution_clock::now();
                        sll.removeFront(); 
                        end = high_resolution_clock::now();
                        break;
                    case 6: 
                        start = high_resolution_clock::now();
                        sll.removeEnd(); 
                        end = high_resolution_clock::now();
                        break;
                    case 7: 
                        start = high_resolution_clock::now();
                        sll.removeAt(0); 
                        end = high_resolution_clock::now();
                        break;
                    case 8: 
                        start = high_resolution_clock::now();
                        sll.find(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;        
                }
                if (wyborP2 != 0 && wyborP2 != 8) {
                    auto duration = duration_cast<nanoseconds>(end - start);
                    cout << "\nCzas wykonania operacji: " << duration.count() << " ns\n";
                    system("pause");
                }
            } while (wyborP2 != 0);
        }

        if(wybor == 3){
            do {
                system("cls");
                cout << "--- LISTA DWUKIERUNKOWA ---\n";
                cout << "1. Generuj losowe dane\n";
                cout << "2. Dodanie na poczatek (addFront)\n";
                cout << "3. Dodanie na koniec (addEnd)\n";
                cout << "4. Dodanie losowo (addAt)\n";
                cout << "5. Usuwanie z poczatku (removeFront)\n";
                cout << "6. Usuwanie z konca (removeEnd)\n";
                cout << "7. Usuwanie losowo (removeAt)\n";
                cout << "8. Przeszukiwanie (search)\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborP3;

                switch(wyborP3){
                    case 1: int quantity;
                        cout << "Ile elementow wygenerowac? ";
                        cin >> quantity;

                        start = high_resolution_clock::now();
                        generujDane(da, quantity); 
                        end = high_resolution_clock::now();
                        
                        break;
                    case 2: 
                        start = high_resolution_clock::now();
                        da.addFront(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 3: 
                        start = high_resolution_clock::now();
                        da.addEnd(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 4: 
                        start = high_resolution_clock::now();
                        da.addAt(0, rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 5: 
                        start = high_resolution_clock::now();
                        da.removeFront(); 
                        end = high_resolution_clock::now();
                        break;
                    case 6: 
                        start = high_resolution_clock::now();
                        da.removeEnd(); 
                        end = high_resolution_clock::now();
                        break;
                    case 7: 
                        start = high_resolution_clock::now();
                        da.removeAt(0); 
                        end = high_resolution_clock::now();
                        break;
                    case 8: 
                        start = high_resolution_clock::now();
                        da.search(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;        
                }

                if (wyborP3 != 0 && wyborP3 != 8) {
                    auto duration = duration_cast<nanoseconds>(end - start);
                    cout << "\nCzas wykonania operacji: " << duration.count() << " ns\n";
                    system("pause");
                }
            } while (wyborP3 != 0);
        }

        if (wybor == 4){
            {
            ofstream clearFile("wyniki_wszystko.txt");
            clearFile << "Struktura;Rozmiar;Seed;Operacja;Czas_ns\n";
            }
            runResearch<DynamicArray>("wyniki_wszystko.txt", "Tablica");
            runResearch<SinglyLinkedList>("wyniki_wszystko.txt", "Lista_Jednokierunkowa");
            //runResearch<DoublyLinkedList>("wyniki_wszystko.txt", "Lista_Dwukierunkowa");

            cout << "Wszystkie pomiary zakonczone!" << endl;
            break;
        }
    } while (wybor != 0);  
    return 0;
}