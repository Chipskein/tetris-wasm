#include <stdlib.h>
#include "raylib.h"
#include "block.h"


Block *CreateBlock(int x, int y, Color color)
{
    Block *block = (Block *)malloc(sizeof(Block));
    block->x = x;
    block->y = y;
    block->color = color;
    return block;
}

void DestroyBlock(Block *block)
{
    if (block == NULL)
    {
        return;
    }
    free(block);
}
