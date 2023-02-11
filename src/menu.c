#include "raylib.h"
#include "../include/menu.h"

#define MAX_COLUMNS 20
#define NUM_FRAMES 3

static int status = 1;

static void buttons(menu_t *menu_st)
{
    BeginDrawing();
    menu_st->mousePoint = GetMousePosition();
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    DrawCircle(menu_st->mousePoint.x, menu_st->mousePoint.y, 50, RED);
    menu_st->btnAction = false;
    menu_st->sourceRec = (Rectangle){ 0, 0, (float)menu_st->button.width / 2, menu_st->button.height};
    DrawTextureRec(menu_st->button, menu_st->sourceRec, (Vector2){((GetScreenWidth() / 2) - (menu_st->button.width / 4)), (GetScreenHeight() - menu_st->button.height) / 2}, WHITE);

    if (CheckCollisionPointRec(menu_st->mousePoint, menu_st->btnBounds)) {
        menu_st->sourceRec.x += menu_st->button.width / 2;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) menu_st->btnState = 2;
        else menu_st->btnState = 1;
    }
    else menu_st->btnState = 0;
    EndDrawing();
}

static void add_back(menu_t *menu_st)
{
    BeginMode3D(menu_st->camera);
    ClearBackground(RAYWHITE);
    DrawCube((Vector3){ -16.0f, 2.5f, -15.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
    DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
    DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall
    EndMode3D();
}

int menu(menu_t *menu_st)
{
    float camera_rotation = 0.0f;
    while (status) {
        if (IsKeyPressed(KEY_ENTER))
            status = 0;
        add_back(menu_st);
        buttons(menu_st);
        camera_rotation += 0.1f;
        menu_st->camera.target = (Vector3){ 1.0f, 1.8f, camera_rotation };
        //if (camera_rotation >= 15.0f) camera_rotation = 0.0f;
    }
    return status;
}