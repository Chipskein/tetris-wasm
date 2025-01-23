#ifndef BLOCK_H
#define BLOCK_H
typedef struct
{
    int x;
    int y;
    Color color;
    int tetranominoId;//used for collision validation
} Block;

Block *CreateBlock(int x, int y, Color color,int tetranimoId);
void DestroyBlock(Block *block);
#endif