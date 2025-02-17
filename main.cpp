#include <iostream>
#include <SDL.h>
#include "graphics.h"
#include "header.h"
#include "logic.h"



int main(int argc, char *argv[])
{
     Graphics graphics;
     ScrollingBackground background;
     object spike;
     Mouse mouse;

     graphics.initSDL();

     mouse.x=100;
     mouse.y=100;

     spike.x = 400;
     spike.y=400;

     mouse.texture = graphics.loadTexture ("Model.PNG");
     background.setTexture(graphics.loadTexture("ahaha.PNG"));
     spike.texture = graphics.loadTexture ("spike.PNG");

    SDL_Event event;
    while(true){

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) graphics.sdlQuit();

            const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
            if (currentKeyState[SDL_SCANCODE_LEFT]) mouse.turnWest();
            if(currentKeyState[SDL_SCANCODE_RIGHT]) mouse.turnEast();
            if(currentKeyState[SDL_SCANCODE_SPACE]) mouse.jump();

            SDL_RenderClear(graphics.renderer);
            graphics.renderBackground(background);
            background.scroll(1);
            renderModel(mouse, graphics);
            renderSpike(spike, graphics);
            mouse.move();
            graphics.presentScene();
            SDL_Delay(1);
        }

    }
    return 0;
}






