#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <time.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include "SDL_mixer.h"

using namespace std;


struct GameCell
{
    int minesAround = 0;
    bool isMine = false;
    bool isOpen = false;
    bool isBlocked = false;
    SDL_Texture* celltexture = NULL;
    SDL_Rect destination;
    SDL_Texture* numtexture = NULL;
    SDL_Rect numdestination;
};
SDL_Texture* IntTextTexture(SDL_Renderer* renderer, string text, TTF_Font* my_font);
SDL_Texture* timerTexture(SDL_Renderer* renderer, int time, TTF_Font* my_font);
void drawMineCount(SDL_Renderer*& renderer, int yCount, int xCount, GameCell** cells, TTF_Font* my_font);
void drawCells(SDL_Renderer*& renderer, int yCount, int xCount, GameCell** cells);
void generateLevel(int y, int x, int minescount, GameCell** cells, int ignorey, int ignorex);
bool winningCheck(GameCell** cells, int MinesCount, int x, int y);
bool isCellHit(int mouse_x, int mouse_y, GameCell cells);
bool isExist(int x, int y, int xCount, int yCount);
void openEmptyCells(SDL_Renderer*& gamerenderer, SDL_Surface* emptyGameCellTexture, GameCell** cells, int yCount, int xCount, int curry, int currx);
void countMinesAround(GameCell** cells, int xCount, int yCount, SDL_Renderer* renderer, TTF_Font* my_font);
bool gameStart(int w, int h, int minesCount, int xCount, int yCount, string nickname, bool fs);
SDL_Texture* TextTexture(SDL_Renderer* renderer, string text, TTF_Font* my_font);