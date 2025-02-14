#ifndef GAMELOGIC
#define GAMELOGIC
#include <iostream>
#include <SDL.h>
#include "graphics.h"
#include "header.h"


struct Tictactoe{
    char board[BOARD_SIZE][BOARD_SIZE];
    char nextMove = O_CELL;
    char currentMove;

void init(){
    for(int i=0; i< BOARD_SIZE; i++){
        for (int j = 0; j <BOARD_SIZE; j++){
            board[i][j] = EMPTY_CELL;
        }
    }
}

void move(int row, int col){
    if (row >=0 && col >=0 && row<= BOARD_SIZE && col <= BOARD_SIZE){
        if (board[row][col] != EMPTY_CELL) nextMove = currentMove;
        board[row][col] = nextMove;
        currentMove = nextMove;
        nextMove = (nextMove == O_CELL)? X_CELL : O_CELL;
    }
}
void newgame(){
    memset(board, ' ', sizeof(board));
}

bool winCondition(){
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            if (board[i][j] == EMPTY_CELL) continue;


                    for(int d=0; d<4; d++){
                        int dx = directions[d][0];
                        int dy = directions[d][1];
                        int cnt=1;

                        for(int step =1; step<5; step++){
                            int x = i + step*dx;
                            int y = j+ step*dy;
                            if(x >= BOARD_SIZE || y<0 || y>= BOARD_SIZE || board[x][y] != currentMove) break;
                            cnt ++;
                        }
                        if (cnt==5) {
                        return true;
                        break;
                    }
                    }
                }

        }
        return false;
    }
};

#endif // LOGIC
