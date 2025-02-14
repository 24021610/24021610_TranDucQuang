#include <iostream>
#include <SDL.h>
#include "graphics.h"
#include "header.h"
using namespace std;


int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    SDL_Rect rect;
    rect.x=100;
    rect.y=100;
    rect.h=100;
    rect.w=100;
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 0 );
    SDL_RenderFillRect(graphics.renderer, &rect);
    SDL_RenderPresent(graphics.renderer);
    SDL_Texture* texture = graphics.loadTexture("img.PNG");
    SDL_Event event;
    int x,y;
     while (true) {
        SDL_GetMouseState(&x, &y);
        cerr << x << ", " << y << endl;

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 cerr << "Down at (" << x << ", " << y << ")\n";
                 break;
            case SDL_MOUSEBUTTONUP:
                 cerr << "Up at (" << x << ", " << y << ")\n";
                 break;

        }
        SDL_Delay(80);
    }




    graphics.waitUntilKeyPressed();
    graphics.sdlQuit();
    return 0;
}
