# Struktury_Danych

# 🚀 Analiza Wydajności Struktur Danych – Miniprojekt 1

Repozytorium zawiera implementację oraz badania wydajnościowe trzech podstawowych struktur danych w języku C++. Celem projektu było porównanie rzeczywistych czasów operacji z ich złożonością teoretyczną.

## 📋 Spis treści
- [Obsługiwane struktury](#-obsługiwane-struktury)
- [Funkcje programu (Hub Projektowy)](#-funkcje-programu-hub-projektowy)
- [Automatyczne badania wydajnościowe](#-automatyczne-badania-wydajnościowe)
- [Metodologia badań](#-metodologia-badań)
- [Środowisko testowe](#-środowisko-testowe)
- [Instrukcja uruchomienia](#-instrukcja-uruchomienia)

## 🏗️ Obsługiwane struktury
Projekt obejmuje pełną implementację następujących struktur:
1. **Tablica Dynamiczna (Dynamic Array)** – oparta na ciągłej alokacji pamięci z mechanizmem reallokacji (powiększanie rozmiaru x2).
2. **Lista Jednokierunkowa (Singly Linked List)** – wykorzystująca wskaźniki `head` oraz `tail` dla optymalizacji dostępu do obu końców.
3. **Lista Dwukierunkowa (Doubly Linked List)** – rozszerzona o wskaźnik `prev`, umożliwiający efektywne usuwanie z końca i poruszanie się w obu kierunkach.

## 🎮 Funkcje programu (Hub Projektowy)
Po uruchomieniu programu użytkownik trafia do **Hubu Projektowego**, który pozwala na:
* **Interaktywne testowanie**: Wybór konkretnej struktury i ręczne wywoływanie metod (dodawanie, usuwanie, wyszukiwanie) wraz z natychmiastowym pomiarem czasu wykonania w nanosekundach.
* **Generowanie danych**: Szybkie wypełnienie wybranej struktury losowymi wartościami z zakresu 0-9999.
* **Automatyzację**: Uruchomienie pełnego cyklu badawczego dla wszystkich struktur jednocześnie.

## 🧪 Automatyczne badania wydajnościowe
Funkcja "Automatyczne Badania" (opcja 4 w menu) wykonuje kompleksowe pomiary dla wszystkich metod:
* **Operacje**: `addFront`, `addEnd`, `addAt`, `removeFront`, `removeEnd`, `removeAt` oraz `find`.
* **Zapis wyników**: Dane są zapisywane w formacie CSV do pliku `wyniki_wszystko.txt`, co ułatwia ich późniejszą analizę w Excelu.

## 📐 Metodologia badań
W celu zapewnienia rzetelności wyników, program stosuje rygorystyczną metodologię:
* **Rozmiary struktur (N)**: Pomiary są wykonywane dla 8 różnych wielkości: 5000, 10000, 20000, 40000, 60000, 80000, 100000 oraz 120000 elementów.
* **Uśrednianie wyników**: Każdy pomiar dla danego rozmiaru $N$ jest powtarzany **10-krotnie** przy użyciu różnych ziarn losowania (seedów).
* **Wykorzystane seedy**: 1670, 42, 123, 2024, 67, 888, 55, 99, 1010, 11.
* **Precyzja**: Czas mierzony jest przy użyciu `std::chrono::high_resolution_clock` z dokładnością do nanosekund.

## 💻 Środowisko testowe
Pomiary zawarte w raporcie zostały przeprowadzone na następującej konfiguracji:
* **Procesor**: AMD Ryzen 5 7535HS (3300MHz)
* **Pamięć RAM**: 32 GB DDR5-5600
* **System**: Windows 11 Home
* **Kompilator**: Visual Studio Code (GCC/MinGW)

## 🚀 Instrukcja uruchomienia
1. Sklonuj repozytorium i przejdź na branch `project1`.
2. Skompiluj projekt (np. używając g++):
   ```bash
   g++ main.cpp -o program.exe
3. Uruchom projekt komendą:

  PowerShell: 
   ```.\program.exe```
   
  MacOs/Linux:
  ```chmod +x program.exe```
   ```./program.exe```
