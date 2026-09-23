#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <raylib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_SIZE 100

void SaveConfig(const char *terminal, const char *bar)
{
        chdir(".config");

    FILE *fp = fopen("FlowerLand/config", "w");

    fprintf(fp,
        "terminal=%s\n"
        "bar=%s\n",
        terminal,
        bar
    );

    fclose(fp);
}
void InputText(char *buffer, int max_len)
{
    int key = GetCharPressed();

    while (key > 0) {
        int len = strlen(buffer);

        if (key >= 32 && key <= 125 && len < max_len - 1) {
            buffer[len] = (char)key;
            buffer[len + 1] = '\0';
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
        int len = strlen(buffer);
        if (len > 0) {
            buffer[len - 1] = '\0';
        }
    }
}

int main(void)
{
    char terminal[INPUT_SIZE] = "";
    char status_bar[INPUT_SIZE] = "";

    InitWindow(1920, 1080, "Introduction to FlowerLand");
    SetTargetFPS(120);

    Rectangle button1      = { 800, 600, 320, 100 };
    Rectangle button       = { 800, 450, 320, 100 };
    Rectangle terminal_box = { 520, 320, 700, 50 };
    Rectangle status_box   = { 520, 400, 700, 50 };

    bool save = false;
    bool started = false;
    bool typing_terminal = true;
    bool typing_status_bar = false;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        bool hovering_terminal = CheckCollisionPointRec(mouse, terminal_box);
        bool hovering_status   = CheckCollisionPointRec(mouse, status_box);
        bool hovering_button   = CheckCollisionPointRec(mouse, button);
        bool hovering_button1  = CheckCollisionPointRec(mouse, button1);

        bool input_triggered = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsGestureDetected(GESTURE_TAP);

        if (input_triggered) {
            if (!started && hovering_button) {
                started = true;
            }
            else if(started && hovering_button1) {
                save = true;
                if(save) {
                        SaveConfig(terminal, status_bar);
                        save = false;
                }
            }
            else if (started) {
                if (hovering_terminal) {
                    typing_terminal   = true;
                    typing_status_bar = false;
                }
                else if (hovering_status) {
                    typing_terminal   = false;
                    typing_status_bar = true;
                }
            }
        }

        if (started) {
            if (typing_terminal) {
                InputText(terminal, INPUT_SIZE);
            }
            else if (typing_status_bar) {
                InputText(status_bar, INPUT_SIZE);
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (!started) {
            DrawText("Welcome to FlowerLand!", 100, 100, 40, DARKBLUE);

            DrawRectangleRec(
                button,
                hovering_button ? SKYBLUE : LIGHTGRAY
            );

            DrawText("Start", 915, 485, 35, DARKBLUE);
        }
        else {
            DrawText("Choose startup apps", 100, 100, 40, DARKBLUE);

            DrawText("Terminal:", 520, 285, 25, DARKBLUE);
            DrawText("Status bar:", 520, 365, 25, DARKBLUE);

            DrawRectangleRec(terminal_box, LIGHTGRAY);
            DrawRectangleRec(status_box, LIGHTGRAY);

            if (typing_terminal) {
                DrawRectangleLinesEx(terminal_box, 3.0f, BLUE);
            } else {
                DrawRectangleLinesEx(terminal_box, 1.0f, GRAY);
            }

            if (typing_status_bar) {
                DrawRectangleLinesEx(status_box, 3.0f, BLUE);
            } else {
                DrawRectangleLinesEx(status_box, 1.0f, GRAY);
            }

            DrawText(terminal, terminal_box.x + 12, terminal_box.y + 10, 30, DARKBLUE);
            DrawText(status_bar, status_box.x + 12, status_box.y + 10, 30, DARKBLUE);
            DrawRectangleRec(button1, hovering_button1 ? SKYBLUE : LIGHTGRAY);
            DrawText("Save", 920, 635, 35, DARKBLUE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
