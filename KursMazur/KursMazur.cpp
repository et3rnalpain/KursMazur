#include <iostream>
#include "GameManager.h"


int main(int argc, char* argv[])
{
    
    srand(time(NULL));
    int width, height, minesCount = 10, xCount, yCount, W,H, lvl = 1;
    W = 600;
    H = 500;
    string nickname = "Pavel";
    xCount = 9;
    yCount = 9;
    bool quit2 = false, create = false , fs = false,vm = true,vs = true;
    width = 50 + xCount * 30;
    height = 100 + yCount * 30;
    SDL_Init(SDL_INIT_EVERYTHING);
    int currmenupos = 0;
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Chunk* click = Mix_LoadWAV("click.wav");
    Mix_Music* music = Mix_LoadMUS("music.wav");
    Mix_Chunk* click2 = Mix_LoadWAV("click2.wav");
    //
    SDL_Window* mainmenu = SDL_CreateWindow("Main Menu", 200, 200, W, H, SDL_WINDOW_SHOWN);
    SDL_Renderer* menurenderer = SDL_CreateRenderer(mainmenu, -1, 0);
    SDL_Event menuevent;
    SDL_Surface* startgame = IMG_Load("startgame.bmp"); SDL_Rect startgamebutton = { W/2 - 200,H/2 - 230,400,100 };  SDL_Texture* sgbuttontexture = SDL_CreateTextureFromSurface(menurenderer, startgame);
    SDL_Surface* exitgame = IMG_Load("exit.bmp");  SDL_Rect exitgamebutton = { W / 2 - 200,H/2 + 130,400,100 };  SDL_Texture* egbuttontexture = SDL_CreateTextureFromSurface(menurenderer, exitgame);
    SDL_Surface* settings = IMG_Load("settings.bmp");  SDL_Rect settingsbutton = { W / 2 - 200,H/2 - 110,400,100 };  SDL_Texture* sbuttontexture = SDL_CreateTextureFromSurface(menurenderer, settings);
    SDL_Surface* records = IMG_Load("records.bmp");  SDL_Rect recordsbutton = { W / 2 - 200,H/2 + 10,400,100 };  SDL_Texture* rbuttontexture = SDL_CreateTextureFromSurface(menurenderer, records);
    //
    SDL_Rect textinput = { W/2,H/2 - 230,280,45 };
    SDL_Surface* tonfs = IMG_Load("tonfs.bmp"); SDL_Surface* tofffs = IMG_Load("tofffs.bmp"); SDL_Rect fullscreen = { W / 2 - 290,H / 2 - 130, 280,45};
    SDL_Texture* tonfstexture = SDL_CreateTextureFromSurface(menurenderer, tonfs);
    SDL_Texture* tofffstexture = SDL_CreateTextureFromSurface(menurenderer, tofffs);
    SDL_Surface* tonm = IMG_Load("tonm.bmp"); SDL_Surface* toffm = IMG_Load("toffm.bmp"); SDL_Rect soundvolume = { W / 2 - 290,H / 2 - 30,280,45 };
    SDL_Texture* tonmtexture = SDL_CreateTextureFromSurface(menurenderer, tonm);
    SDL_Texture* toffmtexture = SDL_CreateTextureFromSurface(menurenderer, toffm);
    SDL_Surface* tons = IMG_Load("tons.bmp"); SDL_Surface* toffs = IMG_Load("toffs.bmp"); SDL_Rect musicvolume = { W / 2 - 290,H / 2 + 70, 280, 45 };
    SDL_Texture* tonstexture = SDL_CreateTextureFromSurface(menurenderer, tons);
    SDL_Texture* toffstexture = SDL_CreateTextureFromSurface(menurenderer, toffs);
    SDL_Surface* exitmenu = IMG_Load("exitmenu.bmp"); SDL_Rect exitsettings = { W / 2 - 290,H / 2 + 170, 280, 45 };
    SDL_Texture* exitmenutexture = SDL_CreateTextureFromSurface(menurenderer, exitmenu);
   //
    SDL_Surface* easy = IMG_Load("easy.bmp"); SDL_Surface* medium = IMG_Load("medium.bmp"); SDL_Surface* hard = IMG_Load("hard.bmp"); SDL_Surface* osob = IMG_Load("osob.bmp"); SDL_Surface* nicknames = IMG_Load("nickname.bmp");
    SDL_Rect nicknamerect = { W / 2 - 290,H / 2 - 230,280,45 }; SDL_Rect easyrect = { W / 2,H / 2 - 130, 280,45 }; SDL_Rect mediumrect = { W / 2,H / 2 - 30, 280,45 }; SDL_Rect hardrect = { W / 2,H / 2 +70, 280,45 }; SDL_Rect osobrect = { W / 2,H / 2 +170, 280,45 };
    SDL_Texture* easytexture = SDL_CreateTextureFromSurface(menurenderer, easy);
    SDL_Texture* mediumtexture = SDL_CreateTextureFromSurface(menurenderer, medium);
    SDL_Texture* hardtexture = SDL_CreateTextureFromSurface(menurenderer, hard);
    SDL_Texture* osobtexture = SDL_CreateTextureFromSurface(menurenderer, osob);
    SDL_Texture* nicknametexture = SDL_CreateTextureFromSurface(menurenderer, nicknames);
    SDL_Rect currlvl1 = { W / 2 + 235, H / 2 - 130,45,45 };
    SDL_Rect currlvl2 = { W / 2 + 235, H / 2 - 30,45,45 };
    SDL_Rect currlvl3 = { W / 2 + 235, H / 2  + 70,45,45 };
    SDL_Rect currlvl4 = { W / 2 + 235, H / 2 + 170,45,45 }; SDL_Surface* icon = IMG_Load("gameCellMine.bmp"); SDL_Texture* currlvltexture = SDL_CreateTextureFromSurface(menurenderer,icon);
    SDL_SetRenderDrawColor(menurenderer, 230, 230, 230, 0);
    SDL_RenderClear(menurenderer);
    SDL_RenderPresent(menurenderer);
    Mix_PlayMusic(music, -1);
    do
    {
        if (vs) Mix_Volume(0, 50); else Mix_Volume(0, 0);
        if (!vm) Mix_VolumeMusic(0); else Mix_VolumeMusic(50);
        if (fs) { SDL_SetWindowFullscreen(mainmenu, SDL_WINDOW_FULLSCREEN_DESKTOP); }
        else
        {
            SDL_SetWindowSize(mainmenu, 600, 500);
        }
        switch (currmenupos)
        {
        case 0:
        {
            if (create)
            {
                mainmenu = SDL_CreateWindow("Main Menu", 200, 200, 600, 500, SDL_WINDOW_SHOWN);
                menurenderer = SDL_CreateRenderer(mainmenu, -1, 0);
                SDL_SetRenderDrawColor(menurenderer, 230, 230, 230, 0);
                SDL_RenderClear(menurenderer);
                SDL_RenderPresent(menurenderer);
                SDL_Surface* startgame = IMG_Load("startgame.bmp"); startgamebutton = { 100,20,400,100 };  sgbuttontexture = SDL_CreateTextureFromSurface(menurenderer, startgame);
                SDL_Surface* exitgame = IMG_Load("exit.bmp");  exitgamebutton = { 100,380,400,100 };  egbuttontexture = SDL_CreateTextureFromSurface(menurenderer, exitgame);
                SDL_Surface* settings = IMG_Load("settings.bmp");  settingsbutton = { 100,140,400,100 };  sbuttontexture = SDL_CreateTextureFromSurface(menurenderer, settings);
                SDL_Surface* records = IMG_Load("records.bmp");  recordsbutton = { 100,260,400,100 }; rbuttontexture = SDL_CreateTextureFromSurface(menurenderer, records);
                SDL_Rect textinput = { W / 2,H / 2 - 230,280,45 };
                SDL_Surface* tonfs = IMG_Load("tonfs.bmp"); SDL_Surface* tofffs = IMG_Load("tofffs.bmp"); fullscreen = { W / 2 - 290,H / 2 - 130, 280,45 };
                tonfstexture = SDL_CreateTextureFromSurface(menurenderer, tonfs);
                tofffstexture = SDL_CreateTextureFromSurface(menurenderer, tofffs);
                SDL_Surface* tonm = IMG_Load("tonm.bmp"); SDL_Surface* toffm = IMG_Load("toffm.bmp"); soundvolume = { W / 2 - 290,H / 2 - 30,280,45 };
                tonmtexture = SDL_CreateTextureFromSurface(menurenderer, tonm);
                toffmtexture = SDL_CreateTextureFromSurface(menurenderer, toffm);
                SDL_Surface* tons = IMG_Load("tons.bmp"); SDL_Surface* toffs = IMG_Load("toffs.bmp");musicvolume = { W / 2 - 290,H / 2 + 70, 280, 45 };
                tonstexture = SDL_CreateTextureFromSurface(menurenderer, tons);
                toffstexture = SDL_CreateTextureFromSurface(menurenderer, toffs);
                SDL_Surface* exitmenu = IMG_Load("exitmenu.bmp"); exitsettings = { W / 2 - 290,H / 2 + 170, 280, 45 };
                exitmenutexture = SDL_CreateTextureFromSurface(menurenderer, exitmenu);
                SDL_Surface* easy = IMG_Load("easy.bmp"); SDL_Surface* medium = IMG_Load("medium.bmp"); SDL_Surface* hard = IMG_Load("hard.bmp"); SDL_Surface* osob = IMG_Load("osob.bmp"); SDL_Surface* nicknames = IMG_Load("nickname.bmp");
                nicknamerect = { W / 2 - 290,H / 2 - 230,280,45 }; easyrect = { W / 2,H / 2 - 130, 280,45 }; mediumrect = { W / 2,H / 2 - 30, 280,45 }; hardrect = { W / 2,H / 2 + 70, 280,45 }; osobrect = { W / 2,H / 2 + 170, 280,45 };
                easytexture = SDL_CreateTextureFromSurface(menurenderer, easy);
                mediumtexture = SDL_CreateTextureFromSurface(menurenderer, medium);
                hardtexture = SDL_CreateTextureFromSurface(menurenderer, hard);
                osobtexture = SDL_CreateTextureFromSurface(menurenderer, osob);
                nicknametexture = SDL_CreateTextureFromSurface(menurenderer, nicknames);
                currlvl1 = { W / 2 + 235, H / 2 - 130,45,45 };
                currlvl2 = { W / 2 + 235, H / 2 - 30,45,45 };
                currlvl3 = { W / 2 + 235, H / 2 + 70,45,45 };
                currlvl4 = { W / 2 + 235, H / 2 + 170,45,45 }; SDL_Surface* icon = IMG_Load("gameCellMine.bmp"); currlvltexture = SDL_CreateTextureFromSurface(menurenderer, icon);

                SDL_FreeSurface(startgame); SDL_FreeSurface(exitgame); SDL_FreeSurface(settings); SDL_FreeSurface(records);
                SDL_FreeSurface(tonfs); SDL_FreeSurface(tofffs); SDL_FreeSurface(tonm); SDL_FreeSurface(toffm);
                SDL_FreeSurface(tons); SDL_FreeSurface(toffs); SDL_FreeSurface(exitmenu);
                create = false;
            }
            //SDL_ShowWindow(mainmenu);
            SDL_RenderCopy(menurenderer, sgbuttontexture, NULL, &startgamebutton);
            SDL_RenderCopy(menurenderer, egbuttontexture, NULL, &exitgamebutton);
            SDL_RenderCopy(menurenderer, sbuttontexture, NULL, &settingsbutton);
            SDL_RenderCopy(menurenderer, rbuttontexture, NULL, &recordsbutton);
            SDL_RenderPresent(menurenderer);
            while (SDL_PollEvent(&menuevent))
            {
                if (menuevent.type == SDL_QUIT)
                {
                    currmenupos = 4;
                }
                if (menuevent.type == SDL_MOUSEBUTTONUP && menuevent.button.button == SDL_BUTTON_LEFT)
                {
                    if (menuevent.button.x > 100 && menuevent.button.x < 500 && menuevent.button.y > 20 && menuevent.button.y < 120) {
                        currmenupos = 1; quit2 = false;
                        Mix_PlayChannel(0, click, 0);
                    }
                    if (menuevent.button.x > 100 && menuevent.button.x < 500 && menuevent.button.y > 380 && menuevent.button.y < 460)
                    {
                        currmenupos = 4;
                        Mix_PlayChannel(0, click, 0);
                    }
                    if (menuevent.button.x > 100 && menuevent.button.x < 500 && menuevent.button.y > 140 && menuevent.button.y < 240)
                    {
                        currmenupos = 2;
                        Mix_PlayChannel(0, click, 0);
                    }
                }

            }

        } break;

        case 1:
        {
            //SDL_HideWindow(mainmenu);
            SDL_DestroyWindow(mainmenu);
            switch (lvl)
            {
            case 1: { xCount = 9; yCount = 9; minesCount = 10; }; break;
            case 2: { xCount = 16; yCount = 16; minesCount = 40; }; break;
            case 3: { xCount = 30; yCount = 16; minesCount = 99; }; break;
            //case 4: SDL_RenderCopy(menurenderer, currlvltexture, NULL, &currlvl4); break;
            }
            width = 50 + xCount * 30;
            height = 100 + yCount * 30;
            while (!quit2)
            {
                quit2 = gameStart(width, height, minesCount, xCount, yCount, nickname);
            }
            currmenupos = 0;
            create = true;
        } break;
        case 2: 
        {
            SDL_SetRenderDrawColor(menurenderer, 230, 230, 230, 0);
            SDL_RenderClear(menurenderer);
            SDL_SetRenderDrawColor(menurenderer, 255, 255, 255, 0);
            SDL_RenderFillRect(menurenderer, &textinput);
            if (fs) SDL_RenderCopy(menurenderer, tofffstexture, NULL, &fullscreen); else SDL_RenderCopy(menurenderer, tonfstexture, NULL, &fullscreen);
            if (vm) SDL_RenderCopy(menurenderer, toffmtexture, NULL, &musicvolume); else SDL_RenderCopy(menurenderer, tonmtexture, NULL, &musicvolume);
            if (vs) SDL_RenderCopy(menurenderer, toffstexture, NULL, &soundvolume); else SDL_RenderCopy(menurenderer, tonstexture, NULL, &soundvolume);
            SDL_RenderCopy(menurenderer, exitmenutexture, NULL, &exitsettings);
            SDL_RenderCopy(menurenderer, easytexture, NULL, &easyrect);
            SDL_RenderCopy(menurenderer, mediumtexture, NULL, &mediumrect);
            SDL_RenderCopy(menurenderer, hardtexture, NULL, &hardrect);
            SDL_RenderCopy(menurenderer, osobtexture, NULL, &osobrect);
            SDL_RenderCopy(menurenderer, nicknametexture, NULL, &nicknamerect);
            switch (lvl)
            {
            case 1: SDL_RenderCopy(menurenderer, currlvltexture, NULL, &currlvl1); break;
            case 2: SDL_RenderCopy(menurenderer, currlvltexture, NULL, &currlvl2); break;
            case 3: SDL_RenderCopy(menurenderer, currlvltexture, NULL, &currlvl3); break;
            case 4: SDL_RenderCopy(menurenderer, currlvltexture, NULL, &currlvl4); break;
            }
            SDL_RenderPresent(menurenderer);
            while (SDL_PollEvent(&menuevent))
            {
                if (menuevent.type == SDL_QUIT)
                {
                    currmenupos = 4;
                }
                if (menuevent.type == SDL_MOUSEBUTTONUP && menuevent.button.button == SDL_BUTTON_LEFT)
                {
                    if (menuevent.button.x > W / 2 - 290 && menuevent.button.x <  W / 2 - 10  && menuevent.button.y > H / 2 - 130 && menuevent.button.y < H / 2 - 85) 
                    {
                        fs = !fs; Mix_PlayChannel(0, click, 0);
                    }
                    if (menuevent.button.x > W / 2 - 290 && menuevent.button.x < W / 2 - 10 && menuevent.button.y > H / 2 - 30 && menuevent.button.y < H / 2 + 15)
                    {
                        vs = !vs; Mix_PlayChannel(0, click, 0);
                    }
                    if (menuevent.button.x > W / 2 - 290 && menuevent.button.x < W / 2 - 10 && menuevent.button.y > H / 2 + 70 && menuevent.button.y < H / 2 + 115)
                    {
                        vm = !vm; Mix_PlayChannel(0, click, 0);
                    }
                    if (menuevent.button.x > W / 2 - 290 && menuevent.button.x < W / 2 - 10 && menuevent.button.y > H / 2 + 170 && menuevent.button.y < H / 2 + 215)
                    {
                        currmenupos = 0; SDL_RenderClear(menurenderer); Mix_PlayChannel(0, click, 0);
                    }
                    if (menuevent.button.x > W / 2 && menuevent.button.x <  W / 2 + 280 && menuevent.button.y > H / 2 - 130 && menuevent.button.y < H / 2 - 85)
                    {
                        lvl = 1; Mix_PlayChannel(0, click, 0);
                    }
                    if (menuevent.button.x > W / 2 && menuevent.button.x < W / 2 + 280 && menuevent.button.y > H / 2 - 30 && menuevent.button.y < H / 2 + 15)
                    {
                        lvl = 2; Mix_PlayChannel(0, click, 0);
                    }
                    if (menuevent.button.x > W / 2 && menuevent.button.x < W / 2 + 280 && menuevent.button.y > H / 2 + 70 && menuevent.button.y < H / 2 + 115)
                    {
                        lvl = 3; Mix_PlayChannel(0, click, 0);
                    }
                    if (menuevent.button.x > W / 2 && menuevent.button.x < W / 2 + 280 && menuevent.button.y > H / 2 + 170 && menuevent.button.y < H / 2 + 215)
                    {
                        lvl = 4; Mix_PlayChannel(0, click, 0);
                    }
                }

            }
        }
        break;
        case 3: break;
        case 4: exit(0); break;
        }
    
    } while (true);
    SDL_FreeSurface(startgame); SDL_FreeSurface(exitgame); SDL_FreeSurface(settings); SDL_FreeSurface(records);
    SDL_FreeSurface(tonfs); SDL_FreeSurface(tofffs); SDL_FreeSurface(tonm); SDL_FreeSurface(toffm);
    SDL_FreeSurface(tons); SDL_FreeSurface(toffs); SDL_FreeSurface(exitmenu); SDL_FreeSurface(nicknames);
    SDL_Quit();
    Mix_Quit();
    return 0;
    
}
