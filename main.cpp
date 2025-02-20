#include <iostream>
#include <SDL.h>
#include "graphics.h"
#include "header.h"
#include "logic.h"

int main(int argc, char *argv[])
{
     Graphics graphics;
     ScrollingBackground background;
     Player player(0,370);
     Game_object spike(900,370);
     Game_object square(3000,370);

     graphics.initSDL();

     player.texture = graphics.loadTexture ("Model.PNG");
     background.setTexture(graphics.loadTexture("Second_Stage.JPG"));
     spike.texture = graphics.loadTextureFromSurface ("spike.PNG");
     square.texture = graphics.loadTexture("square.PNG");



    SDL_Event event;
    while (true) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) graphics.sdlQuit();

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) player.jump();
        }
    }

    SDL_RenderClear(graphics.renderer);

    if (player.x > 225) {
        background.scroll(5);
        spike.move();
    }
    graphics.renderBackground(background);
    graphics.renderModel(player);
    graphics.renderSpike(spike);
    graphics.renderSpike(square);
    player.move();
    square.move();
    graphics.presentScene();
    if (Side_Collision(player, spike)) graphics.sdlQuit();
    if (Top_Collision(player, square)){
        while (player.x<=square.x && player.x+OBJECT_SIZE >= square.x){
            player.ground = square.y;
        }
    }

    SDL_Delay(16);
}
    return 0;
}
