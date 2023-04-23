#include <iostream>
#include "GameManager.h"

struct GameCell 
{
    int minesAround = 0;
    bool isMine = false;
    bool isOpen = false;
    SDL_Texture* celltexture = NULL;
    SDL_Rect destination;
};

SDL_Texture* IntTextTexture(SDL_Renderer* renderer, string text, TTF_Font* my_font)
{
    SDL_Color fon = { 0,0,0,255 };
    SDL_Color textcolor = { 50+ stoi(text) * 23, 30+stoi(text) * 30,100+stoi(text) * 15,0 };
    SDL_Surface* face = TTF_RenderUTF8_Shaded(my_font, text.c_str(), textcolor, fon);
    SDL_SetColorKey(face, 10, SDL_MapRGB(face->format, 0, 0, 0));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, face);
    SDL_FreeSurface(face);
    return texture;
}

void drawMineCount(SDL_Renderer*& renderer, int yCount, int xCount, GameCell** cells, TTF_Font* my_font)
{
    for (int i = 0; i < yCount; i++)
    {
        for (int z = 0; z < xCount; z++)
        {
            SDL_Rect rect = { cells[i][z].destination.x+4,cells[i][z].destination.y+1,cells[i][z].destination.w - 8,cells[i][z].destination.h-2 };
            if (cells[i][z].isOpen && !cells[i][z].isMine && cells[i][z].minesAround>0) SDL_RenderCopy(renderer, IntTextTexture(renderer, to_string(cells[i][z].minesAround), my_font), NULL, &rect);
        }
    }
}

void drawCells(SDL_Renderer*& renderer,int yCount, int xCount, GameCell** cells)
{
    for (int i = 0; i < yCount; i++)
    {
        for (int z = 0; z < xCount; z++)
        {
            SDL_RenderCopy(renderer, cells[i][z].celltexture, NULL, &cells[i][z].destination);
        }
    }
}

void generateLevel(int y, int x, int minescount, GameCell** cells) 
{
    for (int i = 0; i < minescount;) 
    {
        int indexx = rand() % x;
        int indexy = rand() % y;
        if (!cells[indexy][indexx].isMine) 
        {
            cells[indexy][indexx].isMine = true;
            i++;
        }
    }
}

bool isCellHit(int mouse_x, int mouse_y, GameCell cells) 
{
    if (!cells.isOpen)
    {
        int cx = cells.destination.x + cells.destination.w / 2;
        int cy = cells.destination.y + cells.destination.w / 2;
        return mouse_x<cx + cells.destination.w / 2 && mouse_x > cx - cells.destination.w / 2 && mouse_y<cy + cells.destination.w / 2 && mouse_y > cy - cells.destination.w / 2;
    }
    else return false;
}

bool isExist(int x, int y, int xCount, int yCount) 
{
    return (x >= 0) && (x <= xCount-1) && (y >= 0) && (y <= yCount-1);
}

void countMinesAround(GameCell** cells, int xCount, int yCount) 
{
    for (int i = 0; i < yCount; i++) 
    {
        for (int z = 0; z < xCount; z++) 
        {
            if(isExist(i-1,z,xCount,yCount))
            {
                if (cells[i - 1][z].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i + 1, z, xCount, yCount))
            {
                if (cells[i + 1][z].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i, z+1, xCount, yCount))
            {
                if (cells[i][z+1].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i, z-1, xCount, yCount))
            {
                if (cells[i][z-1].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i - 1, z+1, xCount, yCount))
            {
                if (cells[i - 1][z+1].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i - 1, z-1, xCount, yCount))
            {
                if (cells[i - 1][z - 1].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i + 1, z - 1, xCount, yCount))
            {
                if (cells[i + 1][z - 1].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i + 1, z + 1, xCount, yCount))
            {
                if (cells[i + 1][z + 1].isMine) cells[i][z].minesAround++;
            }
            cout << cells[i][z].minesAround;
        }
    }
}

void gameStart(int w,int h, int minesCount, int xCount, int yCount) 
{
    bool firstClick = false;
    SDL_Surface* Icon = IMG_Load("gameCellMine.bmp");
    SDL_Window* game = SDL_CreateWindow("Saper Main Menu", 400, 400, w, h, SDL_WINDOW_SHOWN);
    SDL_SetWindowIcon(game, Icon);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("Arialbd.ttf",50);
    SDL_Renderer* gamerenderer = SDL_CreateRenderer(game, -1, 0);
    SDL_Event event;
    SDL_Surface* closedGameCellTexture = IMG_Load("gameCell.bmp");
    SDL_Surface* emptyGameCellTexture = IMG_Load("gameCellEmpty.bmp");
    SDL_Surface* mineGameCellTexture = IMG_Load("gameCellMine.bmp");
    GameCell** cells = new GameCell*[yCount];
    for (int i = 0; i < yCount; i++) 
    {
        cells[i] = new GameCell[xCount];
    }

    for (int i = 0; i < yCount; i++) 
    {
        for (int z = 0; z < xCount; z++) 
        {
            cells[i][z].destination = {50+z*30,100+i*30,30,30};
            if (!cells[i][z].isMine) cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, closedGameCellTexture);
        }
    }

    bool quit = false;
    while (!quit) 
    {
        SDL_SetRenderDrawColor(gamerenderer, 230, 230, 230, 0);
        SDL_RenderClear(gamerenderer);
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) 
            {
                for (int i = 0; i < yCount; i++) 
                {
                    for (int z = 0; z < xCount; z++) 
                    {
                        if (isCellHit(event.button.x, event.button.y, cells[i][z]) && !firstClick) 
                        {
                            generateLevel(yCount,xCount,minesCount,cells);
                            countMinesAround(cells, xCount, yCount);
                            firstClick = true;
                        }
                        if (isCellHit(event.button.x, event.button.y, cells[i][z]) && cells[i][z].isMine && !cells[i][z].isOpen)
                        {
                            for (int i = 0; i < yCount; i++)
                            {
                                for (int z = 0; z < xCount; z++)
                                {
                                    if (cells[i][z].isMine) {
                                        cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, mineGameCellTexture);
                                        cells[i][z].isOpen = true;
                                    }
                                }
                            }
                        }
                        if (isCellHit(event.button.x, event.button.y, cells[i][z]) && !cells[i][z].isMine && !cells[i][z].isOpen)
                        {
                            cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                            cells[i][z].isOpen = true;
                        }
                    }
                }
            }
        }
        drawCells(gamerenderer,yCount,xCount,cells);
        drawMineCount(gamerenderer,yCount,xCount,cells,font);
        SDL_RenderPresent(gamerenderer);
    }

    //Очистка памяти
    for (int i = 0; i < yCount; i++)
    {
        delete[] cells[i];
    }
    delete[] cells;
    SDL_DestroyWindow(game);
    SDL_DestroyRenderer(gamerenderer);
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int width, height, minesCount, xCount, yCount;
    xCount = 9;
    yCount = 9;
    width = 100 + xCount * 30;
    height = 200 + yCount * 30;
    SDL_Init(SDL_INIT_EVERYTHING);
    gameStart(width,height,10,xCount,yCount);
    SDL_Quit();
    return 0;
}
