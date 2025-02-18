#include <iostream>
#include <SDL.h>
#include "graphics.h"
#include "header.h"
#include "logic.h"

int main(int argc, char *argv[])
{
     Graphics graphics;
     ScrollingBackground background;
     Player player;
     Spike spike;

     graphics.initSDL();

     player.x=100;
     player.y=100;
     spike.x = 900;
     spike.y = 400;



     player.texture = graphics.loadTexture ("Model.PNG");
     background.setTexture(graphics.loadTexture("Second_Stage.JPG"));
     spike.texture = graphics.loadTexture ("spike.PNG");



    SDL_Event event;
    while (true) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) graphics.sdlQuit();

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) player.jump();
        }
    }

    SDL_RenderClear(graphics.renderer);

    if (player.x > 350) {
        background.scroll(INITIAL_SPEED);
    }
    graphics.renderBackground(background);
    graphics.renderModel(player);
    graphics.renderSpike(spike);
    player.move();
    spike.move();
    graphics.presentScene();
    if (Side_Collision(player, spike)) graphics.sdlQuit();

    SDL_Delay(16);
}
    return 0;
}
