#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

bool game_over;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;
int tailX[100], tailY[100];
int nTail;

// This sets-up the game before we begin to play.
void set_up()
{
    game_over = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    srand(time(0));
    fruitX = rand() % width;
    fruitY = rand() % height;
    if (fruitX == 0 || fruitY == 0)
    {
        fruitX = 3;
        fruitY = 3;
    }
    score = 0;
}

// This draws the map every time the while in the main()
// and refreshes according to the Sleep() command.
void draw()
{
    system("cls");

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
            {
                cout << "#";
            }
            else
            {
                if (i == y && j == x)
                {
                    cout << "O";
                }
                else if (i == fruitY && j == fruitX)
                {
                    cout << "F";
                }
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++)
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print)
                    {
                        cout << " ";
                    }
                }
            }
        }
        cout << endl;
    }
    cout << "SCORE : " << score << endl;
}

// This part decides the input from the user :)
void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;

        case 'd':
            dir = RIGHT;
            break;

        case 'w':
            dir = UP;
            break;

        case 's':
            dir = DOWN;
            break;

        case 'x':
            game_over = true;
            break;
        }
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break;

    default:
        break;
    }
    if (x >= width || x <= 0 || y >= height || y <= 0)
    {
        game_over = true;
    }

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            game_over = true;
        }
    }

    if (x == fruitX && y == fruitY)
    {
        nTail++;
        score += 1;
        srand(time(0));
        fruitX = rand() % width;
        fruitY = rand() % height;
        if (fruitX == 0 || fruitY == 0)
        {
            fruitX = 3;
            fruitY = 3;
        }
    }
}

int main()
{
    set_up();

    while (!game_over)
    {
        draw();
        input();
        logic();
        Sleep(100);
    }

    cout << "\nGAME OVER !!";

    return 0;
}
