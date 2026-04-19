#include <iostream>
#include <cstdlib> //Funkcja rand/srand
#include <chrono> //Do pomiaru czasu
#include <fstream> //Zapis i odczyt danych
#include <vector> //Kontener do przechowywania czasów pomiarów
#include <numeric> //Dla acumulate
#include <string> //Przechowywanie fileName

#include "dynamic_array.hpp"
#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"

using namespace std;
using namespace std::chrono;

//Szablon do wypełnienia struktury losowymi danymi z zakresu 0-9999
template <typename T>
void generujDane(T &ds, int quantity) {
    //Pętla przechodząca przez strukturę o danej wielkości
    for (int i = 0; i < quantity; i++) {
        //Dodawanie wartości z zakresu 0-9999 na koniec struktury
        ds.addEnd(rand() % 10000);
    }
}

//Szablon funkcji, która przeprowadza automatyczne testy wydajnościowe
//Zamiast pisać 3 razy runResearch dla każdej struktury tworzę template
template <typename T>
void runResearch(string fileName, string structureName) {
    ofstream file(fileName, ios::app); //ios:app sprawia, że pomiar czasów kolejnych struktur nie jest nadpisywany

    //Rozmiary struktur do testów
    int rozmiary[] = {5000, 10000, 20000, 40000, 60000, 80000, 100000, 120000};

    //Seedy do testów
    int seedy[] = {1670, 42, 123, 2024, 67, 888, 55, 99, 1010, 11};

    for (int n : rozmiary) {
        vector<long long> t_addF, t_addE, t_addA, t_remF, t_remE, t_remA, t_find;

        for (int s : seedy) {
            T ds; //Tworzenie nowej instancji struktury (Tablica Dynamiczna/Lista Jednokierunkowa/Lista Dwukierunkowa)
            srand(s); //Generator o konkretnym seedzie
            for (int i = 0; i < n; i++) ds.addEnd(rand() % 10000);

            //Losowa wartość w zakresie 0-9999
            int val = rand() % 10000; 

            //Losuje bezpieczny indeks wewnątrz struktury od 0 do rozmiar-1
            int idx = (ds.getSize() > 0) ? rand() % ds.getSize() : 0; 

            high_resolution_clock::time_point start, stop;

            // 1. Add Front
            start = high_resolution_clock::now();
            ds.addFront(val);
            stop = high_resolution_clock::now();
            t_addF.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.removeFront(); // Przywrócenie rozmiaru 

            // 2. Add End
            start = high_resolution_clock::now();
            ds.addEnd(val);
            stop = high_resolution_clock::now();
            t_addE.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.removeEnd(); // Przywrócenie rozmiaru 

            // 3. Add At
            start = high_resolution_clock::now();
            ds.addAt(idx, val);
            stop = high_resolution_clock::now();
            t_addA.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.removeAt(idx); // Przywrócenie rozmiaru 

            // 4. Remove Front
            start = high_resolution_clock::now();
            ds.removeFront();
            stop = high_resolution_clock::now();
            t_remF.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.addFront(val); // Przywrócenie rozmiaru 

            // 5. Remove End
            start = high_resolution_clock::now();
            ds.removeEnd();
            stop = high_resolution_clock::now();
            t_remE.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.addEnd(val); // Przywrócenie rozmiaru 

            // 6. Remove At
            start = high_resolution_clock::now();
            ds.removeAt(idx);
            stop = high_resolution_clock::now();
            t_remA.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.addAt(idx, val); // Przywrócenie rozmiaru 

            // 7. Search
            start = high_resolution_clock::now();
            ds.find(val);
            stop = high_resolution_clock::now();
            t_find.push_back(duration_cast<nanoseconds>(stop - start).count());
        }

        //Funkcja pomocnicza do zapisu średniej | [&] - capture by reference (skrót do oryginału)
        auto saveAvg = [&](string op, vector<long long>& v) { //Teoretycznie powinien być int bo nie bazujemy na tak dużych liczbach
            //Iloraz sumy wszystkich elementów w wektorze przez ich ilość
            long long avg = accumulate(v.begin(), v.end(), 0LL) / v.size();
            //Zapis wyniku do pliku csv
            file << structureName << ";" << n << ";" << op << ";" << avg << "\n";
        };
        
        //Zapis średnich dla bieżącego rozmiaru
        saveAvg("addFront", t_addF);
        saveAvg("addEnd", t_addE);
        saveAvg("addAt", t_addA);
        saveAvg("removeFront", t_remF);
        saveAvg("removeEnd", t_remE);
        saveAvg("removeAt", t_remA);
        saveAvg("find", t_find);

        cout << "  N=" << n << " zakonczone." << endl;
    }
    file.close();
}

int main() {
    srand(1670); //Seed nadany do testów manualnych
    int wybor, wyborP1, wyborP2, wyborP3;
    DynamicArray da;
    SinglyLinkedList sll;
    DoublyLinkedList dll;
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
                cout << "8. Przeszukiwanie (find)\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborP1;

                switch(wyborP1){
                    case 1: 
                        int quantity;
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
                        da.addAt(rand() % da.getSize(), rand() % 10000); 
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
                        da.removeAt(rand() % da.getSize()); 
                        end = high_resolution_clock::now();
                        break;
                    case 8: 
                        start = high_resolution_clock::now();
                        da.find(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;        
                }

                if (wyborP1 != 0 && wyborP1 != 9) {
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
                cout << "8. Przeszukiwanie (find)\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborP2;

                switch(wyborP2){
                    case 1: int quantity;
                        cout << "Ile elementow wygenerowac? ";
                        cin >> quantity;

                        start = high_resolution_clock::now();
                        generujDane(sll, quantity); 
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
                        sll.addAt(rand() % sll.getSize(), rand() % 10000); 
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
                        sll.removeAt(rand() % sll.getSize()); 
                        end = high_resolution_clock::now();
                        break;
                    case 8: 
                        start = high_resolution_clock::now();
                        sll.find(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;        
                }
                if (wyborP2 != 0 && wyborP2 != 9) {
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
                cout << "8. Przeszukiwanie (find)\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborP3;

                switch(wyborP3){
                    case 1: int quantity;
                        cout << "Ile elementow wygenerowac? ";
                        cin >> quantity;

                        start = high_resolution_clock::now();
                        generujDane(dll, quantity); 
                        end = high_resolution_clock::now();
                        
                        break;
                    case 2: 
                        start = high_resolution_clock::now();
                        dll.addFront(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 3: 
                        start = high_resolution_clock::now();
                        dll.addEnd(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 4: 
                        start = high_resolution_clock::now();
                        dll.addAt(rand() % dll.getSize(), rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;
                    case 5: 
                        start = high_resolution_clock::now();
                        dll.removeFront(); 
                        end = high_resolution_clock::now();
                        break;
                    case 6: 
                        start = high_resolution_clock::now();
                        dll.removeEnd(); 
                        end = high_resolution_clock::now();
                        break;
                    case 7: 
                        start = high_resolution_clock::now();
                        dll.removeAt(rand() % dll.getSize()); 
                        end = high_resolution_clock::now();
                        break;
                    case 8: 
                        start = high_resolution_clock::now();
                        dll.find(rand() % 10000); 
                        end = high_resolution_clock::now();
                        break;        
                }

                if (wyborP3 != 0 && wyborP3 != 9) {
                    auto duration = duration_cast<nanoseconds>(end - start);
                    cout << "\nCzas wykonania operacji: " << duration.count() << " ns\n";
                    system("pause");
                }
            } while (wyborP3 != 0);
        }

        if (wybor == 4){
            {
            ofstream clearFile("wyniki_wszystko.txt");
            clearFile << "Struktura;Rozmiar;Operacja;Czas_ns\n";
            }
            runResearch<DynamicArray>("wyniki_wszystko.txt", "Tablica");
            runResearch<SinglyLinkedList>("wyniki_wszystko.txt", "Lista_Jednokierunkowa");
            runResearch<DoublyLinkedList>("wyniki_wszystko.txt", "Lista_Dwukierunkowa");

            cout << "Wszystkie pomiary zakonczone!" << endl;
            break;
        }
    } while (wybor != 0);  
    return 0;
}