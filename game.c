#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "block.h"
#include "tetramino.h"
#include "settings.h"
void UpdateDrawFrame(void);
const Color DEFAULT_BACKGROUND_COLOR=GRAY;
Block *playFieldBlocks[wPlayField][hPlayField];
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
int main(void)
{
    
    InitWindow(screenWidth, screenHeight, "CTetris");
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
    for (int x = 0; x < wPlayField; x += tileSize)
    {
        for (int y = 0; y < hPlayField; y += tileSize)
        {
            Block * block=playFieldBlocks[x][y];
            if (block != NULL)
            {
                DrawRectangle(startX+x, startY+y, tileSize-1, tileSize-1, block->color);
            }
            else
            {
                DrawRectangle(startX+x, startY+y, tileSize-1, tileSize-1, DEFAULT_BACKGROUND_COLOR);
            }
        }
    }
}



void UpdateDrawFrame(void)
{
    BeginDrawing();
        ClearBackground(BLACK);
        DrawPlayField();
    EndDrawing();

}