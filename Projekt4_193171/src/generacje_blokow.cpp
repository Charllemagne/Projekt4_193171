#include "funkcje.hpp"

double punkt_kolizji (int& xa, int& ya, int& xb, int& yb, int& x)
{
    double kol = (yb-ya)/(xb-xa)*(x-xa)+ya;
    return kol;
}

void rysuj_kwadraty(Gdiplus::Graphics& g, Gdiplus::SolidBrush& brush)
{
    bool kolizja = false;

    for (int i=0; i<6; i++)
    {
        if (blok[i].podniesiony == true) { //jeśli podniesiony to pozycja zmienia się zgodnie z chwytakiem
            blok[i].poz_x += dx;
            blok[i].poz_y += dy;
        }

        else {
            if (blok[i].poz_y == 100)   //jeśli na ziemi to nie zmienia pozycji
                kolizja = true;
            else
                for (int j=0; j<6; j++)
                    if (i==j)
                        continue;
                    else if (blok[i].poz_y+50 == blok[j].poz_y) {   //jeśli na innym bloku to nie zmienia pozycji
                        kolizja = true;
                        break;
                    }
                            
            while (kolizja == false)    //spada, póki nie napotka ziemi lub innego bloku
            {
                blok[i].poz_y += 2;

                if (blok[i].poz_y == 100)
                    kolizja = true;
                else
                    for (int j=0; j<6; j++)
                        if (i==j)
                            continue;
                        else if ((blok[i].poz_y+50 == blok[j].poz_y) && (blok[i].poz_x >= blok[j].poz_x)&& (blok[i].poz_x <= blok[j].poz_x+50)) {
                            kolizja = true;
                            break; }

                        else if ((blok[i].poz_y+50 == blok[j].poz_y) && (blok[i].poz_x+50 >= blok[j].poz_x)&& (blok[i].poz_x+50 <= blok[j].poz_x+50)) {
                            kolizja = true;
                            break; }
                        
            }
            kolizja = false;
        }   
            
        

        Gdiplus::Point kwadrat[4] = 
        {
            Gdiplus::Point(blok[i].poz_x, blok[i].poz_y),
            Gdiplus::Point(blok[i].poz_x+50, blok[i].poz_y),
            Gdiplus::Point(blok[i].poz_x+50, blok[i].poz_y+50),
            Gdiplus::Point(blok[i].poz_x, blok[i].poz_y+50),
        };
        g.FillPolygon(&brush, kwadrat, 4);
    };

    if (chwyt == true)
    {
        for (int i = 0; i < 6; i++) {
            if (styk_y > blok[i].poz_y && styk_x > blok[i].poz_x && styk_x < blok[i].poz_x + 50){
                blok[i].podniesiony = !blok[i].podniesiony;
                puszczony = true;
                break; }
        }
    chwyt = false; // dezaktywuj, aby nie powtarzać akcji
    }   
}

void rysuj_trojkaty(Gdiplus::Graphics& g, Gdiplus::SolidBrush& brush)
{
    bool kolizja = false;

    for (int i=0; i<6; i++)
    {
        if (blok[i].podniesiony == true) { //jeśli podniesiony to pozycja zmienia się zgodnie z chwytakiem
            blok[i].poz_x += dx;
            blok[i].poz_y += dy;
        }

        else {
            kolizja = false;
            if (blok[i].poz_y == 100)   //jeśli na ziemi to nie zmienia pozycji
                kolizja = true;
            else
                for (int j=0; j<6; j++)
                    if (i==j)
                        continue;
                    //kolizja dolna
                    else if ((blok[j].poz_x>=blok[i].poz_x-25) && (blok[j].poz_x<=blok[i].poz_x+25) && (blok[i].poz_y+50 == blok[j].poz_y)) {   //jeśli na innym bloku to nie zmienia pozycji
                        kolizja = true;
                        break;
                    }
                    //kolizja boczna prawa
                    else if ((blok[i].poz_x+25<blok[j].poz_x) && (blok[i].poz_x+25>blok[j].poz_x-25)) {
                        int xa=blok[j].poz_x-25, ya=blok[j].poz_y+50, xb=blok[j].poz_x, yb=blok[j].poz_y, x=blok[i].poz_x+25;
                        double p = punkt_kolizji(xa,ya,xb,yb,x);

                        if (blok[i].poz_y+50 >= p) {
                            kolizja = true;
                            break;
                        }

                    }
                    //kolizja boczna lewa
                    else if ((blok[i].poz_x-25>blok[j].poz_x) && (blok[i].poz_x-25<blok[j].poz_x+25)) {
                        int xa=blok[j].poz_x+25, ya=blok[j].poz_y+50, xb=blok[j].poz_x, yb=blok[j].poz_y, x=blok[i].poz_x-25;
                        double p = punkt_kolizji(xa,ya,xb,yb,x);

                        if (blok[i].poz_y+50 >= p) {
                            kolizja = true;
                            break;
                        }

                    }

                            
            while (kolizja == false)    //spada, póki nie napotka ziemi lub innego bloku
            {
                blok[i].poz_y += 2;

                if (blok[i].poz_y == 100)
                    kolizja = true;
                else
                    for (int j=0; j<6; j++)
                    if (i==j)
                        continue;
                    else if ((blok[j].poz_x>=blok[i].poz_x-25) && (blok[j].poz_x<=blok[i].poz_x+25) && (blok[i].poz_y+50 == blok[j].poz_y)) {   //jeśli na innym bloku to nie zmienia pozycji
                        kolizja = true;
                        break;
                    }
                    else if ((blok[i].poz_x+25<blok[j].poz_x) && (blok[i].poz_x+25>=blok[j].poz_x-25)) {
                        int xa=blok[j].poz_x-25, ya=blok[j].poz_y+50, xb=blok[j].poz_x, yb=blok[j].poz_y, x=blok[i].poz_x+25;
                        double p = punkt_kolizji(xa,ya,xb,yb,x);

                        if (blok[i].poz_y+50 <= p) {
                            kolizja = true;
                            break;
                        }

                    }
                    else if ((blok[i].poz_x-25>blok[j].poz_x) && (blok[i].poz_x-25<=blok[j].poz_x+25)) {
                        int xa=blok[j].poz_x+25, ya=blok[j].poz_y+50, xb=blok[j].poz_x, yb=blok[j].poz_y, x=blok[i].poz_x-25;
                        double p = punkt_kolizji(xa,ya,xb,yb,x);

                        if (blok[i].poz_y+50 <= p) {
                            kolizja = true;
                            break;
                        }

                    }
                        
            }
            kolizja = false;
        }   
            
        

        Gdiplus::Point trojkat[3] = 
        {
            Gdiplus::Point(blok[i].poz_x, blok[i].poz_y),
            Gdiplus::Point(blok[i].poz_x+25, blok[i].poz_y+50),
            Gdiplus::Point(blok[i].poz_x-25, blok[i].poz_y+50)
        };
        g.FillPolygon(&brush, trojkat, 3);
    };

    if (chwyt == true)
    {
        for (int i = 0; i < 6; i++) {
            if (styk_y > blok[i].poz_y && styk_x > blok[i].poz_x-25 && styk_x < blok[i].poz_x + 25){
                blok[i].podniesiony = !blok[i].podniesiony;
                puszczony = true;
                break; }
        }
    chwyt = false; // dezaktywuj, aby nie powtarzać akcji
    }   
}

void rysuj_prostokaty(Gdiplus::Graphics& g, Gdiplus::SolidBrush& brush)
{
    bool kolizja = false;

    for (int i=0; i<6; i++)
    {
        if (blok[i].podniesiony == true) { //jeśli podniesiony to pozycja zmienia się zgodnie z chwytakiem
            blok[i].poz_x += dx;
            blok[i].poz_y += dy;
        }

        else {
            if (blok[i].poz_y == 100)   //jeśli na ziemi to nie zmienia pozycji
                kolizja = true;
            else
                for (int j=0; j<6; j++)
                    if (i==j)
                        continue;
                    else if (blok[i].poz_y+50 == blok[j].poz_y) {   //jeśli na innym bloku to nie zmienia pozycji
                        kolizja = true;
                        break;
                    }
                            
            while (kolizja == false)    //spada, póki nie napotka ziemi lub innego bloku
            {
                blok[i].poz_y += 2;

                if (blok[i].poz_y == 100)
                    kolizja = true;
                else
                    for (int j=0; j<6; j++)
                        if (i==j)
                            continue;
                        else if ((blok[i].poz_y+50 == blok[j].poz_y) && (blok[i].poz_x >= blok[j].poz_x)&& (blok[i].poz_x <= blok[j].poz_x+50)) {
                            kolizja = true;
                            break; }

                        else if ((blok[i].poz_y+50 == blok[j].poz_y) && (blok[i].poz_x+80 >= blok[j].poz_x)&& (blok[i].poz_x+80 <= blok[j].poz_x+80)) {
                            kolizja = true;
                            break; }
                        
            }
            kolizja = false;
        }   
            
        

        Gdiplus::Point prostokat[4] = 
        {
            Gdiplus::Point(blok[i].poz_x, blok[i].poz_y),
            Gdiplus::Point(blok[i].poz_x+80, blok[i].poz_y),
            Gdiplus::Point(blok[i].poz_x+80, blok[i].poz_y+50),
            Gdiplus::Point(blok[i].poz_x, blok[i].poz_y+50),
        };
        g.FillPolygon(&brush, prostokat, 4);
    };

    if (chwyt == true)
    {
        for (int i = 0; i < 6; i++) {
            if (styk_y > blok[i].poz_y && styk_x > blok[i].poz_x && styk_x < blok[i].poz_x + 80){
                blok[i].podniesiony = !blok[i].podniesiony;
                puszczony = true;
                break; }
        }
    chwyt = false; // dezaktywuj, aby nie powtarzać akcji
    }   
}

void rysuj_kola(Gdiplus::Graphics& g, Gdiplus::SolidBrush& brush)
{
    bool kolizja = false;

    for (int i = 0; i < 6; i++)
    {
        if (blok[i].podniesiony == true) {
            blok[i].poz_x += dx;
            blok[i].poz_y += dy;
        }
        else {
            if (blok[i].poz_y == 100)
                kolizja = true;
            else {
                for (int j = 0; j < 6; j++) {
                    if (i == j) continue;
                    else if (blok[i].poz_y + 50 == blok[j].poz_y) {
                        kolizja = true;
                        break;
                    }
                }
            }

            while (!kolizja)
            {
                blok[i].poz_y += 2;

                if (blok[i].poz_y == 100)
                    kolizja = true;
                else {
                    for (int j = 0; j < 6; j++) {
                        if (i == j) continue;

                        bool warunek1 = (blok[i].poz_y + 50 == blok[j].poz_y) &&
                                        (blok[i].poz_x >= blok[j].poz_x) &&
                                        (blok[i].poz_x <= blok[j].poz_x + 50);

                        bool warunek2 = (blok[i].poz_y + 50 == blok[j].poz_y) &&
                                        (blok[i].poz_x + 50 >= blok[j].poz_x) &&
                                        (blok[i].poz_x + 50 <= blok[j].poz_x + 50);

                        if (warunek1 || warunek2) {
                            kolizja = true;
                            break;
                        }
                    }
                }
            }

            kolizja = false;
        }

        // Rysowanie KOŁA o średnicy 50
        g.FillEllipse(&brush, blok[i].poz_x, blok[i].poz_y, 50, 50);
    }

    // ----------------------------
    // Warunek chwytania (dla kół)
    // ----------------------------
    if (chwyt == true)
    {
        for (int i = 0; i < 6; i++) {
            int srodek_x = blok[i].poz_x + 25;
            int srodek_y = blok[i].poz_y + 25;
            int dx = styk_x - srodek_x;
            int dy = styk_y - srodek_y;

            if ((dx * dx + dy * dy) <= 625) { // promień 25, 25^2 = 625
                blok[i].podniesiony = !blok[i].podniesiony;
                puszczony = true;
                break;
            }
        }

        chwyt = false;
    }
}

void rysuj_sort(Gdiplus::Graphics& g, Gdiplus::SolidBrush& brush)
{
    bool kolizja = false;

    for (int i=0; i<6; i++)
    {
        if (blok[i].podniesiony == true) { //jeśli podniesiony to pozycja zmienia się zgodnie z chwytakiem
            blok[i].poz_x += dx;
            blok[i].poz_y += dy;
        }

        else {
            if (blok[i].poz_y == 150)   //jeśli na ziemi to nie zmienia pozycji
                kolizja = true;
            else
                for (int j=0; j<6; j++)
                    if (i==j)
                        continue;
                    else if (blok[i].poz_y == blok[j].poz_y-blok[j].h) {   //jeśli na innym bloku to nie zmienia pozycji
                        kolizja = true;
                        break;
                    }
                            
            while (kolizja == false)    //spada, póki nie napotka ziemi lub innego bloku
            {
                blok[i].poz_y += 2;

                if (blok[i].poz_y == 150)
                    kolizja = true;
                else
                    for (int j=0; j<6; j++)
                        if (i==j)
                            continue;
                        else if ((blok[i].poz_y == blok[j].poz_y-blok[j].h) && (blok[i].poz_x >= blok[j].poz_x)&& (blok[i].poz_x <= blok[j].poz_x+50)) {
                            kolizja = true;
                            break; }

                        else if ((blok[i].poz_y == blok[j].poz_y-blok[j].h) && (blok[i].poz_x+50 >= blok[j].poz_x)&& (blok[i].poz_x+50 <= blok[j].poz_x+50)) {
                            kolizja = true;
                            break; }
                        
            }
            kolizja = false;
        }   
            
        

        Gdiplus::Point kwadrat[4] = 
        {
            Gdiplus::Point(blok[i].poz_x, blok[i].poz_y),
            Gdiplus::Point(blok[i].poz_x+50, blok[i].poz_y),
            Gdiplus::Point(blok[i].poz_x+50, blok[i].poz_y-blok[i].h),
            Gdiplus::Point(blok[i].poz_x, blok[i].poz_y-blok[i].h),
        };
        g.FillPolygon(&brush, kwadrat, 4);
    };

    if (chwyt == true)
    {
        for (int i = 0; i < 6; i++) {
            if (styk_y > blok[i].poz_y-blok[i].h && styk_x > blok[i].poz_x && styk_x < blok[i].poz_x + 50){
                blok[i].podniesiony = !blok[i].podniesiony;
                break; }
        }
    chwyt = false; // dezaktywuj, aby nie powtarzać akcji
    }   
}