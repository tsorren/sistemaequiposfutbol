#include <stdio.h>
#include <windows.h>
#include "utils.h"


void enableANSI() {
    // Obtener el manejador de la consola
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // Habilitar el modo de salida VT100 en cmd.exe
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
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

void resetColor() {
    // ANSI code to reset text and background color to default
    printf("\033[0m");
}

void moveTo(int x, int y) {
    // ANSI code to move the cursor to a specific position
    // Positions are 1-indexed (top-left corner is (1, 1))
    printf("\033[%d;%dH", y, x);
}
/*
int main(void)
{
    enableANSI();
    clearScreen();
    moveTo(3, 2);     // Move cursor to position (5, 3)
    printf("Hello, ANSI TUI!");
    moveTo(20, 2);     // Move cursor to position (5, 3)
    printf("Hello, ANSI TUI!");

    setColor(32, 40); // Green text, Black background
    moveTo(3, 6);    // Move cursor to position (10, 6)
    printf("Press any key to exit...");

    resetColor();     // Reset colors to default

    getchar();        // Wait for a key press
    clearScreen();    // Clear the screen before exiting
    return 0;
}
*/