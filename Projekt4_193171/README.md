# Symulacja 2D ramienia robota 

## Autor
**Imię i nazwisko:** Karol Symonowicz
**nr indeksu** 193171  
**Data oodania:** 26 czerwca 2025  
**Środowisko:** Visual Studio Code, CMake, GDI+, WindowsAPI

---

## 1. Cel projektu

Celem projektu było stworzenie symulatora ramienia robota 2D z możliwością sterowania w czasie rzeczywistym. Program miał umożliwiać:
- wizualizację ramienia w oknie graficznym,
- zmianę parametrów (np. długości i kąty segmentów),
- interaktywną kontrolę i renderowanie przy pomocy GDI+.

---

## 2. Wykorzystane technologie

- **Język programowania:** C++
- **Biblioteka graficzna:** GDI+ (Windows API)
- **System budowania:** CMake
- **IDE:** Visual Studio Code

## 3. Funkcjonalności programu

- **sterowanie manualne:** Program umożliwia manualne sterowanie ramieniem, poprzez panel po lewej można ustawiać pozycję końcówki robota
- **manipulacja obiektami** Program umożliwia przenoszenie bloków oraz układanie ich na sobie, używając 
przycisku "CHWYT" w panelu. na dole okna można wybrać 1 z 4 kształtów obiektów (kwadrat, trójkąt, prostokąt, koło)
- **wbudowane programy** Program umożliwia uruchomienie 3 programów: układanie wieży z obiektów oraz sortowanie
obiektów rosnąco lub malejąco 

## 4. Działanie projektu
- przy zmianie pozycji końcówki robota program na bieżąco oblicza położenie poszczególnych segmentów,
umożliwiających osiągnięcie żądanej pozycji przy pomocy wzorów na kinematykę prostą manipulatora płaskiego
- przy złapaniu obiektów przez końcówkę manipulatora
- wbudowane programy zostały zaprogramowane jako "maszyny sekwencyjne", kliknięcie odpowiednich przycisków
uruchamia stan 0, a następnie zgodnie z przyjętą logiką przeprowadza program przez wszystkie stany
- przy sortowaniu użyto sortowanie bąbelkowego



