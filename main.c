#include <stdio.h>
#include "raylib/raylib.h"
#include "memory_manager.c"
// #include "gaussian_blur.c"

int main()
{
    memory_manager_init();
    int* array = memory_manager_int_alloc(3);

    int* array2 = memory_manager_int_alloc(2);

    for (int i = 0; i < 3; ++i)
        array[i] = 2;
    
    for (int i = 0; i < 3; ++i)
        printf("value array at %d = %d\n", i, array[i]);

    memory_manager_int_dealloc(array);
    memory_manager_int_dealloc(array2);


    // InitWindow(1280, 720, "raylib_ui");
    // SetTargetFPS(60);

    // int rectangle_pixels = sizeof(gaussian_boxes) / sizeof(gaussian_boxes[0]);
    // int color_blue = ColorToInt(BLUE);
    // Image image_blue = GenImageColor(width, height, BLUE);

 
    // Texture texture_blue_blur = LoadTextureFromImage(image_blue);

    // while (!WindowShouldClose())
    // {
    //     gaussian_blur_boxes(1, 3, gaussian_boxes);

    //     BeginDrawing();
    //         ClearBackground(WHITE);
    //         // DrawRectangleGradientH(110, 110, 200, 200, DARKGRAY, BLACK);
    //         // DrawRectangle(100, 100, 200, 200, BLUE);
    //     EndDrawing();
    // }

    // UnloadImage(image_blue);
    // UnloadTexture(texture_blue_blur);
    // CloseWindow();
    memory_manager_destroy();
    return 0;
}