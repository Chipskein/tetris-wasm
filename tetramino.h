#include "block.h"
#include "settings.h"
#include <time.h>
#include <stdlib.h>
enum Shape { T, O, J, L, I, S, Z};
enum Direction {LEFT,RIGHT,DOWN};
typedef struct{
    Block **blocks;
    enum Shape shape;
    bool stopped;
    int angle;//0 90 180 270
    int id; //random id to verify stuff
} Tetramino;
Tetramino *CreateTetramino(enum Shape shape, Color color,int x, int y);
Tetramino *CreateRandomTetramino(int x, int y);
void DestroyTetramino(Tetramino *tetramino);
bool CheckBlockOut(Tetramino *tetramino,Block *playFieldBlocks[ROWS][COLS]);
void DrawTetramino(Tetramino *tetramino,Block *playFieldBlocks[ROWS][COLS]);
int GetRandomShape(void);
Color GetRandomColor(void);
void Rotate(Tetramino *tetramino,Block *playFieldBlocks[ROWS][COLS]);
void Move(Tetramino *tetramino,enum Direction direction,Block *playFieldBlocks[ROWS][COLS]);
