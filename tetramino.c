#include <stdio.h>
#include "raylib.h"
#include "block.h"
#include "tetramino.h"
#include "settings.h"
// Need to be in the same order as the Shape enum
// first pair is the pivot block
int tetraminoShapes[7][4][2] = {
    {{0, 0}, {-1, 0}, {1, 0}, {0, -1}},//T
    {{0, 0}, {0, -1}, {1, 0}, {1, -1}},//O
    {{0, 0}, {-1, 0}, {0, -1}, {0, -2}},//J
    {{0, 0}, {1, 0}, {0, -1}, {0, -2}},//L
    {{0, 0}, {0, 1}, {0, -1}, {0, -2}},//I
    {{0, 0}, {-1, 0}, {0, -1}, {1, -1}},//S
    {{0, 0}, {1, 0}, {0, -1}, {-1, -1}}//Z
};
Tetramino CreateTetramino(enum Shape shape, Color color, int x, int y){
    Tetramino tetramino;
    tetramino.shape=shape;
    for (int i = 0; i < 4; i++)
    {   
        Block block={
            .x=x+tetraminoShapes[shape][i][0],
            .y=y+tetraminoShapes[shape][i][1],
            .color=color
        };
        tetramino.blocks[i]=&block;
    }
    return tetramino;
}
void DrawTetramino(Tetramino *tetramino,Block *playFieldBlocks[wPlayField][hPlayField]){
    printf("Drawing tetramino\n");
    for(int i=0;i<4;i++){
        Block *block=tetramino->blocks[i];
        playFieldBlocks[block->x][block->y]=block;
    }
};