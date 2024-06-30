#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std;

class Menu
{
public:
    int liczebnosc_tablicy = 0;
    string skad_dane;
    string nazwa_pliku;
    int *tablica_int = nullptr;
    float *tablica_float = nullptr;
    string typ_danych;

    int Jak_duzo()
    {
        cout << "Prosze podac ilosc danych: ";
        cin >> liczebnosc_tablicy;
        return liczebnosc_tablicy;
    }

    void Tworzenie_tablicy_int()
    {
        tablica_int = new int[liczebnosc_tablicy];
    }

    void Zapelnianie_tablicy_int()
    {
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            tablica_int[i] = (rand() % liczebnosc_tablicy);
        }
    }

    void Tworzenie_tablicy_float()
    {
        tablica_float = new float[liczebnosc_tablicy];
    }

    void Zapelnienie_tablicy_float()
    {
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            tablica_float[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / liczebnosc_tablicy);
        }
    }

    void Wypisywanie_tablicy_int()
    {
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            cout << tablica_int[i] << " ";
        }
    }

    void Wypisywanie_tablicy_float()
    {
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            cout << tablica_float[i] << " ";
        }
    }

    void menu()
    {
        bool poprawny_typ = false;
        bool poprawne_skad_dane = false;
        ifstream plik;

        do
        {
            cout << "Prosze wybrac typ danych (int lub float): ";
            cin >> typ_danych;
            if (typ_danych == "int" || typ_danych == "float")
            {
                poprawny_typ = true;
            }
            else
            {
                poprawny_typ = false;
            }
        } while (poprawny_typ == false);

        do
        {
            cout << "Prosze wybrac czy dane maja byc wygenerowane losowo czy pobrane z pliku txt (g lub p): ";
            cin >> skad_dane;
            if (skad_dane == "g" && typ_danych == "int")
            {
                Jak_duzo();
                cout << "Dane do posortowania: ";
                Tworzenie_tablicy_int();
                Zapelnianie_tablicy_int();
                Wypisywanie_tablicy_int();
                poprawne_skad_dane = true;
            }
            else if (skad_dane == "g" && typ_danych == "float")
            {
                Jak_duzo();
                cout << "Dane do posortowania: ";
                Tworzenie_tablicy_float();
                Zapelnienie_tablicy_float();
                Wypisywanie_tablicy_float();
                poprawne_skad_dane = true;
            }
            else if (skad_dane == "p" && typ_danych == "int")
            {
                Podaj_nazwe_pliku();
                Odczyt_wielkosci_pliku(nazwa_pliku, plik);
                Tworzenie_tablicy_int();
                Odczyt_z_pliku_do_tablicy_int(liczebnosc_tablicy, plik);
                cout << "Dane do posortowania: ";
                Wypisywanie_tablicy_int();
                poprawne_skad_dane = true;
            }
            else if (skad_dane == "p" && typ_danych == "float")
            {
                Podaj_nazwe_pliku();
                Odczyt_wielkosci_pliku(nazwa_pliku, plik);
                Tworzenie_tablicy_float();
                Odczyt_z_pliku_do_tablicy_float(liczebnosc_tablicy, plik);
                cout << "Dane do posortowania: ";
                Wypisywanie_tablicy_float();
                poprawne_skad_dane = true;
            }
            else
                (cout << "Nieprawidlowy sposob \n");

        } while (poprawne_skad_dane == false);
    }

    string Podaj_nazwe_pliku()
    {
        cout << "Prosze podac nazwe pliku: ";
        cin >> nazwa_pliku;
        return nazwa_pliku;
    }

    void Odczyt_wielkosci_pliku(string nazwa_pliku, ifstream &plik)
    {
        plik.open(nazwa_pliku);
        plik >> liczebnosc_tablicy;
    }

    void Odczyt_z_pliku_do_tablicy_int(int liczebnosc_tablicy, ifstream &plik)
    {
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            plik >> tablica_int[i];
        }
    }

    void Odczyt_z_pliku_do_tablicy_float(int liczebnosc_tablicy, ifstream &plik)
    {
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            plik >> tablica_float[i];
        }
    }
};

class Sortowania
{
public:
    int *kopiowanie_int(int liczebnosc_tablicy, int *tablica_int)
    {
        int *tablica = new int[liczebnosc_tablicy];
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            tablica[i] = tablica_int[i];
        }
        return tablica;
    }

    float *kopiowanie_float(int liczebnosc_tablicy, float *tablica_float)
    {
        float *tablica = new float[liczebnosc_tablicy];
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            tablica[i] = tablica_float[i];
        }
        return tablica;
    }

    template <typename T>
    void wypiszTablice(T tablica[], int liczebnosc_tablicy)
    {
        for (int i = 0; i < liczebnosc_tablicy; ++i)
            cout << tablica[i] << " ";
        cout << "\n";
    }

    //------------------------------ SORTOWANIA-----------------------------------

    template <typename T> // sortowanie przez wstawianie
    void wstawianie_zwykle(T tablica[], int liczebnosc_tablicy)
    {
        T *tablica1 = new T[liczebnosc_tablicy];
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            tablica1[i] = tablica[i];
        }

        T x;
        int i, j;

        // Rozpoczęcie pomiaru czasu
        auto start = std::chrono::high_resolution_clock::now();

        for (i = 1; i < liczebnosc_tablicy; i++)
        {
            x = tablica1[i];
            j = i - 1;
            while (j >= 0 && tablica1[j] > x)
            {
                tablica1[j + 1] = tablica1[j];
                j = j - 1;
            }
            tablica1[j + 1] = x;
        }

        // Zakończenie pomiaru czasu
        auto stop = std::chrono::high_resolution_clock::now();
        // Obliczenie różnicy czasu
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        cout << "\nSortowanie przez wstawianie zwykle: " << endl;
        wypiszTablice(tablica1, liczebnosc_tablicy);
        //   Sprawdzenie czy posortowane
        for (int i = 0; i < liczebnosc_tablicy - 1; i++)
        {
            if (tablica1[i] > tablica1[i + 1])
                cout << "Nieposortowane! \n";
        }
        cout << "Czas sortowania: " << duration.count() << " milisekund" << endl;
        delete[] tablica1;
    }

    template <typename T> // binarne sortowanie przez wstawianie
    void wstawianie_binarne(T tablica[], int liczebnosc_tablicy)
    {
        T *tablica1 = new T[liczebnosc_tablicy];
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            tablica1[i] = tablica[i];
        }
        int i, j, ip, ik;
        T x;

        // Rozpoczęcie pomiaru czasu
        auto start = std::chrono::high_resolution_clock::now();

        for (j = liczebnosc_tablicy - 2; j >= 0; j--)
        {
            x = tablica1[j];
            ip = j;
            ik = liczebnosc_tablicy;
            while (ik - ip > 1)
            {
                i = (ip + ik) / 2;
                if (x <= tablica1[i])
                    ik = i;
                else
                    ip = i;
            }
            for (i = j; i < ip; i++)
                tablica1[i] = tablica1[i + 1];
            tablica1[ip] = x;
        }

        // Zakończenie pomiaru czasu
        auto stop = std::chrono::high_resolution_clock::now();
        // Obliczenie różnicy czasu
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        cout << "Sortowanie przez wstawianie binarne: " << endl;
        wypiszTablice(tablica1, liczebnosc_tablicy);
        //   Sprawdzenie czy posortowane
        for (int i = 0; i < liczebnosc_tablicy - 1; i++)
        {
            if (tablica1[i] > tablica1[i + 1])
                cout << "Nieposortowane! \n";
        }
        cout << "Czas sortowania: " << duration.count() << " milisekund" << endl;
        delete[] tablica1;
    }

    template <typename T> // przywracanie wlasnosci kopca
    void kopiec(T tablica[], int liczebnosc_tablicy, int i)
    {
        int najwiekszy = i;
        int lewy = 2 * i + 1;
        int prawy = 2 * i + 2;

        if (lewy < liczebnosc_tablicy && tablica[lewy] > tablica[najwiekszy])
            najwiekszy = lewy;

        if (prawy < liczebnosc_tablicy && tablica[prawy] > tablica[najwiekszy])
            najwiekszy = prawy;

        if (najwiekszy != i)
        {
            swap(tablica[i], tablica[najwiekszy]);
            kopiec(tablica, liczebnosc_tablicy, najwiekszy);
        }
    }

    template <typename T>
    void sortowanie_kopcowe(T tablica[], int liczebnosc_tablicy)
    {
        T *tablica1 = new T[liczebnosc_tablicy];
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            tablica1[i] = tablica[i];
        }

        // Rozpoczęcie pomiaru czasu
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = liczebnosc_tablicy / 2 - 1; i >= 0; i--)
            kopiec(tablica1, liczebnosc_tablicy, i);

        for (int i = liczebnosc_tablicy - 1; i >= 0; i--)
        {
            swap(tablica1[0], tablica1[i]);
            kopiec(tablica1, i, 0);
        }

        // Zakończenie pomiaru czasu
        auto stop = std::chrono::high_resolution_clock::now();
        // Obliczenie różnicy czasu
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        // Sprawdzenie czy posortowane
        for (int i = 0; i < liczebnosc_tablicy - 1; i++)
        {
            if (tablica1[i] > tablica1[i + 1])
                cout << "Nieposortowane! \n";
        }

        cout << "Sortowanie przez kopcowanie: " << endl;
        wypiszTablice(tablica1, liczebnosc_tablicy);
        cout << "Czas sortowania: " << duration.count() << " milisekund" << endl;
        delete[] tablica1;
    }

    template <typename T>
    void sortowanie_szybkie(T tablica[], int lewy, int prawy)
    {
        int i, j;
        T piwot;

        if (lewy < prawy)
        {
            piwot = tablica[(lewy + prawy) / 2];
            i = lewy;
            j = prawy;

            do
            {
                while (tablica[i] < piwot)
                    i++;
                while (tablica[j] > piwot)
                    j--;
                if (i <= j)
                {
                    swap(tablica[i], tablica[j]);
                    i++;
                    j--;
                }
            } while (i <= j);

            if (lewy < j)
                sortowanie_szybkie(tablica, lewy, j);
            if (i < prawy)
                sortowanie_szybkie(tablica, i, prawy);
        }
    }

    template <typename T>
    void sortowanie_szybkie_wypisanie(T tablica[], int liczebnosc_tablicy)
    {
        T *tablica1 = new T[liczebnosc_tablicy];
        for (int i = 0; i < liczebnosc_tablicy; i++)
        {
            tablica1[i] = tablica[i];
        }

        // Rozpoczęcie pomiaru czasu
        auto start = std::chrono::high_resolution_clock::now();

        sortowanie_szybkie(tablica1, 0, liczebnosc_tablicy - 1);

        // Zakończenie pomiaru czasu
        auto stop = std::chrono::high_resolution_clock::now();
        // Obliczenie różnicy czasu
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        // Sprawdzenie czy posortowane
        for (int i = 0; i < liczebnosc_tablicy - 1; i++)
        {
            if (tablica1[i] > tablica1[i + 1])
                cout << "Nieposortowane! \n";
        }

        cout << "Sortowanie szybkie: " << endl;
        wypiszTablice(tablica1, liczebnosc_tablicy);
        cout << "Czas sortowania: " << duration.count() << " milisekund" << endl;
        delete[] tablica1;
    }
};

int main()
{
    srand(time(NULL));
    Menu start;
    Sortowania sort;

    int x;
    cout << "Prosze podac ilosc uruchomien programu: ";
    cin >> x;

    for (int i = 0; i < x; i++)
    {
        start.menu();

        if (start.typ_danych == "int")
        {
            sort.wstawianie_zwykle(start.tablica_int, start.liczebnosc_tablicy);
            sort.wstawianie_binarne(start.tablica_int, start.liczebnosc_tablicy);
            sort.sortowanie_kopcowe(start.tablica_int, start.liczebnosc_tablicy);
            sort.sortowanie_szybkie_wypisanie(start.tablica_int, start.liczebnosc_tablicy);
        }
        else if (start.typ_danych == "float")
        {
            sort.wstawianie_zwykle(start.tablica_float, start.liczebnosc_tablicy);
            sort.wstawianie_binarne(start.tablica_float, start.liczebnosc_tablicy);
            sort.sortowanie_kopcowe(start.tablica_float, start.liczebnosc_tablicy);
            sort.sortowanie_szybkie_wypisanie(start.tablica_float, start.liczebnosc_tablicy);
        }
    }

    char exit;
    do
    {
        cout << "Prosze wpisac 'q' i nacisnac Enter, aby zakonczyc program...";
        cin >> exit;
    } while (exit != 'q');

    return 0;
}