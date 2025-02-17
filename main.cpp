#include <iostream>
#include <SDL.h>
#include "graphics.h"
#include "header.h"
#include "logic.h"

int main(int argc, char *argv[])
{
     Graphics graphics;

     ScrollingBackground background;
     Mouse mouse;

     graphics.initSDL();

     mouse.x=100;
     mouse.y=100;

     mouse.texture = graphics.loadTexture ("Model.PNG");
     background.setTexture(graphics.loadTexture("ahaha.PNG"));

    SDL_Event event;
while (true) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) graphics.sdlQuit();
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_w) mouse.jump();
        }
    }

    SDL_RenderClear(graphics.renderer);
    graphics.renderBackground(background);
    mouse.move();
    renderModel(mouse, graphics);
    graphics.presentScene();

    SDL_Delay(16);
}

    return 0;
}
