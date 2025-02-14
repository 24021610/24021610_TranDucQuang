#ifndef GRAPHICSH
#define GRAPHICSH

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "header.h"
#include "logic.h"

    struct Graphics{
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* cell_empty, *cell_o, *cell_x, *o_win, *x_win;

    void clearRenderer(){
    SDL_RenderClear(renderer);
    }

    void prepareScene(SDL_Texture* texture){
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
        }

    void logErrorAndExit(const char* msg, const char* error){
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s : %s", msg, error);
            SDL_Quit();
        }

        SDL_Texture* loadTexture(const char* filename){
            SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
            if (texture == nullptr) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load Texture: %s", IMG_GetError());
            return texture;
        }
    void renderxy(Tictactoe game){
        SDL_Rect rect;
            rect.x = 100;
            rect.y = 100;
            rect.w = 600;
            rect.h = 400;
        (game.currentMove == X_CELL)? SDL_RenderCopy(renderer, x_win, NULL, &rect) : SDL_RenderCopy(renderer, o_win, NULL, &rect);
        presentScene();
    }

    void initSDL(){
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) logErrorAndExit("Create Window: ", SDL_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) logErrorAndExit("Create renderer: ", SDL_GetError());
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


        if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) logErrorAndExit("Load Image: ", IMG_GetError());
        cell_empty = loadTexture("cell_empty.PNG");
        cell_o = loadTexture("cell_o.PNG");
        cell_x = loadTexture("cell_x.PNG");
        o_win = loadTexture("o_win.PNG");
        x_win = loadTexture("x_win.PNG");

    }
        void presentScene(){
        SDL_RenderPresent(renderer);
        }
        void RenderTexture (SDL_Texture* texture, int x, int y){
            SDL_Rect rect;
            rect.x = x;
            rect.y = y;
            SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
            SDL_RenderCopy(renderer,texture,NULL, &rect);
            presentScene();
        }

        void render(const Tictactoe& game) {


        for (int i = 0; i < BOARD_SIZE; i++){
            for (int j = 0; j < BOARD_SIZE; j++) {
                int x = BOARD_X + j * CELL_SIZE;
                int y = BOARD_Y + i * CELL_SIZE;
                switch (game.board[i][j]) {
                    case EMPTY_CELL: RenderTexture(cell_empty, x, y); break;
                    case X_CELL: RenderTexture(cell_x, x, y); break;
                    case O_CELL: RenderTexture(cell_o, x, y); break;
                };
            }
        }

        presentScene();
    }


        void sdlQuit(){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyTexture(cell_empty);
            SDL_DestroyTexture(cell_o);
            SDL_DestroyTexture(cell_x);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();


    }
};



#endif // GRAPHICS_H_INCLUDED

