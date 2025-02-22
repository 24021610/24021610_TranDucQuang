#ifndef GAMEMAP
#define GAMEMAP

#include "header.h"
#include <stdfix.h>

#define GAME_MAP_X 400
#define GAME_MAP_Y 10


struct Map{
    int start_x, start_y, max_x, max_y;

    int tile[GAME_MAP_Y][GAME_MAP_X];
    char* filename;
};

struct GameMap{
    Game_object tile_mat[40];
    Map game_map;
    FILE* fp = NULL;

    void LoadMap(char* filename){
        fopen_s(&fp, filename, "rb");

        game_map.max_x = 0;
        game_map.max_y = 0;

    for (int i=0; i< GAME_MAP_Y; i++)
        {
        for(int j = 0; j<GAME_MAP_X; j++)
            {
            fscanf( fp, %d, &game_map.tile[i][j]);
            int val = game_map.tile[i][j];
                if(val >0){
                    if (j > game_map.max_x) game_map.max_x = j;
                    if (i > game_map.max_y) game_map.max_y = i;
                        }
            }
        }

        game_map.max_x = (game_map.max_x +1) * OBJECT_SIZE;
        game_map.max_y = (game_map.max_y +1) * OBJECT_SIZE;

        game_map.start_x = 0;
        game_map.start_y = 0;

        fclose(fp);
    }

    void LoadTiles (Graphics &graphics)
    {
        FILE* fp = NULL;
        char file_image[40];

        for(int i=0; i< 40; i++)
        {
            sprintf_s(file_image, "Resources/%d.PNG", i);
            fopen_s(&fp, file_image,"rb");
            if(fp == NULL) continue;
            fclose(fp);

        }
    }

};

#endif // GAMEMAP
