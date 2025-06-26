#ifndef FUNKCJE_HPP
#define FUNKCJE_HPP

#include<iostream>
#include <windows.h>
#include <windowsx.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
#include <queue>
#include <cstring>


extern int polozenie_x, polozenie_y, dx, dy, start_x, start_y;
extern int styk_x, styk_y;
extern int typ_blokow;
extern bool chwyt, wywolaj_wieze, puszczony;

struct bloki {
    int poz_x;
    int poz_y;
    int h;
    bool podniesiony;
};

extern bloki blok[6];




struct Wieza {
    int stan;
    int index;
    int cel;
    int h;
    int kierunek;
    bool aktywna = false;
};

extern Wieza wieza;

struct Sort {
    int stan;
    int index;
    int zakres;
    int h1;
    int h2;
    int kierunek;
    int typ_sortu;
    bool aktywny = false;
};

extern Sort sort;

void aktualizujSort();

void DrawScene(Gdiplus::Graphics& g);
void inicjalizuj_bloki ();
void inicjalizuj_sort ();
void rysuj_kwadraty(Gdiplus::Graphics& g, Gdiplus::SolidBrush& brush);
void rysuj_trojkaty(Gdiplus::Graphics& g, Gdiplus::SolidBrush& brush);
void rysuj_prostokaty(Gdiplus::Graphics& g, Gdiplus::SolidBrush& brush);
void rysuj_kola(Gdiplus::Graphics& g, Gdiplus::SolidBrush& brush);
void rysuj_sort(Gdiplus::Graphics& g, Gdiplus::SolidBrush& brush);
void aktualizujWieza();



#endif