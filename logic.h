#ifndef GAMELOGIC
#define GAMELOGIC
#include <SDL.h>
#include "graphics.h"

#define INITIAL_SPEED 10
#define GRAVITY 5
#define GROUND 330
#define OBJECT_SIZE 60

bool inside(int x, int y, SDL_Rect &rect){
    return (x > rect.x) && (y>rect.y) && (x < rect.x + rect.w) && (y< rect.y + rect.h);
}

bool overlap(SDL_Rect &r1, SDL_Rect &r2){
return inside(r1.x, r1.y, r2) || inside(r1.x + r1.w, r1.y, r2) ||
            inside(r1.x, r1.y+r1.h, r2) || inside(r1.x+r1.w, r1.y+r1.h, r2);
}


struct object{
    SDL_Rect rect;
    SDL_Texture* texture;
    int x,y;
};

struct Mouse {
    int x, y;
    SDL_Rect rect;

    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;
    int gravity = GRAVITY;
    int ground = GROUND;
    SDL_Texture* texture;

    void loadTexture(SDL_Texture* _texture){
        texture = _texture;
    }

    void move() {
        x += dx;
        y += dy;
        dx=0;

        if (y >= ground) {
            y = ground;
            dy = 0;
        } else {
            dy += gravity;
        }
    }

    void jump() {
        dx = 0;
        dy -=speed;
    }

    void turnWest() {
        dy = 0;
        dx = -speed;
    }
    void turnEast() {
        dy = 0;
        dx = speed;
    }

};
#endif // GAMELOGIC
