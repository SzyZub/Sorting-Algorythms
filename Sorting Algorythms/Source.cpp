#include "raylib.h"
#include <iostream>
#define SCREENH 864
#define SCREENW 1152
#define FONTS 40

typedef enum EnProgFlag {
    EMenu = 0,
    EMode,
    EBasic,
    EDem
};

typedef enum EnAlg {
    ESelection = 0,
    EBubble,
    EInsertion,
    EMerge,
    ERadix,
    EQuick,
    ECycle,
    EShell,
    EBogo,
    EStalin,
    ECounting,
    EGnome
};

typedef struct StrMousePos {
    int x, y;
};

void _DrawRectWithText(int x, int y, int w, int h, int b, const char t[]) {
    DrawRectangle(x, y, w, h, WHITE);
    DrawRectangle(x + b, y + b, w - 2*b, h - 2*b, BLACK);
    DrawText(t, (w - MeasureText(t, FONTS))/2 + x, (h - FONTS)/2 + y, FONTS, WHITE);
}

class MainClass {
    EnProgFlag flag;
    EnAlg alg;
public:
    MainClass() {
        InitWindow(SCREENW, SCREENH, "SortingAlgorythms");
        SetTargetFPS(500);
        SetMouseCursor(4);
        flag = EMenu;
    }
    void _mainLoop() {
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(BLACK);
            switch (flag) {
            case EMenu:
                _menu();
                break;
            case EMode:
                _mode();
                break;
            case EBasic:
                _basic();
                break;
            }
            EndDrawing();
        }
    }
    StrMousePos _getMousePos() {
        return { (int)GetTouchX(), (int)GetTouchY() };
    }
    void _menu() {
        _DrawRectWithText(0, 0, SCREENW/2, SCREENH/6, 4, "Selection Sort");
        _DrawRectWithText(SCREENW / 2, 0, SCREENW / 2, SCREENH / 6, 4, "Bubble Sort");
        _DrawRectWithText(0, SCREENH / 6, SCREENW / 2, SCREENH / 6, 4, "Insertion Sort");
        _DrawRectWithText(SCREENW / 2, SCREENH/6, SCREENW / 2, SCREENH / 6, 4, "Merge Sort");
        _DrawRectWithText(0, SCREENH * 2 / 6, SCREENW / 2, SCREENH / 6, 4, "Radix Sort");
        _DrawRectWithText(SCREENW/2, SCREENH * 2 / 6, SCREENW / 2, SCREENH / 6, 4, "Quick Sort");
        _DrawRectWithText(0, SCREENH * 3 / 6, SCREENW / 2, SCREENH / 6, 4, "Cycle Sort");
        _DrawRectWithText(SCREENW / 2, SCREENH * 3 / 6, SCREENW / 2, SCREENH / 6, 4, "Shell Sort");
        _DrawRectWithText(0, SCREENH * 4 / 6, SCREENW / 2, SCREENH / 6, 4, "Bogo Sort");
        _DrawRectWithText(SCREENW / 2, SCREENH * 4 / 6, SCREENW / 2, SCREENH / 6, 4, "Stalin Sort(by deletion)");
        _DrawRectWithText(0, SCREENH * 5 / 6, SCREENW / 2, SCREENH / 6, 4, "Counting Sort");
        _DrawRectWithText(SCREENW/2, SCREENH * 5 / 6, SCREENW / 2, SCREENH / 6, 4, "Gnome Sort");
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StrMousePos temp = _getMousePos();
            flag = EMode;
            if (temp.x >= SCREENW / 2) {
                switch (6 * temp.y/SCREENH) {
                case 0:
                    alg = EBubble;
                    break;
                case 1:
                    alg = EMerge;
                    break;
                case 2:
                    alg = EQuick;
                    break;
                case 3:
                    alg = EShell;
                    break;
                case 4:
                    alg = EStalin;
                    break;
                case 5:
                    alg = EGnome;
                    break;
                }
            }
            else {
                switch (6 * temp.y / SCREENH) {
                case 0:
                    alg = ESelection;
                    break;
                case 1:
                    alg = EInsertion;
                    break;
                case 2:
                    alg = ERadix;
                    break;
                case 3:
                    alg = ECycle;
                    break;
                case 4:
                    alg = EBogo;
                    break;
                case 5:
                    alg = ECounting;
                    break;
                }
            }
        }
    }
    void _mode() {
        _DrawRectWithText(0, 0, SCREENW, SCREENH/3, 4, "Basic explanation");
        _DrawRectWithText(0, SCREENH / 3, SCREENW, SCREENH / 3, 4, "Demonstration");
        _DrawRectWithText(0, SCREENH * 2/ 3, SCREENW, SCREENH / 3, 4, "Go Back");
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StrMousePos temp = _getMousePos();
            switch (3 * temp.y / SCREENH) {
            case 0:
                flag = EBasic;
                break;
            case 1:
                flag = EDem;
                break;
            case 2:
                flag = EMenu;
                break;
            }
        }

    }
    void _basic() {
        static Texture2D temp;
        if (!IsTextureReady(temp)) {
            switch (alg) {
            case ESelection:
                temp = LoadTexture("Explanations/Selection sort.png");
                break;
            case EBubble:
                temp = LoadTexture("Explanations/Bubble sort.png");
                break;
            case EInsertion:
                temp = LoadTexture("Explanations/Insertion sort.png");
                break;
            case EMerge:
                temp = LoadTexture("Explanations/Merge sort.png");
                break;
            case ERadix:
                temp = LoadTexture("Explanations/Radix sort.png");
                break;
            case EQuick:
                temp = LoadTexture("Explanations/Quick sort.png");
                break;
            case ECycle:
                temp = LoadTexture("Explanations/Cycle sort.png");
                break;
            case EShell:
                temp = LoadTexture("Explanations/Shell sort.png");
                break;
            case EBogo:
                temp = LoadTexture("Explanations/Bogo sort.png");
                break;
            case EStalin:
                temp = LoadTexture("Explanations/Stalin sort.png");
                break;
            case ECounting:
                temp = LoadTexture("Explanations/Counting sort.png");
                break;
            case EGnome:
                temp = LoadTexture("Explanations/Gnome sort.png");
                break;
            }
        }
        DrawTexture(temp, 0, 0, WHITE);
        _DrawRectWithText(0, 764, SCREENW / 2, 100, 4, "This algorythm menu");
        _DrawRectWithText(SCREENW / 2, 764, SCREENW / 2, 100, 4, "Main Menu");
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StrMousePos mouse = _getMousePos();
            if (mouse.y >= 764) {
                UnloadTexture(temp);
                temp.id = 0;
                switch (mouse.x / (SCREENW / 2)) {
                case 0:
                    flag = EMode;
                    break;
                case 1:
                    flag = EMenu;
                    break;
                }
            }
        }
    }
};

int main(void)
{
    MainClass mainClass;
    mainClass._mainLoop();
    CloseWindow();
    return 0;
}