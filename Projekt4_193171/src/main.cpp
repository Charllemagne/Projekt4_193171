
#include "funkcje.hpp"

HWND hwndButton;
HWND hwndButton2;
HWND hwndButton3;
HWND hwndButton4;
HWND hwndButton5;
HWND hwndButton6;
HWND hwndButton7;
HWND hwndButton8;
HWND hwndButton9;
HWND hwndButton10;
HWND hwndButton11;
HWND hwndButton12;
HWND hwndButton13;
HWND hwndButton14;
HWND hwndButton15;
HWND hwndButton16;
bool lewo, prawo, gora, dol;
bool wywolaj_wieze = false;
bool puszczony = false;
int pr=2; //predkosc chwytaka



using namespace Gdiplus;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ULONG_PTR gdiplusToken;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MainWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        "Symulacja 2D ramienia robota",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr);

    if (!hwnd)
        return -1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    
    switch (msg)
    {
        case WM_CREATE:
        {
            hwndButton = CreateWindow(
            "BUTTON", "W",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
            130, 200, 50, 50,
            hwnd, (HMENU)1,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton2 = CreateWindow(
            "BUTTON", "S",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
            130, 300, 50, 50,
            hwnd, (HMENU)2,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton3 = CreateWindow(
            "BUTTON", "A",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
            80, 250, 50, 50,
            hwnd, (HMENU)3,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton4 = CreateWindow(
            "BUTTON", "D",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
            180, 250, 50, 50,
            hwnd, (HMENU)4,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton5 = CreateWindow(
            "BUTTON", "START",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            55, 125, 80, 50,
            hwnd, (HMENU)5,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton6 = CreateWindow(
            "BUTTON", "CHWYT",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            175, 125, 80, 50,
            hwnd, (HMENU)6,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton7 = CreateWindow(
            "BUTTON", "WOLNO",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            25, 370, 70, 50,
            hwnd, (HMENU)7,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton8 = CreateWindow(
            "BUTTON", "SREDNIO",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            120, 370, 70, 50,
            hwnd, (HMENU)8,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton9 = CreateWindow(
            "BUTTON", "SZYBKO",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            215, 370, 70, 50,
            hwnd, (HMENU)9,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton10 = CreateWindow(
            "BUTTON", "KWADRATY",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            25, 550, 100, 50,
            hwnd, (HMENU)10,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton11 = CreateWindow(
            "BUTTON", "TROJKATY",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            150, 550, 100, 50,
            hwnd, (HMENU)11,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton12 = CreateWindow(
            "BUTTON", "PROSTOKATY",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            275, 550, 100, 50,
            hwnd, (HMENU)12,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton13 = CreateWindow(
            "BUTTON", "KOLA",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            400, 550, 100, 50,
            hwnd, (HMENU)13,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            hwndButton14 = CreateWindow(
            "BUTTON", "BUDUJ_WIEZE",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            600, 550, 130, 50,
            hwnd, (HMENU)14,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

             hwndButton15 = CreateWindow(
            "BUTTON", "SORT_ROSNACO",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            800, 550, 130, 50,
            hwnd, (HMENU)15,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

             hwndButton16 = CreateWindow(
            "BUTTON", "SORT_MALEJACO",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1000, 550, 130, 50,
            hwnd, (HMENU)16,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
            );

            SetTimer(hwnd,1,100,NULL);
            inicjalizuj_bloki ();
            return 0;

            
        }   
    
        case WM_COMMAND:
        {       
            switch (LOWORD(wParam)) {
                case 1: // W
                    gora = true;
                    break;
                case 2: // S
                    dol = true;
                    break;
                case 3: // A
                    lewo = true;
                    break;
                case 4: // D
                    prawo = true;
                    break;
                case 6:       
                    chwyt = true;
                    break;
                case 7:
                    pr = 2;
                    break;
                case 8:
                    pr = 6;
                    break;
                case 9:
                    pr = 10;
                    break;
                case 10:
                    typ_blokow = 1;
                    break;
                case 11:
                    typ_blokow = 2;
                    break;
                case 12:
                    typ_blokow = 3;
                    break;
                case 13:
                {
                    typ_blokow = 4;
                    break;
                }
                case 14:
                {
                    wieza.aktywna = true;
                    wieza.stan = 0;
                    break;
                }
                case 15:
                {
                    inicjalizuj_sort();
                    sort.aktywny = true;
                    sort.stan = 0;
                    sort.typ_sortu = 1;
                    break;
                }
                case 16:
                {
                    inicjalizuj_sort();
                    sort.aktywny = true;
                    sort.typ_sortu = -1;
                    sort.stan = 0;
                    
                    break;
                }

            }
            return 0;
        }
  
         case WM_TIMER:
        {
            dx = dy = 0;

            if ((lewo = (SendMessage(hwndButton3, BM_GETCHECK, 0, 0) == BST_CHECKED))) dx = -pr;
            if ((prawo = (SendMessage(hwndButton4, BM_GETCHECK, 0, 0) == BST_CHECKED))) dx = pr;
            if ((gora = (SendMessage(hwndButton, BM_GETCHECK, 0, 0) == BST_CHECKED))) dy = -pr;
            if ((dol = (SendMessage(hwndButton2, BM_GETCHECK, 0, 0) == BST_CHECKED))) dy = pr;

            if (wieza.aktywna)
                aktualizujWieza(); // <<< tu dodajemy FSM
            else if (sort.aktywny)    
                aktualizujSort();

            if (lewo || prawo || gora || dol || wieza.aktywna || sort.aktywny)
            {
                puszczony = false;
                InvalidateRect(hwnd, NULL, TRUE);
            }
                
            
            return 0;
        }

       
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        Gdiplus::Graphics g(hdc);
        Gdiplus::FontFamily fontFamily(L"Arial");
        Gdiplus::Font font(&fontFamily, 18, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 0, 0)); // Czarny

        // Pozycja tekstu "MANUAL" (dopasuj do położenia przycisków)
        Gdiplus::PointF pos(220, 515);
        g.DrawString(L"MANUAL", -1, &font, pos, &brush);

        Gdiplus::PointF pos2(800, 515);
        g.DrawString(L"PRZYKLADY", -1, &font, pos2, &brush);

       
        DrawScene(g);  

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}