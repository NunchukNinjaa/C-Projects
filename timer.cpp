#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    int h, m, s;
    cout << "\nEnter time in hh mm ss :";
    cin >> h >> m >> s;

    int time = h * 3600 + m * 60 + s;

    for (int i = 0; time > 0; i++)
    {
        system("cls");
        cout << time--;
        Sleep(1000);
        system("cls");
    }

    cout << "TIME ENDED !";

    return 0;
}