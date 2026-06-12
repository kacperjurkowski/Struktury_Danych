#include <iostream>
#include <random> //Liczby pseudolosowe
#include <chrono> //Pomiar czasu
#include <fstream> //Zapis i odczyt danych
#include <vector> //Kontener do przechowywania czasów pomiarów
#include <numeric> //Dla acumulate
#include <string> //Przechowywanie fileName

#include "CuckooHash.hpp"
#include "HashTableChaining.hpp"
//#include "HashTableAVL.hpp"

using namespace std;
using namespace std::chrono;

//Szablon do wypełnienia struktury losowymi danymi z zakresu 0-9999
template <typename T>
void generujDane(T &ds, int quantity, mt19937 &gen) {
    //Zakresy (4 bajtowa liczba całkowita / większy priorytet niż wielkość struktury)
    //Zakres priorytetów jest 10-krotnie większy od rozmiaru struktury
    uniform_int_distribution<int> distValue(0, quantity * 10);

    for (int i = 0; i < quantity; i++) {

        //Dodanie klucza i wartości (klucz - unikalna, wartość - losowa)
        ds.insert(i, distValue(gen));
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
        //Wektory przechowujące czasy dla każdej z prób
        vector<long long> t_ins, t_rem;

        for (int s : seedy) {
            T ds; //Tworzenie nowej instancji struktury (Kolejka Priorytetowa - Kopiec/Tablica Nieposortowana)
            mt19937 gen(s); //Generator o konkretnym seedzie

            generujDane(ds, n, gen);        //Wypełnienie struktury do rozmiaru N

            //Zakresy (4 bajtowa liczba całkowita / większy priorytet niż wielkość struktury)
            uniform_int_distribution<int> distValue(0, n * 10);
            uniform_int_distribution<int> distKey(0, n - 1);

            int randomKey = distKey(gen);           //Wygenerowany klucz
            int randomValue = distValue(gen);          //Wygenerowana wartość

            high_resolution_clock::time_point start, stop;

            // 1. Insert
            int uniqueKey = n + 10;
            start = high_resolution_clock::now();
            ds.insert(uniqueKey, randomValue);
            stop = high_resolution_clock::now();
            t_ins.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.remove(uniqueKey);

            // 2. Remove
            start = high_resolution_clock::now();
            ds.remove(randomKey);
            stop = high_resolution_clock::now();
            t_rem.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.insert(randomKey, randomValue);

        }

        //Funkcja pomocnicza do zapisu średniej | [&] - capture by reference (skrót do oryginału)
        auto saveAvg = [&](string op, vector<long long>& v) { //Teoretycznie powinien być int bo nie bazujemy na tak dużych liczbach
            //Iloraz sumy wszystkich elementów w wektorze przez ich ilość
            long long avg = accumulate(v.begin(), v.end(), 0LL) / v.size();
            //Zapis wyniku do pliku csv
            file << structureName << ";" << n << ";" << op << ";" << avg << "\n";
        };
        
        //Zapis średnich dla bieżącego rozmiaru
        saveAvg("insert", t_ins);
        saveAvg("remove", t_rem);

        cout << " Struktura: " << structureName << "N=" << n << " zakonczone." << endl;
    }
    file.close();
}

int main() {
    mt19937 gen(1670); //Seed nadany do testów manualnych

    int wybor, wyborMenu;
    int quantity = 20; //Domyślny rozmiar 

    int k, v, outVal; //Klucz i wartość

    //Alokacja struktur do testów
    HashTableChaining hll(quantity); 
    //HashTableAVL hta;
    CuckooHash ch;

    high_resolution_clock::time_point start, end;

    do {
        system("cls");
        cout << "--- HUB PROJEKTOWY: STRUKTURY DANYCH ---\n";
        cout << "1. Tablica mieszajaca - Lancuchowa (Lista)\n";
        cout << "2. Tablica mieszajaca - Lancuchowa (Drzewo AVL)\n";
        cout << "3. Tablica mieszajaca - Cuckoo Hashing\n";
        cout << "4. Automatyczne Badania\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> wybor;

        if(wybor == 1){
            do {
                system("cls");
                cout << "--- MENU: Tablica mieszajaca - Lista ---\n";
                cout << "1. Generuj losowe dane (" << quantity << ")\n";
                cout << "2. Insert\n";
                cout << "3. Remove\n";
                cout << "4. Szukaj (find)\n";
                cout << "5. Wyswietl (Display))\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborMenu;

                switch(wyborMenu){
                    case 1: 
                        start = high_resolution_clock::now();
                        generujDane(hll, quantity, gen); 
                        end = high_resolution_clock::now();
                        break;
                    case 2:
                        cout << "Podaj klucz oraz wartość: " << endl;
                        cin >> k >> v;
                        start = high_resolution_clock::now();
                        hll.insert(k, v);
                        end = high_resolution_clock::now();
                        break;
                    case 3:
                        cout << "Podaj klucz do usuniecia: " << endl;
                        cin >> k;
                        start = high_resolution_clock::now();
                        hll.remove(k);
                        end = high_resolution_clock::now();
                        break;
                    case 4:
                        cout << "Podaj klucz do znalezienia: " << endl;
                        cin >> k;
                        start = high_resolution_clock::now();
                        hll.find(k);
                        end = high_resolution_clock::now();
                        break;
                    case 5:
                        hll.display();
                        break;
                }

                if (wyborMenu != 0 && wyborMenu != 5) {
                    auto duration = duration_cast<nanoseconds>(end - start);
                    cout << "\nCzas wykonania operacji: " << duration.count() << " ns\n";
                    system("pause");
                }
            } while (wyborMenu != 0);
        }

        if(wybor == 2){
            do {
                system("cls");
                cout << "--- MENU: Tablica mieszajaca - Drzewo AVL ---\n";
                cout << "1. Generuj losowe dane (" << quantity << ")\n";
                cout << "2. Insert\n";
                cout << "3. Remove\n";
                cout << "4. Szukaj (find)\n";
                cout << "5. Wyswietl (Display))\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborMenu;

                switch(wyborMenu){ // W Budowie
                    case 1: 
                        start = high_resolution_clock::now();
                        //generujDane(hta, quantity, gen); 
                        end = high_resolution_clock::now();
                        break;
                    case 2:
                        start = high_resolution_clock::now();
                        //hll.insert(k, v);
                        end = high_resolution_clock::now();
                        break;
                    case 3:
                        start = high_resolution_clock::now();
                        //hll.remove(k);
                        end = high_resolution_clock::now();
                        break;
                    case 4:
                        start = high_resolution_clock::now();
                        //hll.find(k);
                        end = high_resolution_clock::now();
                        break;
                    case 5:
                        //hll.display();
                        break;
                }

                if (wyborMenu != 0 && wyborMenu != 5) {
                    auto duration = duration_cast<nanoseconds>(end - start);
                    cout << "\nCzas wykonania operacji: " << duration.count() << " ns\n";
                    system("pause");
                }
            } while (wyborMenu != 0);
        }

        if(wybor == 3){
            do {
                system("cls");
                cout << "--- Tablica mieszajaca - Cuckoo Hashing ---\n";
                cout << "1. Generuj losowe dane (" << quantity << ")\n";
                cout << "2. Insert\n";
                cout << "3. Remove\n";
                cout << "4. Szukaj (find)\n";
                cout << "5. Wyswietl (Display))\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborMenu;

                switch(wyborMenu){
                    case 1: 
                        start = high_resolution_clock::now();
                        generujDane(ch, quantity, gen); 
                        end = high_resolution_clock::now();
                        break;
                    case 2:
                        cout << "Podaj klucz oraz wartość: " << endl;
                        cin >> k >> v;
                        start = high_resolution_clock::now();
                        ch.insert(k, v);
                        end = high_resolution_clock::now();
                        break;
                    case 3:
                        cout << "Podaj klucz do usuniecia: " << endl;
                        cin >> k;
                        start = high_resolution_clock::now();
                        ch.remove(k);
                        end = high_resolution_clock::now();
                        break;
                    case 4:
                        cout << "Podaj klucz do znalezienia: " << endl;
                        cin >> k;
                        start = high_resolution_clock::now();
                        if(ch.find(k, outVal)) {
                            cout << "Znaleziono wartosc: " << outVal << endl;
                        } else {
                            cout << "Nieznaleziono wartosci." << endl;
                        }
                        end = high_resolution_clock::now();
                        break;
                    case 5:
                        ch.display();
                        break;
                }

                if (wyborMenu != 0 && wyborMenu != 5) {
                    auto duration = duration_cast<nanoseconds>(end - start);
                    cout << "\nCzas wykonania operacji: " << duration.count() << " ns\n";
                    system("pause");
                }
            } while (wyborMenu != 0);
        }

        if (wybor == 4){
            ofstream clearFile("wyniki.txt");
            clearFile << "Struktura;Rozmiar;Operacja;Czas_ns\n";
            clearFile.close();
            
            runResearch<HashTableChaining>("wyniki.txt", "Chaining_Lista");
            //runResearch<HashTableChaining>("wyniki.txt", "Chaining_AVL");
            runResearch<CuckooHash>("wyniki.txt", "Cuckoo_Hashing");

            cout << "Wszystkie pomiary zakonczone!" << endl;
            break;
        }
    } while (wybor != 0);  
    return 0;
}