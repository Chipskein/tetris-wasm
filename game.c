#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "block.h"
#include "tetramino.h"
#include "settings.h"
void UpdateDrawFrame(void);
const Color DEFAULT_BACKGROUND_COLOR=GRAY;
Block *playFieldBlocks[ROWS][COLS];
Tetramino *tetramino;
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
int main(void)
{
    srand(time(NULL)); 
    InitWindow(screenWidth, screenHeight, "CTetris");
    tetramino=CreateRandomTetramino(ROWS/2-1,2);
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif
    CloseWindow();
    return 0;
}


void DrawPlayField(void)
{
    int startX = (screenWidth - wPlayField) / 2;
    int startY = (screenHeight - hPlayField) / 2;
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            Block * block=playFieldBlocks[row][col];
            if (block != NULL)
            {
                DrawRectangle(startX+row*tileSize, startY+col*tileSize, tileSize-1, tileSize-1, block->color);
            }
            else
            {
                DrawRectangle(startX+row*tileSize, startY+col*tileSize, tileSize-1, tileSize-1, DEFAULT_BACKGROUND_COLOR);
            }
        }
    }
}


void HandleInput(Tetramino *t,Block *playFieldBlocks[ROWS][COLS])
{
    if (IsKeyPressed(KEY_LEFT)) Move(t,LEFT,playFieldBlocks);
    if (IsKeyPressed(KEY_RIGHT)) Move(t,RIGHT,playFieldBlocks);
    if (IsKeyPressed(KEY_DOWN)) Move(t,DOWN,playFieldBlocks);
    if (IsKeyPressed(KEY_SPACE)) Rotate(t,playFieldBlocks);
}
void UpdateDrawFrame(void)
{
    HandleInput(tetramino,playFieldBlocks);
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTetramino(tetramino,playFieldBlocks);
        DrawPlayField();
    EndDrawing();

}