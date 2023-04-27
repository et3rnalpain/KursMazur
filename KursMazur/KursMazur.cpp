#include <iostream>
#include "GameManager.h"

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

SDL_Texture* IntTextTexture(SDL_Renderer* renderer, string text, TTF_Font* my_font)
{
    SDL_Color fon = { 0,0,0,255 };
    SDL_Color textcolor = { 10+ stoi(text) * 60, 20+stoi(text) * 15,150+stoi(text) * 15,0 };
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
            if (cells[i][z].isOpen && !cells[i][z].isMine && cells[i][z].minesAround>0) SDL_RenderCopy(renderer, cells[i][z].numtexture, NULL, & cells[i][z].numdestination);
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

void generateLevel(int y, int x, int minescount, GameCell** cells, int ignorey, int ignorex)
{
    for (int i = 0; i < minescount;) 
    {
        int indexx = rand() % x;
        int indexy = rand() % y;
        if (!cells[indexy][indexx].isMine && indexy!=ignorey && indexx!=ignorex) 
        {
            cells[indexy][indexx].isMine = true;
            cells[indexy][indexx].minesAround = -1;
            i++;
        }
    }
}

bool winningCheck(GameCell** cells, int MinesCount, int x, int y)
{
    int cellsCount = x * y;
    int openCellsCount = 0;
    
    for (int i = 0; i < y; i++) 
    {
        for (int z = 0; z < x; z++) 
        {
            if (cells[i][z].isOpen) openCellsCount++;
        }
    }
    cellsCount -= openCellsCount;
    if (cellsCount == MinesCount) return true;
    else return false;
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
    return (x >= 0) && (x < yCount) && (y >= 0) && (y < xCount);
}

void openEmptyCells(SDL_Renderer*& gamerenderer,SDL_Surface* emptyGameCellTexture,GameCell** cells, int yCount, int xCount, int curry, int currx)
{
            if (isExist(curry - 1, currx, xCount, yCount) && cells[curry - 1][currx].minesAround == 0 && !cells[curry - 1][currx].isOpen)
            {
                cells[curry - 1][currx].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry - 1][currx].isOpen = true;
                openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, curry - 1, currx);
            }
            else if (isExist(curry - 1, currx, xCount, yCount) && cells[curry - 1][currx].minesAround > 0 && !cells[curry - 1][currx].isOpen) 
            {
                cells[curry - 1][currx].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry - 1][currx].isOpen = true;
            }

            if (isExist(curry + 1, currx, xCount, yCount) && cells[curry + 1][currx].minesAround == 0 && !cells[curry + 1][currx].isOpen)
            {
                cells[curry + 1][currx].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry + 1][currx].isOpen = true;
                openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, curry + 1, currx);
            }
            else if (isExist(curry + 1, currx, xCount, yCount) && cells[curry + 1][currx].minesAround > 0 && !cells[curry + 1][currx].isOpen) 
            {
                cells[curry + 1][currx].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry + 1][currx].isOpen = true;
            }

            if (isExist(curry, currx + 1, xCount, yCount) && cells[curry][currx + 1].minesAround == 0 && !cells[curry][currx + 1].isOpen)
            {
                cells[curry][currx + 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry][currx + 1].isOpen = true;
                openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, curry, currx + 1);
            }
            else if (isExist(curry, currx + 1, xCount, yCount) && cells[curry][currx + 1].minesAround > 0 && !cells[curry][currx + 1].isOpen) 
            {
                cells[curry][currx + 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry][currx + 1].isOpen = true;
            }

            if (isExist(curry, currx - 1, xCount, yCount) && cells[curry][currx - 1].minesAround == 0 && !cells[curry][currx - 1].isOpen)
            {
                cells[curry][currx - 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry][currx - 1].isOpen = true;
                openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, curry, currx - 1);
            }
            else if (isExist(curry, currx - 1, xCount, yCount) && cells[curry][currx - 1].minesAround > 0 && !cells[curry][currx - 1].isOpen)
            {
                cells[curry][currx - 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry][currx - 1].isOpen = true;
            }

            if (isExist(curry - 1, currx + 1, xCount, yCount) && cells[curry - 1][currx + 1].minesAround == 0 && !cells[curry-1][currx + 1].isOpen)
            {
                cells[curry - 1][currx + 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry - 1][currx + 1].isOpen = true;
                openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, curry - 1, currx + 1);
            }
            else if (isExist(curry - 1, currx + 1, xCount, yCount) && cells[curry - 1][currx + 1].minesAround > 0 && !cells[curry - 1][currx + 1].isOpen) 
            {
                cells[curry - 1][currx + 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry - 1][currx + 1].isOpen = true;
            }

            if (isExist(curry - 1, currx - 1, xCount, yCount) && cells[curry - 1][currx - 1].minesAround == 0 && !cells[curry-1][currx - 1].isOpen)
            {
                cells[curry - 1][currx - 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry - 1][currx - 1].isOpen = true;
                openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, curry - 1, currx - 1);
            }
            else if (isExist(curry - 1, currx - 1, xCount, yCount) && cells[curry - 1][currx - 1].minesAround > 0 && !cells[curry - 1][currx - 1].isOpen)
            {
                cells[curry - 1][currx - 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry - 1][currx - 1].isOpen = true;
            }
            if (isExist(curry + 1, currx - 1, xCount, yCount) && cells[curry + 1][currx - 1].minesAround == 0 && !cells[curry+1][currx - 1].isOpen)
            {
                cells[curry + 1][currx - 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry + 1][currx - 1].isOpen = true;
                openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, curry + 1, currx - 1);
            }
            else if (isExist(curry + 1, currx - 1, xCount, yCount) && cells[curry + 1][currx - 1].minesAround > 0 && !cells[curry + 1][currx - 1].isOpen)
            {
                cells[curry + 1][currx - 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry + 1][currx - 1].isOpen = true;
            }
            if (isExist(curry + 1, currx + 1, xCount, yCount) && cells[curry + 1][currx + 1].minesAround == 0 && !cells[curry+1][currx + 1].isOpen)
            {
                cells[curry + 1][currx + 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry + 1][currx + 1].isOpen = true;
                openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, curry + 1, currx + 1);
            }
            else if (isExist(curry + 1, currx + 1, xCount, yCount) && cells[curry + 1][currx + 1].minesAround > 0 && !cells[curry + 1][currx + 1].isOpen)
            {
                cells[curry + 1][currx + 1].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                cells[curry + 1][currx + 1].isOpen = true;
            }
}

void countMinesAround(GameCell** cells, int xCount, int yCount, SDL_Renderer* renderer, TTF_Font* my_font) 
{
    for (int i = 0; i < yCount; i++) 
    {
        for (int z = 0; z < xCount; z++)
        {
            if (isExist(i - 1, z, xCount, yCount))
            {
                if (cells[i - 1][z].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i + 1, z, xCount, yCount))
            {
               if (cells[i + 1][z].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i, z + 1, xCount, yCount))
            {
                if (cells[i][z + 1].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i, z - 1, xCount, yCount))
            {
                if (cells[i][z - 1].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i - 1, z + 1, xCount, yCount))
            {
                if (cells[i - 1][z + 1].isMine) cells[i][z].minesAround++;
            }
            if (isExist(i - 1, z - 1, xCount, yCount))
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
            if (cells[i][z].minesAround > 0) {
                cells[i][z].numtexture = IntTextTexture(renderer, to_string(cells[i][z].minesAround), my_font);
            }
        }
    }

}

bool gameStart(int w,int h, int minesCount, int xCount, int yCount) 
{
    bool firstClick = false;
    SDL_Window* game = SDL_CreateWindow("Saper Main Menu", 400, 400, w, h, SDL_WINDOW_SHOWN);
    SDL_Surface* Icon = IMG_Load("gameCellMine.bmp");
    SDL_SetWindowIcon(game, Icon);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("Arialbd.ttf",100);
    SDL_Renderer* gamerenderer = SDL_CreateRenderer(game, -1, 0);
    SDL_Event event;
    SDL_Surface* closedGameCellTexture = IMG_Load("gameCell.bmp");
    SDL_Surface* emptyGameCellTexture = IMG_Load("gameCellEmpty.bmp");
    SDL_Surface* mineGameCellTexture = IMG_Load("gameCellMine.bmp");
    SDL_Surface* flagGameCellTexture = IMG_Load("gameCellFlag.bmp");
    GameCell** cells = new GameCell*[yCount];
    for (int i = 0; i < yCount; i++) 
    {
        cells[i] = new GameCell[xCount];
    }
    for (int i = 0; i < yCount; i++) 
    {
        for (int z = 0; z < xCount; z++) 
        {
            cells[i][z].destination = cells[i][z].numdestination = {50+z*30,100+i*30,30,30};
            if (!cells[i][z].isMine) cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, closedGameCellTexture);
        }
    }

    bool quit = false;
    bool restart = false;
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
                        if (isCellHit(event.button.x, event.button.y, cells[i][z]) && !firstClick && !cells[i][z].isBlocked)
                        {
                            generateLevel(yCount,xCount,minesCount,cells,i,z);
                            countMinesAround(cells, xCount, yCount, gamerenderer, font);
                            firstClick = true;
                            if(cells[i][z].minesAround == 0) openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, i, z);
                        }
                        if (isCellHit(event.button.x, event.button.y, cells[i][z]) && cells[i][z].isMine && !cells[i][z].isOpen && !cells[i][z].isBlocked)
                        {
                            for (int i = 0; i < yCount; i++)
                            {
                                for (int z = 0; z < xCount; z++)
                                {
                                    if (cells[i][z].isMine) {
                                        cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, mineGameCellTexture);
                                        cells[i][z].isOpen = true;
                                    }
                                    cells[i][z].isBlocked = true;
                                }
                            }
                        }
                        if (isCellHit(event.button.x, event.button.y, cells[i][z]) && !cells[i][z].isMine && !cells[i][z].isOpen && !cells[i][z].isBlocked)
                        {
                            cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                            cells[i][z].isOpen = true;
                            if (cells[i][z].minesAround == 0) 
                            {
                                openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, i, z);
                            }
                        }
                        
                    }
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_RIGHT)
            {
                for (int i = 0; i < yCount; i++)
                {
                    for (int z = 0; z < xCount; z++)
                    {
                        if (isCellHit(event.button.x, event.button.y, cells[i][z]) && !cells[i][z].isOpen && !cells[i][z].isBlocked)
                        {
                            cells[i][z].isBlocked = true;
                            cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, flagGameCellTexture);
                        }
                        else if (isCellHit(event.button.x, event.button.y, cells[i][z]) && !cells[i][z].isOpen && cells[i][z].isBlocked) 
                        {
                            cells[i][z].isBlocked = false;
                            cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, closedGameCellTexture);
                        }
                    }
                }
            }
            if ((event.type == SDL_KEYUP) && (event.key.keysym.sym = SDLK_F5))
            {
                restart = true;
                quit = true;
            }
        }
        drawCells(gamerenderer,yCount,xCount,cells);
        drawMineCount(gamerenderer,yCount,xCount,cells,font);
        SDL_RenderPresent(gamerenderer);
        if (winningCheck(cells, minesCount, xCount, yCount)) { cout << " Победа!" << endl; break; }
    }

    //Очистка памяти
    for (int i = 0; i < yCount; i++)
    {
        delete[] cells[i];
    }
    delete[] cells;
    SDL_DestroyWindow(game);
    SDL_DestroyRenderer(gamerenderer);
    if (restart == true) return false;
    else return true;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int width, height, minesCount = 2, xCount, yCount;
    xCount = 3;
    yCount = 3;
    bool quit;
    width = 100 + xCount * 30;
    height = 200 + yCount * 30;
    SDL_Init(SDL_INIT_EVERYTHING);
    do 
    {
        quit = gameStart(width, height, minesCount, xCount, yCount);
    } while (!quit);
    SDL_Quit();
    return 0;
}
