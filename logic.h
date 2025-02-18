#ifndef GAMELOGIC
#define GAMELOGIC
#include <SDL.h>
#include "graphics.h"

#define INITIAL_SPEED 7
#define GRAVITY 1
#define GROUND 370
#define OBJECT_SIZE 60

bool inside(int x, int y, SDL_Rect &rect){
    return (x > rect.x) && (y>rect.y) && (x < rect.x + rect.w) && (y< rect.y + rect.h);
}

struct Spike{
    int x,y;
    SDL_Rect rect;
    SDL_Texture* texture;

    void move(){
        x -= INITIAL_SPEED/3;
    }

};

struct Player {
    int x, y;
    SDL_Rect rect;

    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;
    int gravity = GRAVITY;
    int ground = GROUND;
    bool isJumping = false;
    SDL_Texture* texture;

    void loadTexture(SDL_Texture* _texture){
        texture = _texture;
    }

    void move() {
    if(x >350) speed=0;

    dy += gravity;
    y += dy;
    x += speed;
    rect.x=x;
    rect.y=y;

     if(y < ground) {
            dy += gravity;
        }
        else {
            y = ground;
            dy = 0;
        }
}
void jump() {
    if (y == ground) {
        dy = -23;
    }
}
};

bool Side_Collision(Player &player, Spike &spike){
return (player.x + OBJECT_SIZE >= spike.x) && (player.y + OBJECT_SIZE >= spike.y);
}
#endif // GAMELOGIC
