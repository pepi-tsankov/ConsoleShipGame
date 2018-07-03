#ifndef __SCREEN_HPP_P__
#define __SCREEN_HPP_P__
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "../GameItems/Entity.hpp"
class Screen{
    unsigned char bufferA[100][30];
    unsigned char colorBufferA[100][30];
    unsigned char bufferB[100][30];
    unsigned char colorBufferB[100][30];
    int width;
    int height;
    int chWidth;
    int chHeight;
    HWND cHandle;
    HANDLE hStdout;
    bool totalRedraw;
    DWORD nFont;

    static Screen& getInstance();
    Screen();
    Screen(Screen& a);
    Screen& operator=(Screen& rhs);
    bool calibrateSize();
    void makeCursorInvisible();
    void printDifferences();
    bool checkConsoleSize();
    void totalPrint();
    void clearScreen();
    void moveCursor(int x,int y);
    void clearCell_priv(int x,int y);
    void setCell_priv(int x,int y, char chr,char color);
public:
    static void write(int x,int y,const char* str,const char* color,int length);
    static void clearCell(int x,int y);
    static void setCell(int x,int y, char chr,char color);
    static void swapBuffers();
    static void clearBuffer();
    static void fill2d(char color,char ch, int rect2d[4]);
};
#endif // __SCREEN_HPP_P__
