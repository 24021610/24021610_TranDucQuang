#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "header.h"

using namespace std;

    struct Graphics{
        SDL_Window* window;
        SDL_Renderer* renderer;

    void clearRenderer(){
    SDL_RenderClear(renderer);
    }

    void logErrorAndExit(const char* msg, const char* error){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s : %s", msg, error);
            SDL_Quit();
        }
    void init(){
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) logErrorAndExit("Create Window: ", SDL_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) logErrorAndExit("Create renderer: ", SDL_GetError());
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


        if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) logErrorAndExit("Load Image: ", IMG_GetError());
    }

        void prepareScene(SDL_Texture* texture){
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);

        }

        void presentScene(){
        SDL_RenderPresent(renderer);
        }

        SDL_Texture* loadTexture(const char* filename){
            SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
            if (texture == nullptr) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load Texture: %s", IMG_GetError());
            return texture;
        }
        void RenderTexture (SDL_Texture* texture, int x, int y){
            SDL_RenderClear(renderer);
            SDL_Rect rect;
            rect.x = x;
            rect.y = y;
            SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
            SDL_RenderCopy(renderer,texture,NULL, &rect);
        }
        void sdlQuit(){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
        }
        void waitUntilKeyPressed(){
    SDL_Event e;
     while(true){
        if (( SDL_PollEvent(&e) !=0 ) && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)){
            return;
            }
            SDL_Delay(700);
    }
}
    void drawSomething() {
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH - 400;
    filled_rect.y = SCREEN_HEIGHT - 150;
    filled_rect.w = 320;
    filled_rect.h = 100;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);
}
    };
#endif // GRAPHICS_H_INCLUDED

