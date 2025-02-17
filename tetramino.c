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
    tetramino->id=rand()%1000000;
    tetramino->angle=90;
    tetramino->stopped=false;
    tetramino->shape = shape;
    tetramino->blocks = (Block**)malloc(4 * sizeof(Block*));
    for (int i = 0; i < 4; i++)
    {   
        int row_offset_shape=tetraminoShapes[shape][i][0];
        int col_offset_shape=tetraminoShapes[shape][i][1];
        int x=row+row_offset_shape % ROWS;
        int y=col+col_offset_shape % COLS;
        Block * b=CreateBlock(x,y,color,tetramino->id);
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

bool CheckBlockOut(Tetramino *tetramino,Block *playFieldBlocks[ROWS][COLS]){
    //Blockout: A piece is spawned overlapping at least one block in the playfield
    for(int i=0;i<4;i++){
        Block *block=tetramino->blocks[i];
        Block *field=playFieldBlocks[block->x][block->y];
        if(field!=NULL&&block->tetranominoId!=field->tetranominoId){
            return true;
        }
    }
    return false;
}

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
    Block * pivot=tetramino->blocks[0];
    int origin_x = pivot->x;
    int origin_y = pivot->y;
    for(int i=0;i<4;i++)
    {
        Block * currentBlock=tetramino->blocks[i];
        int old_x=currentBlock->x;
        int old_y=currentBlock->y;
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
        bool isOutOfBounds=new_x>=ROWS || new_y>=COLS || new_x<=-1 || new_y<=-1;
        if(isOutOfBounds) return;
        Block* blockAtNewPos=playFieldBlocks[new_x][new_y];
        bool hasAnyBlockAtNewPos=blockAtNewPos!=NULL;
        bool blockIsNotInSameTetranomino= hasAnyBlockAtNewPos && blockAtNewPos->tetranominoId!=currentBlock->tetranominoId;
        if(blockIsNotInSameTetranomino) return;
        currentBlock->x = new_x;
        currentBlock->y = new_y;
        playFieldBlocks[new_x][new_y]=currentBlock;
        playFieldBlocks[old_x][old_y]=NULL;
    }
    tetramino->angle = (tetramino->angle + 90) % 360;
}
void Move(Tetramino *tetramino,enum Direction direction,Block *playFieldBlocks[ROWS][COLS])
{
    //TODO:REFACTOR
    if(tetramino->stopped) return;
    switch (direction)
    {
        case LEFT:
            for(int i=0;i<4;i++){ 
                Block* currentBlock=tetramino->blocks[i];
                bool hasReachedBorderLimit=currentBlock->x-1==-1;
                if(hasReachedBorderLimit) return;
                Block* blockAtNewX=playFieldBlocks[currentBlock->x-1][currentBlock->y];
                bool hasAnyBlockAtNewX=blockAtNewX!=NULL;
                bool blockIsNotInSameTetranomino=hasAnyBlockAtNewX && currentBlock->tetranominoId!=blockAtNewX->tetranominoId;
                if((blockIsNotInSameTetranomino)) return;
            }
            for(int i=0;i<4;i++){
                playFieldBlocks[tetramino->blocks[i]->x][tetramino->blocks[i]->y]=NULL;
                tetramino->blocks[i]->x-=1;
                playFieldBlocks[tetramino->blocks[i]->x][tetramino->blocks[i]->y]=tetramino->blocks[i];
            }
            break;
        case RIGHT:
            for(int i=0;i<4;i++){ 
                Block* currentBlock=tetramino->blocks[i];
                bool hasReachedBorderLimit=currentBlock->x+1==ROWS;
                if(hasReachedBorderLimit) return;
                Block* blockAtNewX=playFieldBlocks[currentBlock->x+1][currentBlock->y];
                bool hasAnyBlockAtNewX=blockAtNewX!=NULL;
                bool blockIsNotInSameTetranomino = hasAnyBlockAtNewX && currentBlock->tetranominoId!=blockAtNewX->tetranominoId;
                if((blockIsNotInSameTetranomino)) return;
            }
            for(int i=0;i<4;i++){
                playFieldBlocks[tetramino->blocks[i]->x][tetramino->blocks[i]->y]=NULL;
                tetramino->blocks[i]->x+=1;
                playFieldBlocks[tetramino->blocks[i]->x][tetramino->blocks[i]->y]=tetramino->blocks[i];
            }
            break;
        case DOWN:
            for(int i=0;i<4;i++){
                Block* currentBlock=tetramino->blocks[i];
                bool hasReachedBorderLimit=currentBlock->y+1==COLS-1;
                if(hasReachedBorderLimit) {
                    tetramino->stopped=true;
                }
                Block* blockAtNewY=playFieldBlocks[currentBlock->x][currentBlock->y+1];
                bool hasAnyBlockAtNewY=blockAtNewY!=NULL;
                bool blockIsNotInSameTetranomino=hasAnyBlockAtNewY && currentBlock->tetranominoId!=blockAtNewY->tetranominoId;
                if(blockIsNotInSameTetranomino) {
                    tetramino->stopped=true;
                    return;
                }
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