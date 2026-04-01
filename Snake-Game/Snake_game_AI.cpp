#include <iostream>
#include <conio.h>   // _kbhit(), _getch()
#include <windows.h> // Sleep()
#include <ctime>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 10;

int x, y;      // snake head
int foodX, foodY;
int score;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    srand(time(0));
    foodX = rand() % (width - 2) + 1;
    foodY = rand() % (height - 2) + 1;
    score = 0;
}

void Draw()
{
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";

            if (i == y && j == x)
                cout << "O";          // snake head
            else if (i == foodY && j == foodX)
                cout << "F";          // food
            else
                cout << " ";

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a': dir = LEFT;  break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP;    break;
            case 's': dir = DOWN;  break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic()
{
    switch (dir)
    {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default: break;
    }

    // Wall collision
    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    // Food collision
    if (x == foodX && y == foodY)
    {
        score += 10;
        foodX = rand() % (width - 2) + 1;
        foodY = rand() % (height - 2) + 1;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100); // speed control
    }

    system("cls");
    cout << "Game Over!" << endl;
    cout << "Final Score: " << score << endl;
    return 0;
}
