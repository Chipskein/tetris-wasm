#include <time.h>
#include <stdlib.h>
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

Tetramino *CreateTetramino(enum Shape shape, Color color, int row, int col)
{
    Tetramino *tetramino = (Tetramino*)malloc(sizeof(Tetramino));
    if (tetramino == NULL) {
        printf("Tetramino is null\n");
        exit(1);
    }
    tetramino->angle=90;
    tetramino->stopped=false;
    tetramino->shape = shape;
    tetramino->blocks = (Block**)malloc(4 * sizeof(Block*));
    for (int i = 0; i < 4; i++)
    {   
        int row_offset_shape=tetraminoShapes[shape][i][0];
        int col_offset_shape=tetraminoShapes[shape][i][1];
        Block * b=CreateBlock(row+row_offset_shape,col+col_offset_shape,color);
        if (b==NULL){
            printf("Block is null\n");
            exit(1);
        }
        tetramino->blocks[i] = b;
    }
    return tetramino;
}

void DestroyTetramino(Tetramino *tetramino){
    for (int i = 0; i < 4; i++)
    {
        DestroyBlock(tetramino->blocks[i]);
    }
    free(tetramino->blocks);
    free(tetramino);
}

Tetramino *CreateRandomTetramino(int x, int y)
{
    enum Shape shape = GetRandomShape();
    Color color = GetRandomColor();
    return CreateTetramino(shape, color, x, y);
}

void DrawTetramino(Tetramino *tetramino,Block *playFieldBlocks[ROWS][COLS])
{
    for(int i=0;i<4;i++){
        Block *block=tetramino->blocks[i];
        playFieldBlocks[block->x][block->y]=block;
    }
};

int GetRandomShape(void)
{
    return rand() % 7;
}

Color GetRandomColor(void)
{
    return (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
}
void Rotate(Tetramino *tetramino,Block *playFieldBlocks[ROWS][COLS])
{
    if(tetramino->stopped) return;
    int origin_x = tetramino->blocks[0]->x;
    int origin_y = tetramino->blocks[0]->y;
    for(int i=0;i<4;i++)
    {
        int old_x=tetramino->blocks[i]->x;
        int old_y=tetramino->blocks[i]->y;
        int rel_x = old_x - origin_x;
        int rel_y = old_y - origin_y;
        int new_rel_x, new_rel_y;
        switch (tetramino->angle)
        {
            case 0:
                new_rel_x = rel_x;
                new_rel_y = rel_y;
                break;
            case 90:
                new_rel_x = rel_y;
                new_rel_y = -rel_x;
                break;
            case 180:
                new_rel_x = -rel_x;
                new_rel_y = -rel_y;
                break;
            case 270:
                new_rel_x = -rel_y;
                new_rel_y = rel_x;
                break;
            default:
                new_rel_x = rel_x;
                new_rel_y = rel_y;
                break;
        }
        int new_x = origin_x + new_rel_x;
        int new_y = origin_y + new_rel_y;
        //check collision with other blocks if has collide return
        tetramino->blocks[i]->x = new_x;
        tetramino->blocks[i]->y = new_y;
        playFieldBlocks[new_x][new_y]=tetramino->blocks[i];
        playFieldBlocks[old_x][old_y]=NULL;
    }
    tetramino->angle = (tetramino->angle + 90) % 360;
}
void Move(Tetramino *tetramino,enum Direction direction,Block *playFieldBlocks[ROWS][COLS])
{
    if(tetramino->stopped) return;
    switch (direction)
    {
        case LEFT:
            for(int i=0;i<4;i++){ 
                if(tetramino->blocks[i]->x-1==-1) return;                
            }
            for(int i=0;i<4;i++){
                playFieldBlocks[tetramino->blocks[i]->x][tetramino->blocks[i]->y]=NULL;
                tetramino->blocks[i]->x-=1;
                playFieldBlocks[tetramino->blocks[i]->x][tetramino->blocks[i]->y]=tetramino->blocks[i];
            }
            break;
        case RIGHT:
            for(int i=0;i<4;i++){ 
                if(tetramino->blocks[i]->x+1==ROWS) return;                
            }
            for(int i=0;i<4;i++){
                playFieldBlocks[tetramino->blocks[i]->x][tetramino->blocks[i]->y]=NULL;
                tetramino->blocks[i]->x+=1;
                playFieldBlocks[tetramino->blocks[i]->x][tetramino->blocks[i]->y]=tetramino->blocks[i];
            }
            break;
        case DOWN:
            for(int i=0;i<4;i++){ 
                if(tetramino->blocks[i]->y+1==COLS) {
                    tetramino->stopped=true;
                    return;
                }
                //check collision with other blocks if has collide set stopped to true
            }
            for(int i=0;i<4;i++){
                playFieldBlocks[tetramino->blocks[i]->x][tetramino->blocks[i]->y]=NULL;
                tetramino->blocks[i]->y+=1;
                playFieldBlocks[tetramino->blocks[i]->x][tetramino->blocks[i]->y]=tetramino->blocks[i];
            }
            break;
    
    default:
        break;
    }

}