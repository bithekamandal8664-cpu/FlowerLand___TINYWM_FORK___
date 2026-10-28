#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <raylib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_SIZE 100
#define DEEPBLUE  (Color){35, 78, 128, 255}
#define CLOUDBLUE (Color){220, 235, 250, 255}
#define BABYBLUE  (Color){184, 216, 248, 255}
#define DrawCText(text, x, y, size, color) \
    DrawTextEx(CFont, text, (Vector2){x, y}, size, 1, color)

void SaveConfig(const char *terminal, const char *bar, const char *wallpaper)
{
        chdir(".config");

    FILE *fp = fopen("FlowerLand/config", "w");

    fprintf(fp,
        "terminal=%s\n"
        "bar=%s\n"
	"wallpaper=%s\n",
        terminal,
        bar,
	wallpaper
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
    char wallpaper[INPUT_SIZE]  = "";

    InitWindow(1920, 1080, "Introduction to FlowerLand");
    SetTargetFPS(120);

    Font CFont = LoadFont("assets/Comfortaa.ttf");

    Rectangle button1      = { 800, 600, 320, 100 };
    Rectangle button       = { 800, 450, 320, 100 };
    Rectangle terminal_box = { 520, 320, 700, 50 };
    Rectangle status_box   = { 520, 400, 700, 50 };
    Rectangle wallpaper_box = {520, 480, 700, 50 };

    bool save = false;
    bool started = false;
    bool typing_terminal = true;
    bool typing_status_bar = false;
    bool typing_wallpaper = false;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        bool hovering_terminal = CheckCollisionPointRec(mouse, terminal_box);
        bool hovering_status   = CheckCollisionPointRec(mouse, status_box);
        bool hovering_button   = CheckCollisionPointRec(mouse, button);
        bool hovering_button1  = CheckCollisionPointRec(mouse, button1);
	bool hovering_wallpaper  = CheckCollisionPointRec(mouse, wallpaper_box);

        bool input_triggered = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsGestureDetected(GESTURE_TAP);

        if (input_triggered) {
            if (!started && hovering_button) {
                started = true;
            }
            else if(started && hovering_button1) {
                save = true;
                if(save) {
                        SaveConfig(terminal, status_bar, wallpaper);
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
		else if (hovering_wallpaper) {
		    typing_terminal = false;
		    typing_status_bar = false;
		    typing_wallpaper = true;
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
	    else if (typing_wallpaper) {
		InputText(wallpaper, INPUT_SIZE);
	    }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (!started) {
            DrawCText("Welcome to FlowerLand!", 100, 100, 40, DARKBLUE);

            DrawRectangleRec(
                button,
                hovering_button ? SKYBLUE : LIGHTGRAY
            );

            DrawCText("Start", 915, 485, 35, DARKBLUE);
	    DrawCircle(1890, 1060, 275, CLOUDBLUE);
	    DrawCircle(1880, 1050, 200, BABYBLUE);
	    DrawCircle(1870, 1040, 125, DEEPBLUE);
        }
        else {
            DrawCText("Choose startup apps", 100, 100, 40, DARKBLUE);

            DrawCText("Terminal:", 520, 285, 25, DARKBLUE);
            DrawCText("Status bar:", 520, 365, 25, DARKBLUE);
	    DrawCText("wallpaper:", 520, 445, 25, DARKBLUE);

            DrawRectangleRec(terminal_box, LIGHTGRAY);
            DrawRectangleRec(status_box, LIGHTGRAY);
	    DrawRectangleRec(wallpaper_box, LIGHTGRAY);

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

	    if (typing_wallpaper) {
		DrawRectangleLinesEx(wallpaper_box, 3.0f, BLUE);
	    } else {
		DrawRectangleLinesEx(wallpaper_box, 1.0f, GRAY);
	    }

            DrawText(terminal, terminal_box.x + 12, terminal_box.y + 10, 30, DARKBLUE);
            DrawText(status_bar, status_box.x + 12, status_box.y + 10, 30, DARKBLUE);
	    DrawText(wallpaper, wallpaper_box.x + 12, wallpaper_box.y +10, 30, DARKBLUE);

            DrawRectangleRec(button1, hovering_button1 ? SKYBLUE : LIGHTGRAY);
            DrawCText("Save", 920, 635, 35, DARKBLUE);
	    DrawCircle(1890, 1060, 275, CLOUDBLUE);
	    DrawCircle(1880, 1050, 200, BABYBLUE);
	    DrawCircle(1870, 1040, 125, DEEPBLUE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
