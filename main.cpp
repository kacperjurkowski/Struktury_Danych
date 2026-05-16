#include <iostream>
#include <random> //Losowość
#include <chrono> //Do pomiaru czasu
#include <fstream> //Zapis i odczyt danych
#include <vector> //Kontener do przechowywania czasów pomiarów
#include <numeric> //Dla acumulate
#include <string> //Przechowywanie fileName

#include "dynamic_array.hpp"
#include "PriorityQueueArray.hpp"
#include "heap.hpp"

using namespace std;
using namespace std::chrono;

//Szablon do wypełnienia struktury losowymi danymi z zakresu 0-9999
template <typename T>
void generujDane(T &ds, int quantity, mt19937 &gen) {
    //Zakresy (4 bajtowa liczba całkowita / większy priorytet niż wielkość struktury)
    uniform_int_distribution<int> distPriority(0, quantity * 10);

    //Pętla przechodząca przez strukturę o danej wielkości
    for (int i = 0; i < quantity; i++) {

        //Dodanie wartość i priorytet
        ds.insert(i, distPriority(gen));
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
        vector<long long> t_ins, t_ext, t_peek, t_dec, t_inc, t_ret;

        for (int s : seedy) {
            T ds; //Tworzenie nowej instancji struktury (Kolejka Priorytetowa - Kopiec/Tablica Nieposortowana)
            mt19937 gen(s); //Generator o konkretnym seedzie

            generujDane(ds, n, gen);        //Wypełnienie struktury do rozmiaru N

            //Zakresy (4 bajtowa liczba całkowita / większy priorytet niż wielkość struktury)
            uniform_int_distribution<int> distValue(0, n - 1);
            uniform_int_distribution<int> distPriority(0, n * 10);

            int v = distValue(gen);           //Wygenerowany element
            int p = distPriority(gen);          //Wygenerowany priorytet

            high_resolution_clock::time_point start, stop;

            // 1. Insert
            start = high_resolution_clock::now();
            ds.insert(v, p);
            stop = high_resolution_clock::now();
            t_ins.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.extractMax(); //Przywrócenie rozmiaru 

            // 2. ExtractMax
            start = high_resolution_clock::now();
            ds.extractMax();
            stop = high_resolution_clock::now();
            t_ext.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.insert(v, p); //Przywrócenie rozmiaru 

            // 3. Peek
            start = high_resolution_clock::now();
            ds.peek();
            stop = high_resolution_clock::now();
            t_peek.push_back(duration_cast<nanoseconds>(stop - start).count());

            // 4. Decrease_key
            start = high_resolution_clock::now();
            ds.decrease_key(v, p);
            stop = high_resolution_clock::now();
            t_dec.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.increase_key(v, p); //Przywrócenie priorytetu

            // 5. Increase_key
            start = high_resolution_clock::now();
            ds.increase_key(v, p);
            stop = high_resolution_clock::now();
            t_inc.push_back(duration_cast<nanoseconds>(stop - start).count());
            ds.decrease_key(v, p); //Przywrócenie priorytetu

            // 6. Return_size
            start = high_resolution_clock::now();
            ds.return_size();
            stop = high_resolution_clock::now();
            t_ret.push_back(duration_cast<nanoseconds>(stop - start).count());

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
        saveAvg("extractMax", t_ext);
        saveAvg("peek", t_peek);
        saveAvg("decrease_key", t_dec);
        saveAvg("increase_key", t_inc);
        saveAvg("return_size", t_ret);

        cout << " Struktura: " << structureName << "N=" << n << " zakonczone." << endl;
    }
    file.close();
}

int main() {
    mt19937 gen(1670); //Seed nadany do testów manualnych

    int wybor, wyborP1, wyborP2, wyborP3, v_man, p_man;;
    int quantity = 50;

    Heap h;
    PriorityQueueArray pqa;
    high_resolution_clock::time_point start, end;

    do {
        cout << "--- HUB PROJEKTOWY: STRUKTURY DANYCH ---\n"; //Zmienić wykonuje ich serię (np. 100 powtórzeń) dla każdego seeda
        cout << "1. Kolejka Priorytetowa - Kopiec\n";
        cout << "2. Kolejka Priorytetowa - Tablica Nieposortowana\n";
        cout << "3. Automatyczne Badania\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> wybor;

        if(wybor == 1){
            do {
                system("cls");
                cout << "--- MENU: KOPIEC ---\n";
                cout << "1. Generuj losowe dane (" << quantity << ")\n";
                cout << "2. ExtractMax\n";
                cout << "3. Peek\n";
                cout << "4. Decrease_key\n";
                cout << "5. Increase_key\n";
                cout << "6. Wyswietl (Display))\n";
                cout << "7. Rozmiar (Return_size)\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborP1;

                switch(wyborP1){
                    case 1: 
                        start = high_resolution_clock::now();
                        generujDane(h, quantity, gen); 
                        end = high_resolution_clock::now();
                        break;
                    case 2: 
                        start = high_resolution_clock::now();
                        h.extractMax();
                        end = high_resolution_clock::now();
                        break;
                    case 3: {
                        start = high_resolution_clock::now();
                        Element top = h.peek();
                        end = high_resolution_clock::now();
                        if(top.priority != -1) {
                            cout << "Element o najwyzszym priorytecie: [" << top.priority << ":" << top.value << "]" << endl;
                        } else {
                            cout << "Kolejka jest pusta!" << endl;
                        }
                        break;
                    }
                    case 4: 
                        cout << "Podaj wartosc i nowy priorytet: ";
                        cin >> v_man >> p_man;
                        start = high_resolution_clock::now();
                        h.decrease_key(v_man, p_man);
                        end = high_resolution_clock::now();
                        break;      
                    case 5: 
                        cout << "Podaj wartosc i nowy priorytet: ";
                        cin >> v_man >> p_man;
                        start = high_resolution_clock::now();
                        h.increase_key(v_man, p_man);
                        end = high_resolution_clock::now();
                        break;      
                    case 6: 
                        start = high_resolution_clock::now();
                        h.display();
                        end = high_resolution_clock::now();
                        break;
                    case 7: 
                        start = high_resolution_clock::now();
                        cout << "Aktualny rozmiar struktury: " << h.return_size() << endl;
                        end = high_resolution_clock::now();
                        system("pause");
                        break;  
                }

                if (wyborP1 != 0 && wyborP1 != 7) {
                    auto duration = duration_cast<nanoseconds>(end - start);
                    cout << "\nCzas wykonania operacji: " << duration.count() << " ns\n";
                    system("pause");
                }
            } while (wyborP1 != 0);
        }

        if(wybor == 2){
            do {
                system("cls");
                cout << "--- LISTA NIEPOSORTOWANA ---\n";
                cout << "1. Generuj losowe dane (" << quantity << ")\n";
                cout << "2. ExtractMax\n";
                cout << "3. Peek\n";
                cout << "4. Decrease_key\n";
                cout << "5. Increase_key\n";
                cout << "6. Wyswietl (Display)\n";
                cout << "7. Rozmiar (Return_size)\n";
                cout << "0. Powrot do menu glownego\n";
                cout << "Wybor: ";
                cin >> wyborP2;

                switch(wyborP2){
                    case 1: 
                        start = high_resolution_clock::now();
                        generujDane(pqa, quantity, gen); 
                        end = high_resolution_clock::now();
                        break;
                    case 2: 
                        start = high_resolution_clock::now();
                        pqa.extractMax();
                        end = high_resolution_clock::now();
                        break;
                    case 3: {
                        start = high_resolution_clock::now();
                        Element top = pqa.peek();
                        end = high_resolution_clock::now();
                        if(top.priority != -1) {
                            cout << "Element o najwyzszym priorytecie: [" << top.priority << ":" << top.value << "]" << endl;
                        } else {
                            cout << "Kolejka jest pusta!" << endl;
                        }
                        break;
                    }
                    case 4: 
                        cout << "Podaj wartosc i nowy priorytet: ";
                        cin >> v_man >> p_man;
                        start = high_resolution_clock::now();
                        pqa.decrease_key(v_man, p_man);
                        end = high_resolution_clock::now();
                        break;      
                    case 5: 
                        cout << "Podaj wartosc i nowy priorytet: ";
                        cin >> v_man >> p_man;
                        start = high_resolution_clock::now();
                        pqa.increase_key(v_man, p_man);
                        end = high_resolution_clock::now();
                        break;    
                    case 6: 
                        start = high_resolution_clock::now();
                        pqa.display();
                        end = high_resolution_clock::now();
                        break;
                    case 7: 
                        start = high_resolution_clock::now();
                        pqa.return_size();
                        cout << "Aktualny rozmiar struktury: " << pqa.return_size() << endl;
                        end = high_resolution_clock::now();
                        system("pause");
                        break;
                }
                if (wyborP2 != 0 && wyborP2 != 7) {
                    auto duration = duration_cast<nanoseconds>(end - start);
                    cout << "\nCzas wykonania operacji: " << duration.count() << " ns\n";
                    system("pause");
                }
            } while (wyborP2 != 0);
        }

        if (wybor == 3){
            ofstream clearFile("wyniki.txt");
            clearFile << "Struktura;Rozmiar;Operacja;Czas_ns\n";
            clearFile.close();
            
            runResearch<Heap>("wyniki.txt", "Kopiec");
            runResearch<PriorityQueueArray>("wyniki.txt", "Tablica_Nieposortowana");

            cout << "Wszystkie pomiary zakonczone!" << endl;
            break;
        }
    } while (wybor != 0);  
    return 0;
}