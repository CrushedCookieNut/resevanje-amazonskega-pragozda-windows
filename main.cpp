#include <iostream>
#include <vector>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "include/sdl-window-and-renderer.hpp"
#include "include/ogenj.hpp"
#include "include/verigaOgnjev.hpp"
#include "include/drevo.hpp"
#include "include/zemljevidDreves.hpp"
#include "include/igralec.hpp"
#include "include/sovraznik.hpp"
#include "include/seznamSovraznikov.hpp"
#include "include/staroselec.hpp"
#include "include/seznamStaroselcev.hpp"
using namespace std;

/*void preverjanjeTrkov(igralec a, verigaOgnjev b, seznamSovraznikov c, seznamStaroselcev d, zemljevidDreves e) {
    SDL_Rect tmp;
    for (int i=0;i<b.veriga.size();i++) {
        tmp=b.veriga.at(i).getRect();
        if (SDL_HasIntersection(&a.getRect(),&tmp)) {
            b.izbrisiOgenj(i);
        }
    }
    for (int i=0;i<c.seznam.size();i++) {
        tmp=c.seznam.at(i).getRect();
        if (SDL_HasIntersection(&a.getRect(),&tmp)) {
            c.izbrisiSovraznika(i);
        }
    }
    for (int i=0;i<c.seznam.size();i++) {
        for (int j=0;j<e.zemljevid.size();j++) {
            tmp=e.zemljevid.at(i).getRect();
            if (SDL_HasIntersection(&c.seznam.at(i).getRect(),&tmp)) {
                e.uniciDrevo(i);
            }
        }
    }
}*/

void osvezevanje(zemljevidDreves igralenZemljevid, verigaOgnjev x, seznamSovraznikov a, igralec b, seznamStaroselcev c) {
    SDL_RenderClear(renderer);
    //preverjanjeTrkov(b,x,a,c,igralenZemljevid);
    igralenZemljevid.ustvariZemljevidDreves();
    for (int i=0;i<a.seznam.size();i++) {
        a.seznam.at(i).premikanje();
    }
    for (int i=0;i<c.seznam.size();i++) {
        c.seznam.at(i).premikanje(b);
    }
    x.izrisiVerigoOgnjev();
    a.izrisiSeznamSovraznikov();
    c.izrisiSeznamStaroselcev();
    b.preveriDotikanjeRoba();
    b.risanje();
    SDL_RenderPresent(renderer);
    //SDL_Delay(20);
}
//* tvoj  int main() sm rabu spremenit v to spodi, ker čene ne bi mogl zaznt SDL_main.h
int main(int argc, char** argv) {
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    initializeWindowAndRenderer();
    int flags=IMG_INIT_PNG;
    int initStatus=IMG_Init(flags);
    if ((initStatus&flags)!=flags) {
        cout << "SDL2_Image format not available!" << endl;
    }
    const int fps=60;
    const int frameDelay=1000/fps;
    Uint32 frameStart;
    int frameTime;

    zemljevidDreves igralenZemljevid;
    verigaOgnjev x;
    x.ustvariVerigoOgnjev();
    seznamSovraznikov a;
    a.ustvariSeznamSovraznikov();
    seznamStaroselcev b;
    b.ustvariSeznamStaroselcev();
    igralec igralec;
    osvezevanje(igralenZemljevid,x,a,igralec,b);

    SDL_Event windowEvent, premikanje;

    while (true) {
        frameStart=SDL_GetTicks();

        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT==windowEvent.type) {
                break;
            }
        } else if (SDL_PollEvent(&premikanje)) {
            if (premikanje.type==SDL_KEYDOWN) {
                igralec.premikanje();
                osvezevanje(igralenZemljevid,x,a,igralec,b);
            }
        } else {
            osvezevanje(igralenZemljevid,x,a,igralec,b);
        }
        
        frameTime=SDL_GetTicks()-frameStart;
        if (frameDelay>frameTime) {
            SDL_Delay(frameDelay-frameTime);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;

    return 0;
}
