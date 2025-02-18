#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "header.h"
#include "logic.h"


struct ScrollingBackground{
    int scrollingOffset =0;
    SDL_Texture* texture;
    int width, height;

    void scroll(int distance){
        scrollingOffset -=distance;
        if (scrollingOffset < 0) scrollingOffset = width;
    }

    void setTexture (SDL_Texture* _texture){
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

};

struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;

	void logErrorAndExit(const char* msg, const char* error){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s : %s", msg, error);
            SDL_Quit();
        }

	void initSDL(){
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
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        }

    SDL_Texture* loadTexture(const char* filename){
            SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
            if (texture == nullptr) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load Texture: %s", IMG_GetError());
            return texture;
        }

    void renderTexture(SDL_Texture *texture, int x, int y){
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void renderBackground(const ScrollingBackground& background) {
        renderTexture(background.texture, background.scrollingOffset, 0);
        renderTexture(background.texture, background.scrollingOffset - background.width, 0);
    }

    void renderModel(const Player& player){
    SDL_Rect rect;
    rect.x = player.x;
    rect.y = player.y;
    SDL_QueryTexture(player.texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, player.texture, NULL, &rect );
}

    void renderSpike(const Spike& spike){
    SDL_Rect rect;
    rect.x = spike.x;
    rect.y = spike.y;
    SDL_QueryTexture(spike.texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, spike.texture, NULL, &rect );
    }



    void sdlQuit(){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();

    }
};



#endif // _GRAPHICS__H




