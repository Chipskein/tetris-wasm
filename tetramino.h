#include "block.h"
#include "settings.h"
#include <time.h>
#include <stdlib.h>
enum Shape { T, O, J, L, I, S, Z};
typedef struct{
    Block **blocks;
    enum Shape shape;
} Tetramino;
Tetramino *CreateTetramino(enum Shape shape, Color color,int x, int y);
Tetramino *CreateRandomTetramino(int x, int y);
void DestroyTetramino(Tetramino *tetramino);
void DrawTetramino(Tetramino *tetramino,Block *playFieldBlocks[ROWS][COLS]);
int GetRandomShape(void);
Color GetRandomColor(void);
