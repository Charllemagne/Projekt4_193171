#include "funkcje.hpp"
int start_x, start_y;
int polozenie_x = start_x = 350;
int polozenie_y = start_y = -240;
int dx = 0;
int dy = 0;
int styk_x = 0;
int styk_y = 0;
int typ_blokow = 1;
int obecne_bloki = 1;
bool chwyt=false;





bloki blok[6];


void DrawScene(Gdiplus::Graphics& g)
{
    
    using namespace Gdiplus;

    Pen pen(Gdiplus::Color(255, 0, 0, 0), 2); // czarna linia, grubość 2 piksele
    g.DrawLine(&pen, 0, 500, 2000, 500);
    g.DrawLine(&pen, 0, 5, 2000, 5);
    g.DrawLine(&pen, 0, 630, 2000, 630);
    g.DrawLine(&pen, 325, 5, 325, 500);
    g.DrawLine(&pen, 530, 500, 530, 630);

    

    Gdiplus::Point triangle[3] = {
        Gdiplus::Point(600, 350),
        Gdiplus::Point(625, 500),
        Gdiplus::Point(575, 500)
    };

    Gdiplus::SolidBrush brush(Gdiplus::Color(255, 87, 87, 87));
    g.FillPolygon(&brush, triangle, 3);
   

    g.TranslateTransform(600,350); //wierzchołek trójkąta

    int L1 = 330;
    int L2 = 350;

    polozenie_x = polozenie_x + dx;
    polozenie_y = polozenie_y + dy;

    int x=polozenie_x;
    int y=-polozenie_y;

  float D = (x * x + y * y - L1 * L1 - L2 * L2) / (2.0f * L1 * L2);
if (D < -1.0f || D > 1.0f) return; // zabezpieczenie
float theta2 = -acos(D);
float theta1 = atan2(y, x) - atan2(L2 * sin(theta2), L1 + L2 * cos(theta2));

    

    int x1 = L1*cos(theta1);
    int y1 = L1*sin(theta1);

    int x2 = x1 + L2*cos(theta1+theta2);
    int y2 = y1 + L2*sin(theta1+theta2);

    g.DrawLine(&pen, 0, 0, x1, -y1);
    g.DrawLine(&pen, x1, -y1, x2, -y2);
    
    Gdiplus::Point chwytak[3] = {
        Gdiplus::Point(x2, -y2),
        Gdiplus::Point(x2+30, -y2+30),
        Gdiplus::Point(x2-30, -y2+30)
    };
    g.FillPolygon(&brush, chwytak, 3);

    styk_x = x2;
    styk_y = -y2+40; 
    
    if (sort.aktywny)
        rysuj_sort(g,brush);
    else
    {
        if (typ_blokow != obecne_bloki){
            inicjalizuj_bloki();
            chwyt = false;
            obecne_bloki = typ_blokow;   
        }
        
        switch (typ_blokow) {
            case 1:
                rysuj_kwadraty(g,brush);
                break;
            case 2:
                rysuj_trojkaty(g,brush);
             break;
            case 3:
                rysuj_prostokaty(g,brush);
                break;
            case 4:
                rysuj_kola(g,brush);
                break;

    }
    }

    

    

    
    g.DrawLine(&pen, x2, -y2, x2, -y2+40);
    dx = 0;
    dy = 0;
    
}


void inicjalizuj_bloki () {
    blok [0] = {100,100,50,false};
    blok [1] = {190,100,100,false};
    blok [2] = {280,100,100,false};
    blok [3] = {370,100,100,false};
    blok [4] = {460,100,100,false};
    blok [5] = {550,100,100,false};
    polozenie_x = start_x;
    polozenie_y = start_y;
};

void inicjalizuj_sort () {
    blok [0] = {150,150,80,false};
    blok [1] = {240,150,100,false};
    blok [2] = {330,150,20,false};
    blok [3] = {420,150,80,false};
    blok [4] = {510,150,110,false};
    blok [5] = {600,150,50,false};
    polozenie_x = start_x;
    polozenie_y = start_y;
};
Wieza wieza;

void aktualizujWieza()
{
    if (!wieza.aktywna) return;

    switch (wieza.stan)
    {
        case 0: //inicjalizacja
        {
            inicjalizuj_bloki();
            wieza.h = 0;
            wieza.kierunek = 1;
            wieza.cel = 2;
            wieza.index = 6;
            wieza.stan = 1;
            break;
        }

        case 1: //zmiana indeksu przenoszonego bloku i sprawdzenie warunku końca
        {
            wieza.index--;
            if(wieza.index == wieza.cel)
                wieza.index--;

            wieza.stan = 2;

            if(wieza.index < 0)
                wieza.stan = 99;
            break;
        }

        case 2: // ruch poziomy do bloku
        {
            if(polozenie_x < blok[wieza.index].poz_x+25)
                wieza.kierunek = 1;
            else   
                wieza.kierunek = -1;

            dx = wieza.kierunek * 5;

            if (polozenie_x == blok[wieza.index].poz_x+25)
                {
                    dx = 0;
                    wieza.stan = 3;
                }

            break;
        }

        case 3: //opuszczenie chwytaka i chwyt bloku
        {
            dy = 5;

            if (styk_y >= blok[wieza.index].poz_y)
                {
                    blok[wieza.index].podniesiony = true;
                    wieza.stan = 4;
                }
            break;    
        }

        case 4: //podniesienie bloku
        {
            dy = -5;

            if (polozenie_y == start_y)
            {
                dy = 0;
                wieza.stan = 5;
            }
                

            break;
        }

        case 5: //przeniesienie bloku nad cel
        {
            if (blok[wieza.index].poz_x < blok[wieza.cel].poz_x)
                wieza.kierunek = 1;
            else
                wieza.kierunek = -1;

            dx = wieza.kierunek * 5;

            if (blok[wieza.index].poz_x == blok[wieza.cel].poz_x){
                dx = 0;
                wieza.stan = 6;
            }

            break;
        }

        case 6: // opuszczenie bloku
        {
            dy = 5;

            if (blok[wieza.index].poz_y+50 == blok[wieza.cel].poz_y - (50*wieza.h)  - 20)
            {
                dy = 0;
                blok[wieza.index].podniesiony = false;
                wieza.h++;
                wieza.stan = 7;
            }

            break;
        }

        case 7: //podniesienie chwytaka
        {
            dy = -5;

            if (polozenie_y == start_y) {
                dy = 0;
                wieza.stan = 1;
            }

            break;
        }

        case 99: // powrót do punktu startowego i koniec
        {
            polozenie_x = start_x;
            wieza.aktywna = false;
            break;
        }
    }
}

Sort sort;
int bufor_x = 60;
int droga = 0;
bloki bufor;

void aktualizujSort()
{
    if (!sort.aktywny) return;

    switch (sort.stan)
    {
        case 0: //inicjalizacja
        {
            inicjalizuj_sort();
            sort.kierunek = 1;
            sort.zakres = 5;
            sort.index = 0;
            sort.stan = 1;
            break;
        }

        case 1: //ruch w poziomie do bloku 1 (index = 0)
        {
            sort.index = 0;
            if(polozenie_x < blok[0].poz_x+25)
                sort.kierunek = 1;
            else
                sort.kierunek = -1;

            dx = sort.kierunek * 5;

            if(polozenie_x == blok[0].poz_x+25)
                {
                    dx=0;
                    sort.h1 = 370;
                    sort.stan = 2;
                }
            
            break;
        }

        case 2: //ruch w dół do bloku 1, sprawdzenie wysokości
        {
            if (styk_y != blok[0].poz_y-blok[0].h)
            {
                dy = 5;
                sort.h1 -= 5;
            }

            else
            {
                dy = 0;
                sort.stan = 3;
            }

            break;
        }

        case 3: //ruch w górę do pozycji startowej
        {
            dy = -5;

            if (polozenie_y == start_y)
            {
                dy = 0;
                sort.index++;
                sort.stan = 4;
            }

            break;
        }

        case 4: //ruch w poziomie do bloku 2 
        {
            if(polozenie_x < blok[sort.index].poz_x+25)
                sort.kierunek = 1;
            else
                sort.kierunek = -1;

            dx = sort.kierunek * 5;

            if(polozenie_x == blok[sort.index].poz_x+25)
                {
                    dx=0;
                    sort.h2 = 370;
                    sort.stan = 5;
                }
            
            break;
        }

        case 5: //ruch w dół do bloku 2, sprawdzenie wysokości
        {
                dy = 5;
                sort.h2 -= 5;
            

            if (styk_y >= blok[sort.index].poz_y-blok[sort.index].h)
            {
                dy = 0;
                sort.stan = 6;
            }

            break;
        }

        case 6: //porownanie wysokości, decyzja czy zamiana
        {
            int czy_wiekszy = 0;

            if(sort.h1 > sort.h2)
                czy_wiekszy = 1;

            else if (sort.h2 > sort.h1)
                czy_wiekszy = -1;

            int czy_zamiana = sort.typ_sortu * czy_wiekszy;

            if (czy_zamiana > 0)
                {
                    blok[sort.index].podniesiony = true;
                    sort.stan = 7;
                }
                
            else
                {
                    sort.h1 = sort.h2;
                    sort.stan = 18;
                }
            
            break;
        }

        case 7: //ruch w górę z zamienianym blokiem
        {
            dy = -5;

            if (polozenie_y == start_y)
            {
                dy = 0;
                sort.stan = 8;
            }

            break;
        }

        case 8: //ruch do bufora
        {
            if(polozenie_x < bufor_x)
                sort.kierunek = 1;
            else
                sort.kierunek = -1;

            dx = sort.kierunek * 5;

            if(polozenie_x == bufor_x)
                {
                    dx=0;
                    blok[sort.index].podniesiony=false;
                    sort.stan = 9;
                }
            
            break;
        }

        case 9: //ruch do drugiego bloku
        {
            if(polozenie_x < blok[sort.index-1].poz_x+25)
                sort.kierunek = 1;
            else
                sort.kierunek = -1;

            dx = sort.kierunek * 5;

            if(polozenie_x == blok[sort.index-1].poz_x+25)
                {
                    dx=0;
                    sort.stan = 10;
                }
            
            break;
        }
        case 10: //ruch w dół do drugiego bloku
        {
            if (styk_y != blok[sort.index-1].poz_y-blok[sort.index-1].h)
            {
                dy = 5;
            }

            else
            {
                dy = 0;
                blok[sort.index-1].podniesiony=true;
                sort.stan = 11;
            }

            break;
        }

        case 11: //ruch w górę z zamienianym blokiem
        {
            dy = -5;

            if (polozenie_y == start_y)
            {
                dy = 0;
                sort.stan = 12;
            }

            break;
        }

        case 12: //ruch w bok z drugim blokiem
        {
            dx = 5;
            if (droga == 90)
                {
                    dx=0;
                    droga=0;
                    blok[sort.index-1].podniesiony = false;
                    sort.stan = 13;
                }    
            droga += 5;
            break;
        }

            
        

        case 13: //ruch do bufora
        {
            if(polozenie_x < bufor_x)
                sort.kierunek = 1;
            else
                sort.kierunek = -1;

            dx = sort.kierunek * 5;

            if(polozenie_x == bufor_x)
                {
                    dx=0;
                    sort.stan = 14;
                }
            break;
        }

        case 14: //ruch w dół po blok w buforze
        {
            if (styk_y != blok[sort.index].poz_y-blok[sort.index].h)
            {
                dy = 5;
            }

            else
            {
                dy = 0;
                blok[sort.index].podniesiony=true;
                sort.stan = 15;
            }

            break;
        }

        case 15: //ruch w górę z zblokiem z bufora
        {
            dy = -5;

            if (polozenie_y == start_y)
            {
                dy = 0;
                sort.stan = 16;
            }

            break;
        }

        case 16: //ruch w poziomie z blokiem z bufora
        {
            if(blok[sort.index].poz_x < blok[sort.index-1].poz_x)
                sort.kierunek = 1;
            else
                sort.kierunek = -1;

            dx = sort.kierunek * 5;

            if(blok[sort.index].poz_x == blok[sort.index-1].poz_x-90)
                {
                    dx=0;
                    blok[sort.index].podniesiony = false;
                    sort.stan = 17;
                }
            
            break;
        }

        case 17: //zamiana indeksow zamienianych blokow
        {
            bufor.poz_x = blok[sort.index].poz_x;
            bufor.poz_y = blok[sort.index].poz_y;
            bufor.h = blok[sort.index].h;

            blok[sort.index].poz_x = blok[sort.index-1].poz_x;
            blok[sort.index].poz_y = blok[sort.index-1].poz_y;
            blok[sort.index].h = blok[sort.index-1].h;

            blok[sort.index-1].poz_x = bufor.poz_x;
            blok[sort.index-1].poz_y = bufor.poz_y;
            blok[sort.index-1].h = bufor.h;

            sort.h1 = blok[sort.index-1].h;


            sort.stan = 18;

            break;
        }

         case 18: //ruch w górę do pozycji startowej
        {
            dy = -5;

            if (polozenie_y == start_y)
            {
                dy = 0;
                sort.stan = 19;
            }

            break;
        }


        case 19:
        {

            if (sort.index==sort.zakres)
                {
                    sort.zakres--;
                    if (sort.zakres < 1)
                        sort.stan = 99;
                    else
                        sort.stan = 1;
                }
            else 
                sort.stan = 3;

            break;
        }

       

        case 99:
        {
            polozenie_x = start_x;
            sort.aktywny = false;
            break;
        }
    }
}

