#ifndef BLOCK_H
#define BLOCK_H
typedef struct
{
    int x;
    int y;
    Color color;
} Block;

Block *CreateBlock(int x, int y, Color color);
void DestroyBlock(Block *block);
#endif