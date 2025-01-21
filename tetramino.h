#include "block.h"
#include "settings.h"
enum Shape { T, O, J, L, I, S, Z};
typedef struct{
    Block *blocks[4];
    enum Shape shape;
} Tetramino;
Tetramino CreateTetramino(enum Shape shape, Color color,int x, int y);
void DrawTetramino(Tetramino *tetramino,Block *playFieldBlocks[wPlayField][hPlayField]);
