#include <stdio.h>
#include <windows.h>

#include "utils.h"

void enableANSI();
void setFontSize(int);
void setupTerminal();
void clearScreen();
void setColor(int, int);
void resetColor();
void moveTo(int, int);

void enableANSI() {
    // Obtener el manejador de la consola
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // Habilitar el modo de salida VT100 en cmd.exe
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void setFontSize(int fontSize)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        printf("Error: Unable to get handle to console.\n");
        return;
    }

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    if (!GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        printf("Error: Unable to get current console font info.\n");
        return;
    }

    // Establecer el tamaño de la fuente
    cfi.dwFontSize.X = fontSize;
    cfi.dwFontSize.Y = fontSize;

    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        printf("Error: Unable to set console font size.\n");
        return;
    }
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);  // Obtén la información actual del cursor
    cursorInfo.bVisible = FALSE;                      // Establece la visibilidad del cursor a FALSE
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Aplica los cambios
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);  // Obtén la información actual del cursor
    cursorInfo.bVisible = TRUE;                      // Establece la visibilidad del cursor a TRUE
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Aplica los cambios
}

void setScreenSize(int width, int height)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        printf("Error: Unable to get handle to console.\n");
        return;
    }

    // Definir el tamaño de la ventana de la consola
    SMALL_RECT windowSize = {0, 0, width - 1, height - 1};
    if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) {
        printf("Error: Unable to set window size.\n");
        return;
    }

    // Definir el tamaño del buffer de pantalla
    COORD bufferSize = {width, height};
    if (!SetConsoleScreenBufferSize(hConsole, bufferSize)) {
        printf("Error: Unable to set screen buffer size.\n");
        return;
    }

    // Verificar el tamaño actual del buffer y ventana
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        printf("Current buffer size: %d x %d\n", csbi.dwSize.X, csbi.dwSize.Y);
        printf("Current window size: %d x %d\n", csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
    } else {
        printf("Error: Unable to get console screen buffer info.\n");
    }
}

void setupTerminal()
{
    enableANSI();
    setFontSize(21);
    //setScreenSize(180, 46);
    setScreenSize(180, 60);
    hideCursor();
}

void clearScreen() {
    // ANSI code to clear the screen and move the cursor to the top-left corner
    printf("\033[2J\033[H");
}

void setColor(int textColor, int bgColor) {
    // ANSI code to set text color and background color
    // Text colors: 30: Negro - 31: Rojo - 32: Verde - 33: Amarillo - 34: Azul - 35: Magenta - 36: Cian - 37: Blanco
    // Background colors: 40: Negro - 41: Rojo - 42: Verde - 43: Amarillo - 44: Azul - 45: Magenta - 46: Cian - 47: Blanco
    printf("\033[%d;%dm", textColor, bgColor);
}

void setColorRGB(int R, int G, int B)
{
    printf("\033[38;2;%d;%d;%dm", R, G, B);
}

void resetColor() {
    // ANSI code to reset text and background color to default
    printf("\033[0m");
}

void moveTo(int x, int y) {
    // ANSI code to move the cursor to a specific position
    // Positions are 1-indexed (top-left corner is (1, 1))
    printf("\033[%d;%dH", y, x);
}