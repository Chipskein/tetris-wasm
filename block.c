#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "block.h"


Block *CreateBlock(int x, int y, Color color,int tetraminoId)
{
    Block *block = (Block *)malloc(sizeof(Block));
    if(block==NULL){
        printf("Memory allocation failed for Block\n");
        exit(1);
    }
    block->x = x;
    block->y = y;
    block->color = color;
    block->tetranominoId=tetraminoId;
    return block;
}

void DestroyBlock(Block *block)
{
    if (block == NULL) return;
    free(block);
    block=NULL;
}
