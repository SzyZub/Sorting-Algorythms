#include "raylib.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
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
    ECocktail,
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

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
bool _show(int arr[], int x, int y) {
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < 100; i++) {
        DrawRectangle(30 + 11 * i, 664 - (arr[i] * 5), 10, arr[i] * 5, (x == i ? RED : y == i ? GREEN : WHITE));
    }
    DrawText("You can press left mouse button to exit", 200, 764, FONTS, WHITE);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || WindowShouldClose()) {
        return true;
    }
    EndDrawing();
    std::chrono::milliseconds dura(12);
    std::this_thread::sleep_for(dura);
    return false;
}
void selectionSort(int arr[]) {
    int min, i ,j;
    for (i = 0; i < 99; i++) {
        min = i;
        for (j = i + 1; j < 100; j++) {
            if (arr[j] < arr[min]) {
                min = j;
                _show(arr, j, min);
            }                
        }
        if (min != i) {
            swap(arr[min], arr[i]);
            _show(arr, min, i);
        }          
    }
}
void bubbleSort(int arr[])
{
    int i, j;
    bool swapped;
    for (i = 0; i < 99; i++) {
        swapped = false;
        for (j = 0; j < 99 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                _show(arr, j, j+1);
            }
        }
        if (swapped == false)
            break;
    }
}
void insertionSort(int arr[])
{
    int i = 1, key, j;
    for (i; i < 100;) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            _show(arr, j, j + 1);
        }
        arr[j + 1] = key;
        i++;
    }
}
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left; 
    int j = mid + 1; 
    int k = left; 
    while (i <= mid && j <= right) {
        _show(arr, i, j);
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        temp[k] = arr[i];
        _show(arr, i, k);
        i++;
        k++;
    }
    while (j <= right) {
        temp[k] = arr[j];
        _show(arr, j, k);
        j++;
        k++;
    }
    for (int i = left; i <= right; i++) {
        arr[i] = temp[i];
        _show(arr, i, i);
    }
}
void mergeSort(int arr[]) {
    int temp[100]; 
    int cur = 1;
    int left = 0;
    for (; cur <= 99;) {
        for (; left < 99; left += 2 * cur) {
            int mid = std::min(left + cur - 1, 99);
            int right = std::min(left + 2 * cur - 1, 99);
            merge(arr, temp, left, mid, right);
        }
        left = 0;
        cur = 2 * cur;
    }
}
void CocktailSort(int arr[])
{
    bool swapped = true;
    int start = 0;
    int end = 100 - 1;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                _show(arr, i, i + 1);
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                _show(arr, i, i+1);
                swapped = true;
            }
        }
        ++start;
    }
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);           
        }
        _show(arr, i, j);
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(int arr[]) {
    int stack[99] = { 0, 99 };
    int top = 1;
    int l = 0, h = 99;
    while (top >= 0) {
        h = stack[top--];
        l = stack[top--];
        int p = partition(arr, l, h);
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
            _show(arr, top, p - 1);
        }
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
            _show(arr, top, h);
        }
    }
}
void cycleSort(int arr[])
{
    int cycle_start = 0;
    int item;
    int pos;
    for (; cycle_start <= 98;)
    {
        item = arr[cycle_start];
        pos = cycle_start;
        for (int i = cycle_start + 1; i < 100; i++) {
            if (arr[i] < item)
                pos++;
        }          
        if (pos == cycle_start) {
            cycle_start++;
            continue;
        }          
        while (item == arr[pos]) {
            pos += 1;
        }          
        if (pos != cycle_start)
        {
            swap(item, arr[pos]);
        }
        while (pos != cycle_start)
        {
            pos = cycle_start;
            for (int i = cycle_start + 1; i < 100; i++)
                if (arr[i] < item) {
                    pos += 1;
                    _show(arr, i, pos);
                }                   
            while (item == arr[pos]) {
                pos += 1;
                _show(arr, pos, pos);
            }              
            if (item != arr[pos])
            {
                swap(item, arr[pos]);
            }
            _show(arr,cycle_start, pos);
        }
        cycle_start++;
    }
}
void shellSort(int arr[]) {
    int gap = 100 / 2;
    for (; gap > 0; ) {
        for (int i = gap; i < 100; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                _show(arr, j, j-gap);
            }
            arr[j] = temp;
            _show(arr, j, i);
        }
        gap /= 2;
        _show(arr, -1, -1);
    }
}
void stalinSort(int arr[]) {
    int last = 0;
    int index = 1;   
    int i = 1;
    for (; i < 100; ) {
        if (arr[i] >= arr[last]) {
            arr[last] = arr[i]; 
            last = i;
        }
        else {
            arr[i] = -1;
        }
        i++;
        _show(arr, i, last);
    }
}
void bogoSort(int arr[]) {  
    while (!_show(arr, -1, -1)) {
        for (int i = 0; i < 100; i++) {
            std::chrono::milliseconds dura(3);
            std::this_thread::sleep_for(dura);
            swap(arr[i], arr[std::rand() % 100]);
        }
    }
}
void countSort(int arr[])
{
    int M = 0;
    for (int i = 0; i < 100; i++)
        M = (M > arr[i] ? M : arr[i]);
    int countArr[100] = { 0 };
    for (int i = 0; i < 100; i++) {
        countArr[arr[i]]++;
        _show(countArr, i, i);
    }    
    for (int i = 1; i <= M; i++) {
        countArr[i] += countArr[i - 1];
        _show(countArr, i, i - 1);
    }
    int outPut[100];
    for (int i = 99; i >= 0; i--)
    {
        outPut[countArr[arr[i]] - 1] = arr[i];
        countArr[arr[i]]--;
        _show(outPut, i, i - 1);
    }
    for (int i = 0; i < 100; i++) {
        arr[i] = outPut[i];
    }
}
void gnomeSort(int arr[])
{
    int index = 0;
    while (index < 100) {
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1]) {
            _show(arr, index, index - 1);
            index++;
        }         
        else {
            swap(arr[index], arr[index - 1]);
            _show(arr, index, index - 1);
            index--;
        }
    }
    return;
}
void _DrawRectWithText(int x, int y, int w, int h, int b, const char t[]) {
    DrawRectangle(x, y, w, h, WHITE);
    DrawRectangle(x + b, y + b, w - 2*b, h - 2*b, BLACK);
    DrawText(t, (w - MeasureText(t, FONTS))/2 + x, (h - FONTS)/2 + y, FONTS, WHITE);
}
class Generator {
    void (*func) (int[]);
    EnAlg flag;
public:
    int arr[100];
    Generator(EnAlg f) {
        for (int i = 0; i < 100; i++) {
            arr[i] = i;
        }
        flag = f;
        std::random_shuffle(&arr[0], &arr[99]);
        switch (f) {
        case ESelection:
            func = &selectionSort;
            break;
        case EBubble:
            func = &bubbleSort;
            break;
        case EInsertion:
            func = &insertionSort;
            break;
        case EMerge:
            func = &mergeSort;
            break;
        case ECocktail:
            func = &CocktailSort;
            break;
        case EQuick:
            func = &quickSort;
            break;
        case ECycle: 
            func = &cycleSort;
            break;
        case EShell:
            func = &shellSort;
            break;
        case EBogo:
            func = &bogoSort;
            break;
        case EStalin :
            func = &stalinSort;
            break;
        case ECounting:
            func = &countSort;
            break;
        case EGnome:
            func = &gnomeSort;
            break;
        }
    }
    void _sort() {
        func(arr);
    }   
};
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
            case EDem:
                _dem();
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
        _DrawRectWithText(0, SCREENH * 2 / 6, SCREENW / 2, SCREENH / 6, 4, "Cocktail Sort");
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
                    alg = ECocktail;
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
            case ECocktail:
                temp = LoadTexture("Explanations/Cocktail sort.png");
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
    void _dem() {
        Generator gen(alg);
        srand(time(0));
        gen._sort();
        _show(gen.arr, -1, -1);
        std::chrono::milliseconds dura(1000);
        std::this_thread::sleep_for(dura);      
        flag = EMenu;
    }
};

int main(void)
{
    MainClass mainClass;
    mainClass._mainLoop();
    CloseWindow();
    return 0;
}