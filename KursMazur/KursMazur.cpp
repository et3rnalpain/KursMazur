#include <iostream>
#include "GameManager.h"

int main(int argc, char* argv[])
{
    
    srand(time(NULL));
    int width, height, minesCount = 10, xCount, yCount, W,H, lvl = 1;
    string easyrec = "1000", mediumrec = "1000", hardrec = "1000", nickeasyrec, nickmediumrec, nickhardrec, sizex, sizey, minessize, rec, currnick;
    W = 600;
    H = 500;
    string nickname = "Pavel";
    xCount = 9;
    yCount = 9;
    bool quit2 = false, create = false , fs = false,vm = true,vs = true,checkrec = true, quit3 = false;
    width = 50 + xCount * 30;
    height = 100 + yCount * 30;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TTF_Font* font2 = TTF_OpenFont("Arialbd.ttf", 100);
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
    SDL_Texture* currtext = TextTexture(menurenderer,nickname,font2);
    SDL_Rect currlvl1 = { W / 2 + 235, H / 2 - 130,45,45 };
    SDL_Rect currlvl2 = { W / 2 + 235, H / 2 - 30,45,45 };
    SDL_Rect currlvl3 = { W / 2 + 235, H / 2  + 70,45,45 };
    SDL_Rect currlvl4 = { W / 2 + 235, H / 2 + 170,45,45 }; 
    SDL_Surface* icon = IMG_Load("gameCellMine.bmp"); SDL_Texture* currlvltexture = SDL_CreateTextureFromSurface(menurenderer,icon);
    SDL_Surface* eazy = IMG_Load("eazy.bmp"); SDL_Texture* eazytexture = SDL_CreateTextureFromSurface(menurenderer, eazy);
    SDL_Surface* mediumz = IMG_Load("mediumz.bmp"); SDL_Texture* mediumztexture = SDL_CreateTextureFromSurface(menurenderer, mediumz);
    SDL_Surface* hardz = IMG_Load("hardz.bmp"); SDL_Texture* hardztexture = SDL_CreateTextureFromSurface(menurenderer, hardz);
    SDL_Rect eazyrect = { W / 2 - 290, H / 2 - 200, 180, 50 };
    SDL_Rect mediumzrect = { W / 2 - 90, H / 2 - 200, 180, 50 };
    SDL_Rect hardzrect = { W / 2 + 110, H / 2 - 200, 180, 50 };
    SDL_Rect eazyRECrect = { W / 2 - 290, H / 2 - 140, 180, 50 };
    SDL_Rect mediumzRECrect = { W / 2 - 90, H / 2 - 140, 180, 50 };
    SDL_Rect hardzRECrect = { W / 2 + 110, H / 2 - 140, 180, 50 };
    SDL_Texture* easyREC = NULL, * mediumREC = NULL, * hardREC = NULL, * nicktexture = TextTexture(menurenderer,nickname, font2);
    SDL_SetRenderDrawColor(menurenderer, 230, 230, 130, 0);
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
            SDL_SetWindowFullscreen(mainmenu, 0);
        }
        switch (currmenupos)
        {
        case 0:
        {
            if (create)
            {
                mainmenu = SDL_CreateWindow("Main Menu", 200, 200, 600, 500, SDL_WINDOW_SHOWN);
                menurenderer = SDL_CreateRenderer(mainmenu, -1, 0);
                SDL_RenderPresent(menurenderer);
                startgame = IMG_Load("startgame.bmp"); startgamebutton = { 100,20,400,100 };  sgbuttontexture = SDL_CreateTextureFromSurface(menurenderer, startgame);
                exitgame = IMG_Load("exit.bmp");  exitgamebutton = { 100,380,400,100 };  egbuttontexture = SDL_CreateTextureFromSurface(menurenderer, exitgame);
                settings = IMG_Load("settings.bmp");  settingsbutton = { 100,140,400,100 };  sbuttontexture = SDL_CreateTextureFromSurface(menurenderer, settings);
                records = IMG_Load("records.bmp");  recordsbutton = { 100,260,400,100 }; rbuttontexture = SDL_CreateTextureFromSurface(menurenderer, records);
                SDL_Rect textinput = { W / 2,H / 2 - 230,280,45 };
                tonfs = IMG_Load("tonfs.bmp"); tofffs = IMG_Load("tofffs.bmp"); fullscreen = { W / 2 - 290,H / 2 - 130, 280,45 };
                tonfstexture = SDL_CreateTextureFromSurface(menurenderer, tonfs);
                tofffstexture = SDL_CreateTextureFromSurface(menurenderer, tofffs);
                tonm = IMG_Load("tonm.bmp");  toffm = IMG_Load("toffm.bmp"); soundvolume = { W / 2 - 290,H / 2 - 30,280,45 };
                tonmtexture = SDL_CreateTextureFromSurface(menurenderer, tonm);
                toffmtexture = SDL_CreateTextureFromSurface(menurenderer, toffm);
                tons = IMG_Load("tons.bmp"); toffs = IMG_Load("toffs.bmp"); musicvolume = { W / 2 - 290,H / 2 + 70, 280, 45 };
                tonstexture = SDL_CreateTextureFromSurface(menurenderer, tons);
                toffstexture = SDL_CreateTextureFromSurface(menurenderer, toffs);
                exitmenu = IMG_Load("exitmenu.bmp"); exitsettings = { W / 2 - 290,H / 2 + 170, 280, 45 };
                exitmenutexture = SDL_CreateTextureFromSurface(menurenderer, exitmenu);
                easy = IMG_Load("easy.bmp");  medium = IMG_Load("medium.bmp");  hard = IMG_Load("hard.bmp");  osob = IMG_Load("osob.bmp");  nicknames = IMG_Load("nickname.bmp");
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
                icon = IMG_Load("gameCellMine.bmp"); currlvltexture = SDL_CreateTextureFromSurface(menurenderer, icon);
                eazy = IMG_Load("eazy.bmp"); eazytexture = SDL_CreateTextureFromSurface(menurenderer, eazy);
                mediumz = IMG_Load("mediumz.bmp"); mediumztexture = SDL_CreateTextureFromSurface(menurenderer, mediumz);
                hardz = IMG_Load("hardz.bmp"); hardztexture = SDL_CreateTextureFromSurface(menurenderer, hardz);
                eazyrect = { W / 2 - 290, H / 2 - 200, 180, 50 };
                mediumzrect = { W / 2 - 90, H / 2 - 200, 180, 50 };
                hardzrect = { W / 2 + 110, H / 2 - 200, 180, 50 };
                eazyRECrect = { W / 2 - 290, H / 2 - 140, 180, 50 };
                mediumzRECrect = { W / 2 - 90, H / 2 - 140, 180, 50 };
                hardzRECrect = { W / 2 + 110, H / 2 - 140, 180, 50 };
                easyREC = NULL; mediumREC = NULL;  hardREC = NULL; nicktexture = TextTexture(menurenderer, nickname, font2);

                SDL_FreeSurface(startgame); SDL_FreeSurface(exitgame); SDL_FreeSurface(settings); SDL_FreeSurface(records);
                SDL_FreeSurface(tonfs); SDL_FreeSurface(tofffs); SDL_FreeSurface(tonm); SDL_FreeSurface(toffm);
                SDL_FreeSurface(tons); SDL_FreeSurface(toffs); SDL_FreeSurface(exitmenu);
                create = false;
            }
            //SDL_ShowWindow(mainmenu);
            SDL_SetRenderDrawColor(menurenderer, 230, 230, 230, 0);
            SDL_RenderClear(menurenderer);
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
                    if (menuevent.button.x > 100 && menuevent.button.x < 500 && menuevent.button.y > 260 && menuevent.button.y < 360)
                    {
                        currmenupos = 3; checkrec = true;
                        Mix_PlayChannel(0, click, 0);
                    }
                }

            }

        } break;
        case 1:
        {
            SDL_DestroyWindow(mainmenu);
            SDL_DestroyRenderer(menurenderer);
            switch (lvl)
            {
            case 1: { xCount = 9; yCount = 9; minesCount = 10; }; break;
            case 2: { xCount = 16; yCount = 16; minesCount = 40; }; break;
            case 3: { xCount = 30; yCount = 16; minesCount = 99; }; break;
            case 4: break;
            }
            width = 50 + xCount * 30;
            height = 100 + yCount * 30;
            while (!quit2)
            {
                quit2 = gameStart(width, height, minesCount, xCount, yCount, nickname, fs);
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
            SDL_RenderCopy(menurenderer, nicktexture, NULL, &textinput);
            switch (lvl)
            {
            case 1: SDL_RenderCopy(menurenderer, currlvltexture, NULL, &currlvl1); break;
            case 2: SDL_RenderCopy(menurenderer, currlvltexture, NULL, &currlvl2); break;
            case 3: SDL_RenderCopy(menurenderer, currlvltexture, NULL, &currlvl3); break;
            case 4: SDL_RenderCopy(menurenderer, currlvltexture, NULL, &currlvl4); break;
            }
            //SDL_RenderCopy(menurenderer, currtext,NULL,&textinput);
            SDL_RenderPresent(menurenderer);
            
            while (SDL_PollEvent(&menuevent))
            {
                if (menuevent.type == SDL_QUIT)
                {
                    currmenupos = 4;
                }
                if ((menuevent.type == SDL_TEXTINPUT) && (menuevent.key.keysym.sym != SDLK_BACKSPACE))
                {
                    nickname += menuevent.text.text;
                    SDL_DestroyTexture(nicktexture);
                    nicktexture = TextTexture(menurenderer, nickname, font2);
                }
                else if ((menuevent.key.keysym.sym == SDLK_BACKSPACE) && (menuevent.type == SDL_KEYDOWN) && nickname.length() > 0) 
                {
                    nickname.pop_back();
                    if (nickname.length() == 0) 
                    {
                        SDL_DestroyTexture(nicktexture);
                        nicktexture = TextTexture(menurenderer, u8"Введите имя игрока", font2);
                    }
                    else 
                    {
                        SDL_DestroyTexture(nicktexture);
                        nicktexture = TextTexture(menurenderer, nickname, font2);
                    }
                }
                if ((menuevent.type == SDL_KEYUP) && (menuevent.key.keysym.sym == SDLK_RETURN) ) 
                {
                    cout << nickname;
                    SDL_StopTextInput();
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
                        currmenupos = 0; SDL_RenderClear(menurenderer); Mix_PlayChannel(0, click, 0); create = false;
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
                        
                        SDL_Window* questwindow = SDL_CreateWindow("Type size of game", 300, 300, 200, 220, SDL_WINDOW_SHOWN);
                        SDL_Renderer* questrender = SDL_CreateRenderer(questwindow, -1, 0);
                        SDL_Rect x = { 20,20,35,35 }, xinp = { 100,20,70,35 }; SDL_Texture* xtext = TextTexture(questrender, "x", font2);
                        SDL_Rect y = { 20, 70, 35, 35 }, yinp = { 100,70,70,35 }; SDL_Texture* ytext = TextTexture(questrender, "y", font2);
                        SDL_Rect m = { 20, 120, 70, 35 }, minp = { 100,120,70,35 }; SDL_Texture* mtext = TextTexture(questrender, "mines", font2);
                        SDL_Rect acc = { 20,170, 150,35 }; SDL_Texture* acctext = TextTexture(questrender, u8"Принять", font2);
                        SDL_Texture* xinputtext = TextTexture(questrender, to_string(xCount), font2);
                        SDL_Texture* yinputtext = TextTexture(questrender, to_string(yCount), font2);
                        SDL_Texture* minputtext = TextTexture(questrender, to_string(minesCount), font2);
                        SDL_Event questevent;
                        string xs = to_string(xCount), ys = to_string(yCount), ms =  to_string(minesCount);
                        int currinput = 0;
                        do
                        {
                            SDL_SetRenderDrawColor(questrender, 100, 100, 100, 0);
                            SDL_RenderClear(questrender);
                            SDL_SetRenderDrawColor(questrender, 150, 150, 150, 0);
                            SDL_RenderFillRect(questrender, &acc);
                            SDL_RenderCopy(questrender, xtext, NULL, &x);
                            SDL_RenderCopy(questrender, ytext, NULL, &y);
                            SDL_RenderCopy(questrender, mtext, NULL, &m);
                            SDL_RenderCopy(questrender, acctext, NULL, &acc);
                            SDL_RenderFillRect(questrender, &xinp);
                            SDL_RenderFillRect(questrender, &yinp);
                            SDL_RenderFillRect(questrender, &minp);
                            SDL_RenderCopy(questrender, xinputtext, NULL, &xinp);
                            SDL_RenderCopy(questrender, yinputtext, NULL, &yinp);
                            SDL_RenderCopy(questrender, minputtext, NULL, &minp);
                            SDL_RenderPresent(questrender);
                            while (SDL_PollEvent(&questevent))
                            {
                                if ((questevent.type == SDL_TEXTINPUT) && (questevent.key.keysym.sym != SDLK_BACKSPACE))
                                {
                                    switch (currinput) 
                                    {
                                        case 1:
                                        {
                                            xs += questevent.text.text;
                                            SDL_DestroyTexture(xinputtext);
                                            xinputtext = TextTexture(questrender, xs, font2);
                                        } break;
                                        case 2:
                                        {
                                            ys += questevent.text.text;
                                            SDL_DestroyTexture(yinputtext);
                                            yinputtext = TextTexture(questrender, ys, font2);
                                        }
                                        break;
                                        case 3:
                                        {
                                            ms += questevent.text.text;
                                            SDL_DestroyTexture(minputtext);
                                            minputtext = TextTexture(questrender, ms, font2);
                                        }
                                        break;
                                    }
                                }
                                else if ((questevent.key.keysym.sym == SDLK_BACKSPACE) && (questevent.type == SDL_KEYDOWN) && xs.length() > 0 && ys.length() > 0 && ms.length() > 0 )
                                {
                                    switch (currinput)
                                    {
                                        case 1:
                                        {
                                            xs.pop_back();
                                            if (xs.length() == 0)
                                            {
                                                SDL_DestroyTexture(xinputtext);
                                                xinputtext = TextTexture(questrender, u8"_", font2);
                                            }
                                            else
                                            {
                                                SDL_DestroyTexture(xinputtext);
                                                xinputtext = TextTexture(questrender, xs, font2);
                                            }
                                        } break;
                                        case 2:
                                        {
                                            ys.pop_back();
                                            if (ys.length() == 0)
                                            {
                                                SDL_DestroyTexture(yinputtext);
                                                yinputtext = TextTexture(questrender, u8"_", font2);
                                            }
                                            else
                                            {
                                                SDL_DestroyTexture(yinputtext);
                                                yinputtext = TextTexture(questrender, ys, font2);
                                            }
                                        } break;
                                        case 3:
                                        {
                                            ms.pop_back();
                                            if (ms.length() == 0)
                                            {
                                                SDL_DestroyTexture(minputtext);
                                                minputtext = TextTexture(questrender, u8"_", font2);
                                            }
                                            else
                                            {
                                                SDL_DestroyTexture(minputtext);
                                                minputtext = TextTexture(questrender, ms, font2);
                                            }
                                        } break;
                                    }
                                    
                                }
                                if ((questevent.type == SDL_KEYUP) && (questevent.key.keysym.sym == SDLK_RETURN))
                                {
                                    SDL_StopTextInput();
                                }
                                if (questevent.type == SDL_MOUSEBUTTONUP && questevent.button.button == SDL_BUTTON_LEFT)
                                {
                                    if (questevent.button.x > 20 && questevent.button.x < 170 && questevent.button.y > 170 && questevent.button.y < 205)
                                    {
                                        quit3 = true;
                                    }
                                    if (questevent.button.x > 100 && questevent.button.x < 170 && questevent.button.y > 20 && questevent.button.y < 55)
                                    {
                                        currinput = 1;
                                        SDL_StartTextInput();
                                    }
                                    if (questevent.button.x > 100 && questevent.button.x < 170 && questevent.button.y > 70 && questevent.button.y < 105)
                                    {
                                        currinput = 2;
                                        SDL_StartTextInput();
                                    }
                                    if (questevent.button.x > 100 && questevent.button.x < 170 && questevent.button.y > 120 && questevent.button.y < 155)
                                    {
                                        currinput = 3;
                                        SDL_StartTextInput();
                                    }
                                }
                            }
                        } while (!quit3);
                        quit3 = false;
                        SDL_DestroyTexture(xinputtext);
                        SDL_DestroyTexture(yinputtext);
                        SDL_DestroyTexture(minputtext);
                        SDL_DestroyTexture(xtext);
                        SDL_DestroyTexture(ytext);
                        SDL_DestroyTexture(mtext);
                        SDL_DestroyTexture(acctext);
                        SDL_DestroyRenderer(questrender);
                        SDL_DestroyWindow(questwindow);
                        xCount = atoi(xs.c_str());
                        yCount = atoi(ys.c_str());
                        minesCount = atoi(ms.c_str());
                    }
                    if (menuevent.button.x > W / 2 && menuevent.button.x < W / 2 + 280 && menuevent.button.y > H / 2 -230 && menuevent.button.y < H / 2 - 185)
                    {
                        cout << "Start"; SDL_StartTextInput();
                    }
                    
                }
            }
        }
        break;
        case 3: 
        {
            if (checkrec)
            {
                fstream fin;
                fin.open("record.txt");
                while (!fin.eof())
                {
                    fin >> currnick;
                    fin >> sizex;
                    fin >> sizey;
                    fin >> minessize;
                    fin >> rec;
                    if (atoi(sizex.c_str()) == 9 && atoi(sizex.c_str()) == 9 && atoi(minessize.c_str()) == 10 && atoi(rec.c_str()) < atoi(easyrec.c_str()))
                    {
                        easyrec = rec;
                        nickeasyrec = currnick;
                    }
                    if (atoi(sizex.c_str()) == 16 && atoi(sizex.c_str()) == 16 && atoi(minessize.c_str()) == 40 && atoi(rec.c_str()) < atoi(mediumrec.c_str()))
                    {
                        mediumrec = rec;
                        nickmediumrec = currnick;
                    }
                    if (atoi(sizex.c_str()) == 16 && atoi(sizex.c_str()) == 30 && atoi(minessize.c_str()) == 99 && atoi(rec.c_str()) < atoi(hardrec.c_str()))
                    {
                        hardrec = rec;
                        nickhardrec = currnick;
                    }
                }
                checkrec = false;
                fin.close();
                if (atoi(easyrec.c_str()) != 1000)
                {
                    easyREC = TextTexture(menurenderer, nickeasyrec + " " + easyrec, font2);
                }
                else easyREC = TextTexture(menurenderer, u8"Рекорда нет", font2);
                if (atoi(mediumrec.c_str()) != 1000)
                {
                    mediumREC = TextTexture(menurenderer, nickmediumrec + " " + mediumrec, font2);
                }
                else mediumREC = TextTexture(menurenderer, u8"Рекорда нет", font2);
                if (atoi(hardrec.c_str()) != 1000)
                {
                    hardREC = TextTexture(menurenderer, nickhardrec + " " + hardrec, font2);
                }
                else hardREC = TextTexture(menurenderer, u8"Рекорда нет", font2);
            }
            SDL_SetRenderDrawColor(menurenderer, 230, 230, 230, 0);
            SDL_RenderClear(menurenderer);
            SDL_RenderCopy(menurenderer, exitmenutexture, NULL, &exitsettings);
            SDL_RenderCopy(menurenderer, eazytexture, NULL, &eazyrect);
            SDL_RenderCopy(menurenderer, mediumztexture, NULL, &mediumzrect);
            SDL_RenderCopy(menurenderer, hardztexture, NULL, &hardzrect);
            SDL_RenderCopy(menurenderer, easyREC, NULL, &eazyRECrect);
            SDL_RenderCopy(menurenderer, mediumREC, NULL, &mediumzRECrect);
            SDL_RenderCopy(menurenderer, hardREC, NULL, &hardzRECrect);
            SDL_RenderPresent(menurenderer);
            while (SDL_PollEvent(&menuevent))
            {
                if (menuevent.type == SDL_MOUSEBUTTONUP && menuevent.button.button == SDL_BUTTON_LEFT)
                {
                    if (menuevent.button.x > W / 2 - 290 && menuevent.button.x < W / 2 - 10 && menuevent.button.y > H / 2 + 170 && menuevent.button.y < H / 2 + 215)
                    {
                        currmenupos = 0; SDL_RenderClear(menurenderer); Mix_PlayChannel(0, click, 0); create = false;
                    }
                }
            }

        }
        break;
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
