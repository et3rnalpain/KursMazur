#include <iostream>
#include "GameManager.h"


int main(int argc, char* argv[])
{
    srand(time(NULL));
    int width, height, minesCount = 2, xCount, yCount;
    xCount = 5;
    yCount = 5;
    bool quit;
    width = 50 + xCount * 30;
    height = 100 + yCount * 30;
    SDL_Init(SDL_INIT_EVERYTHING);
    do 
    {
        quit = gameStart(width, height, minesCount, xCount, yCount);
    } while (!quit);
    SDL_Quit();
    return 0;
}
