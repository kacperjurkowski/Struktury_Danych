# 🚀 Analiza Wydajności Kolejek Priorytetowych – Miniprojekt 2

Repozytorium zawiera własną implementację oraz kompleksowe badania wydajnościowe dwóch odmiennych wariantów kolejki priorytetowej w języku C++. Celem projektu było empiryczne zweryfikowanie średniego oraz pesymistycznego czasu operacji i zestawienie wyników z modelami teoretycznymi.

## 📋 Spis treści
- [Obsługiwane struktury](#-obsługiwane-struktury)
- [Funkcje programu (Hub Projektowy)](#-funkcje-programu-hub-projektowy)
- [Automatyczne badania wydajnościowe](#-automatyczne-badania-wydajnościowe)
- [Metodologia badań](#-metodologia-badań)
- [Strategia obsługi duplikatów priorytetów (FIFO)](#-strategia-obsługi-duplikatów-priorytetów-fifo)
- [Środowisko testowe](#-środowisko-testowe)
- [Instrukcja uruchomienia](#-instrukcja-uruchomienia)

## 🏗️ Obsługiwane struktury
Projekt obejmuje niskopoziomową, pełną implementację kolejki priorytetowej opartej na:
1. **Kopcu Binarnym typu MAX (Binary Heap)** – struktura drzewiasta mapowana sekwencyjnie wewnątrz dynamicznej tablicy kontenerowej, gdzie priorytet rodzica jest zawsze większy bądź równy priorytetom jego synów.
2. **Tablicy Nieposortowanej (Unsorted Array)** – sekwencyjny kontener dynamiczny, w którym elementy dopisywane są bezwarunkowo na koniec struktury, a element maksymalny wyszukiwany jest dopiero w momencie wywołania.

## 🎮 Funkcje programu (Hub Projektowy)
Po uruchomieniu programu użytkownik trafia do **Hubu Projektowego**, który pozwala na:
* **Interaktywne testowanie**: Wybór konkretnej struktury i ręczne wywoływanie metod (`insert`, `extractMax`, `peek`, `decrease_key`, `increase_key`, `return_size`) wraz z natychmiastowym pomiarem czasu wykonania w nanosekundach.
* **Generowanie danych**: Wypełnienie wybranego kontenera losowymi wartościami z automatycznym zachowaniem warunków brzegowych eksperymentu.
* **Automatyzację**: Uruchomienie pełnego, bezobsługowego cyklu badawczego dla obu struktur jednocześnie.

## 🧪 Automatyczne badania wydajnościowe
Funkcja "Automatyczne Badania" (opcja 3 w menu głównym) wykonuje seryjne pomiary dla wszystkich metod modyfikujących i dostępnych:
* **Zapis wyników**: Dane po zakończeniu serii są automatycznie formatowane i zapisywane sekwencyjnie (format CSV) do pliku `wyniki.txt`, co umożliwia bezpośredni import do arkuszy kalkulacyjnych lub skryptów rysujących wykresy (np. pgfplots w LaTeX).

## 📐 Metodologia badań
W celu zapewnienia pełnej czystości metodologicznej i eliminacji anomalii pomiarowych zastosowano rygorystyczny reżim badawczy:
* **Rozmiary struktur (N)**: Pomiary są wykonywane dla 8 różnych wielkości danych: 5000, 10000, 20000, 40000, 60000, 80000, 100000 oraz 120000 elementów.
* **Sposób losowania**: Ziarno losowości sterowane jest przez zestaw **10 niezależnych seedów** (1670, 42, 123, 2024, 67, 888, 55, 99, 1010, 11) i generator `std::mt19937`.
* **Dystrybucja wartości i kluczy**: Wartości elementów ($v$) odpowiadają indeksowi pętli ($0$ do $N-1$), co gwarantuje obecność szukanego elementu w pamięci. Priorytety ($p$) losowane są z zakresu od $0$ do $N \cdot 10$, minimalizując statystyczne ryzyko kolizji.
* **Zasada zachowania stałego stanu**: Aby utrzymać bazowy rozmiar $N$ podczas testów automatycznych, po każdej operacji modyfikującej natychmiast wywoływana jest akcja równoważąca (odwrotna), np. `insert` $\rightarrow$ `extractMax`, `decrease_key` $\rightarrow$ `increase_key`.
* **Precyzja**: Czas zbierany jest z poziomu `std::chrono::high_resolution_clock` z rozdzielczością nanosekundową (`ns`).

## ⚖️ Strategia obsługi duplikatów priorytetów (FIFO)
W przypadku wystąpienia elementów posiadających identyczny priorytet program realizuje dwie różne strategie:
* **Tablica Nieposortowana (Naturalne FIFO)**: Z racji dopisywania elementów na koniec oraz implementacji wyszukiwania od początku tablicy z warunkiem ostro większym (`>`), przy remisie priorytetów zachowane jest ścisłe, bezkosztowe FIFO.
* **Kopiec Binarny (Niestabilność strukturalna)**: Ciągłe rotacje i zamiany węzłów (`std::swap`) w procedurach `heapify_up` oraz `heapify_down` powodują utratę chronologii insercji. Struktura ta traktuje równe priorytety czysto relacyjnie (brak zachowania zasady FIFO).

## 💻 Środowisko testowe
Pomiary zawarte w raporcie zostały przeprowadzone na następującej konfiguracji:
* **Procesor**: AMD Ryzen 5 7535HS (3300MHz)
* **Pamięć RAM**: 32 GB (2 x 16 GB) GoodRam DDR5-5600 CL46
* **System operacyjny**: Windows 11 Home
* **Kompilator**: Visual Studio Code (GCC/MinGW)

## 🚀 Instrukcja uruchomienia
1. Sklonuj repozytorium i przejdź na branch `project2`.
2. Skompiluj projekt (wszystkie powiązane pliki źródłowe):
   ```bash
   g++ main.cpp dynamic_array.cpp PriorityQueueArray.cpp heap.cpp -o program.exe
