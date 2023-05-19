#include "GameManager.h"

using namespace std;

SDL_Texture* IntTextTexture(SDL_Renderer* renderer, string text, TTF_Font* my_font)
{
    SDL_Color fon = { 0,0,0,255 };
    SDL_Color textcolor = { 10 + stoi(text) * 60, 20 + stoi(text) * 15,150 + stoi(text) * 15,0 };
    SDL_Surface* face = TTF_RenderUTF8_Shaded(my_font, text.c_str(), textcolor, fon);
    SDL_SetColorKey(face, 10, SDL_MapRGB(face->format, 0, 0, 0));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, face);
    SDL_FreeSurface(face);
    return texture;
}

SDL_Texture* TextTexture(SDL_Renderer* renderer, string text, TTF_Font* my_font)
{
    SDL_Color fon = { 0,0,0,255 };
    SDL_Color textcolor = { 0,0,0,0 };
    SDL_Surface* face = TTF_RenderUTF8_Shaded(my_font, text.c_str(), textcolor, fon);
    SDL_SetColorKey(face, 10, SDL_MapRGB(face->format, 0, 0, 0));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, face);
    SDL_FreeSurface(face);
    return texture;
}

SDL_Texture* timerTexture(SDL_Renderer* renderer, int time, TTF_Font* my_font)
{
    SDL_Color fon = { 100,100,100,0 };
    SDL_Color textcolor = { 200, 200,200,0 };
    SDL_Surface* face = TTF_RenderUTF8_Shaded(my_font, to_string(time).c_str(), textcolor, fon);
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
            if (cells[i][z].isOpen && !cells[i][z].isMine && cells[i][z].minesAround > 0) SDL_RenderCopy(renderer, cells[i][z].numtexture, NULL, &cells[i][z].numdestination);
        }
    }
}

void drawCells(SDL_Renderer*& renderer, int yCount, int xCount, GameCell** cells)
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
        if (!cells[indexy][indexx].isMine && indexy != ignorey && indexx != ignorex)
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

void openEmptyCells(SDL_Renderer*& gamerenderer, SDL_Surface* emptyGameCellTexture, GameCell** cells, int yCount, int xCount, int curry, int currx)
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

    if (isExist(curry - 1, currx + 1, xCount, yCount) && cells[curry - 1][currx + 1].minesAround == 0 && !cells[curry - 1][currx + 1].isOpen)
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

    if (isExist(curry - 1, currx - 1, xCount, yCount) && cells[curry - 1][currx - 1].minesAround == 0 && !cells[curry - 1][currx - 1].isOpen)
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
    if (isExist(curry + 1, currx - 1, xCount, yCount) && cells[curry + 1][currx - 1].minesAround == 0 && !cells[curry + 1][currx - 1].isOpen)
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
    if (isExist(curry + 1, currx + 1, xCount, yCount) && cells[curry + 1][currx + 1].minesAround == 0 && !cells[curry + 1][currx + 1].isOpen)
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

bool gameStart(int w, int h, int minesCount, int xCount, int yCount, string nickname, bool fs)
{
    int ticks = 0, currenttime = 0, mines = minesCount;
    bool firstClick = false;
    SDL_Window* game = SDL_CreateWindow("Saper", 400, 400, w, h, SDL_WINDOW_SHOWN);
    SDL_Surface* Icon = IMG_Load("gameCellMine.bmp");
    if (fs) SDL_SetWindowFullscreen(game, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetWindowIcon(game, Icon);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("Arialbd.ttf", 100);
    SDL_Renderer* gamerenderer = SDL_CreateRenderer(game, -1, 0);
    SDL_Event event;
    Mix_Chunk* click = Mix_LoadWAV("click.wav");
    Mix_Chunk* click2 = Mix_LoadWAV("click2.wav");
    Mix_Chunk* explode = Mix_LoadWAV("explode.wav");
    SDL_Surface* closedGameCellTexture = IMG_Load("gameCell.bmp");
    SDL_Surface* emptyGameCellTexture = IMG_Load("gameCellEmpty.bmp");
    SDL_Surface* mineGameCellTexture = IMG_Load("gameCellMine.bmp");
    SDL_Surface* flagGameCellTexture = IMG_Load("gameCellFlag.bmp");
    SDL_Surface* alive = IMG_Load("alive.bmp");
    SDL_Surface* dead = IMG_Load("dead.bmp");
    SDL_Surface* win = IMG_Load("win.bmp");
    SDL_Rect timerrect = { w - 75, 10,50,60 };
    SDL_Rect mineCount = { 25, 10, 50,60 };
    SDL_Rect restartButton = { w / 2 - 30,10,60,60 };
    SDL_Texture* restartButtonTexture1 = SDL_CreateTextureFromSurface(gamerenderer, alive);
    SDL_Texture* restartButtonTexture2 = SDL_CreateTextureFromSurface(gamerenderer, dead);
    SDL_Texture* restartButtonTexture3 = SDL_CreateTextureFromSurface(gamerenderer, win);
    SDL_Texture* rbt = restartButtonTexture1;
    SDL_Texture* timerText = timerTexture(gamerenderer, currenttime, font);
    SDL_Texture* minesText = timerTexture(gamerenderer, mines, font);
    GameCell** cells = new GameCell * [yCount];
    ofstream fout;
    fout.open("record.txt", ios::app);
    for (int i = 0; i < yCount; i++)
    {
        cells[i] = new GameCell[xCount];
    }
    for (int i = 0; i < yCount; i++)
    {
        for (int z = 0; z < xCount; z++)
        {
            cells[i][z].destination = cells[i][z].numdestination = { 25 + z * 30,75 + i * 30,30,30 };
            if (!cells[i][z].isMine) cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, closedGameCellTexture);
        }
    }

    bool quit = false;
    bool restart = false;
    bool starttimer = false;
    int starttime;
    while (!quit)
    {
        SDL_SetRenderDrawColor(gamerenderer, 230, 230, 230, 0);
        SDL_RenderClear(gamerenderer);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                restart = false;
                break;
            }
            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                for (int i = 0; i < yCount; i++)
                {
                    for (int z = 0; z < xCount; z++)
                    {
                        if (isCellHit(event.button.x, event.button.y, cells[i][z]) && !firstClick && !cells[i][z].isBlocked)
                        {
                            generateLevel(yCount, xCount, minesCount, cells, i, z);
                            countMinesAround(cells, xCount, yCount, gamerenderer, font);
                            firstClick = true;
                            if (cells[i][z].minesAround == 0) openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, i, z);
                            starttime = SDL_GetTicks();
                            starttimer = true;
                            Mix_PlayChannel(0, click, 0);
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
                                    rbt = restartButtonTexture2;
                                }
                            }
                            starttimer = false;
                            Mix_PlayChannel(0, explode, 0);
                        }
                        if (isCellHit(event.button.x, event.button.y, cells[i][z]) && !cells[i][z].isMine && !cells[i][z].isOpen && !cells[i][z].isBlocked)
                        {
                            cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, emptyGameCellTexture);
                            cells[i][z].isOpen = true;
                            if (cells[i][z].minesAround == 0)
                            {
                                openEmptyCells(gamerenderer, emptyGameCellTexture, cells, yCount, xCount, i, z);
                            }
                            Mix_PlayChannel(0, click, 0);
                        }

                    }
                }
                if (event.button.x > w / 2 - 30 && event.button.x < w / 2 + 30 && event.button.y > 10 && event.button.y < 70) 
                {
                    Mix_PlayChannel(0, click2, 0);
                    restart = true;
                    quit = true;
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_RIGHT && starttimer)
            {
                Mix_PlayChannel(0, click2, 0);
                for (int i = 0; i < yCount; i++)
                {
                    for (int z = 0; z < xCount; z++)
                    {
                        if (isCellHit(event.button.x, event.button.y, cells[i][z]) && !cells[i][z].isOpen && !cells[i][z].isBlocked)
                        {
                            cells[i][z].isBlocked = true;
                            cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, flagGameCellTexture);
                            mines--;
                            minesText = timerTexture(gamerenderer, mines, font);
                        }
                        else if (isCellHit(event.button.x, event.button.y, cells[i][z]) && !cells[i][z].isOpen && cells[i][z].isBlocked)
                        {
                            cells[i][z].isBlocked = false;
                            cells[i][z].celltexture = SDL_CreateTextureFromSurface(gamerenderer, closedGameCellTexture);
                            mines++;
                            minesText = timerTexture(gamerenderer, mines, font);
                        }
                    }
                }
            }
            if (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYUP) 
            {
                quit = true;
                restart = false;
                break;
            }
            if (event.key.keysym.sym == SDLK_r && event.type == SDL_KEYUP)
            {
                quit = true;
                restart = true;
                break;
            }
        }
        SDL_RenderCopy(gamerenderer, rbt, NULL, &restartButton);
        drawCells(gamerenderer, yCount, xCount, cells);
        drawMineCount(gamerenderer, yCount, xCount, cells, font);
        SDL_RenderCopy(gamerenderer, minesText, NULL, &mineCount);
        if (starttimer)
        {
            ticks = (SDL_GetTicks() - starttime) / 1000;
            if (currenttime < ticks) {
                currenttime = ticks;
                SDL_DestroyTexture(timerText);
                timerText = timerTexture(gamerenderer, currenttime, font);
            }
            SDL_RenderCopy(gamerenderer, timerText, NULL, &timerrect);
        }
        if (winningCheck(cells, minesCount, xCount, yCount)) 
        { 
            if(starttimer) fout << nickname << " "<< xCount << " " << yCount<< " " << minesCount<< " " << currenttime << endl;
            starttimer = false;
            rbt = restartButtonTexture3; 
            for (int i = 0; i < yCount; i++)
            {
                for (int z = 0; z < xCount; z++)
                {
                    cells[i][z].isBlocked = true;
                }
            }
        }
        SDL_RenderCopy(gamerenderer, timerText, NULL, &timerrect);
        SDL_RenderPresent(gamerenderer);
    }

    //Очистка памяти
    for (int i = 0; i < yCount; i++)
    {
        delete[] cells[i];
    }
    delete[] cells;
    TTF_CloseFont(font);
    SDL_FreeSurface(closedGameCellTexture); SDL_FreeSurface(mineGameCellTexture); SDL_FreeSurface(emptyGameCellTexture); SDL_FreeSurface(flagGameCellTexture); SDL_FreeSurface(alive); SDL_FreeSurface(dead); SDL_FreeSurface(win);
    Mix_FreeChunk(click); Mix_FreeChunk(click2); Mix_FreeChunk(explode);
    SDL_DestroyTexture(restartButtonTexture1); SDL_DestroyTexture(restartButtonTexture2); SDL_DestroyTexture(restartButtonTexture3); SDL_DestroyTexture(rbt); SDL_DestroyTexture(minesText); SDL_DestroyTexture(timerText);
    SDL_DestroyWindow(game);
    SDL_DestroyRenderer(gamerenderer);
    TTF_Quit();
    fout.close();
    if (restart == false) return true;
    else return false;

}
