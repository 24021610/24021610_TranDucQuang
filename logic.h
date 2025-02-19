#ifndef GAMELOGIC
#define GAMELOGIC
#include <SDL.h>
#include "graphics.h"

#define INITIAL_SPEED 21
#define GRAVITY 1
#define GROUND 370
#define OBJECT_SIZE 60

struct Game_object{
    int x,y;
    SDL_Rect rect;
    SDL_Texture* texture;

    Game_object(int _x, int _y){
    x = _x;
    y = _y;
    }

    void move(){
        x -= 10;
    }

};

struct Player {
    int x, y;
    SDL_Rect rect;

    Player(int _x, int _y){
    x = _x;
    y = _y;
    }

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

bool Side_Collision(Player &player, Game_object &spike){
return (player.x + OBJECT_SIZE >= spike.x) && (player.x <= spike.x) && (player.y + OBJECT_SIZE >= spike.y) && player.y <= spike.y;
}

bool Top_Collision (Player &player, Game_object &spike){
return (player.x >= spike.x) && (player.x  <= spike.x+OBJECT_SIZE) && (player.y + OBJECT_SIZE == spike.y) && player.y <spike.y;
}
#endif // GAMELOGIC
