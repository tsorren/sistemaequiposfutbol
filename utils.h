#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#define FBLK 30
#define FRED 31
#define FGRN 32
#define FYEL 33
#define FBLU 34
#define FMAG 35
#define FCYA 36
#define FWHT 37
#define FORG 38

#define BBLK 40
#define BRED 41
#define BGRN 42
#define BYEL 43
#define BBLU 44
#define BMAG 45
#define BCYA 46
#define BWHT 47

void setupTerminal();
void clearScreen();
void showCursor();

void setColor(int , int);
void setColorRGB(int, int, int);
void resetColor();
void moveTo(int, int);

#endif // UTILS_H