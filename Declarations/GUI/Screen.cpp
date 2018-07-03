#define _WIN32_WINNT 0x0500
#include "../../Headers/GUI/Screen.hpp"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI GetCurrentConsoleFont(HANDLE hConsoleOutput,BOOL bMaximumWindow,PCONSOLE_FONT_INFO lpConsoleCurrentFont);
#ifdef __cplusplus
}
#endif
using std::min;
using std::max;



Screen& Screen::getInstance(){
    static Screen instance;
    return instance;
}

#define WIDTH 101
#define HEIGHT 31
#define ADDITIONAL_X 16
#define ADDITIONAL_Y 39
bool Screen::calibrateSize(){
    CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
    COORD  windowSize;
    GetConsoleScreenBufferInfo ( hStdout, &csbiInfo );
    windowSize = csbiInfo.dwSize;
    width = windowSize.X;
    height = windowSize.Y;
    bool output= true;
    CONSOLE_FONT_INFO cInfo;
    GetCurrentConsoleFont(hStdout,false,&cInfo);
    /*moveCursor(0,0);
    std::cout<<cInfo.nFont;*/
    if(nFont!=cInfo.nFont){
        nFont=cInfo.nFont;
        totalRedraw=true;
    }
    nFont=cInfo.nFont;
    if(cInfo.nFont==0&&cInfo.dwFontSize.Y==7) cInfo.dwFontSize.Y=6;
    if( chWidth!=cInfo.dwFontSize.X||chHeight!=cInfo.dwFontSize.Y){
        totalRedraw=true;
        chWidth=cInfo.dwFontSize.X;
        chHeight=cInfo.dwFontSize.Y;
    }
    RECT coordRect;
    GetWindowRect(cHandle,&coordRect);
    if(coordRect.right-coordRect.left!=(chWidth*WIDTH)+ADDITIONAL_X||coordRect.bottom-coordRect.top!=(chHeight*HEIGHT)+ADDITIONAL_Y){
        MoveWindow ( cHandle, coordRect.left, coordRect.top, (chWidth * WIDTH) +ADDITIONAL_X, (chHeight * HEIGHT) +ADDITIONAL_Y, TRUE);
        if(height>HEIGHT){
            MoveWindow ( cHandle, coordRect.left, coordRect.top, (chWidth * WIDTH) +ADDITIONAL_X, (chHeight * (HEIGHT-2)) +ADDITIONAL_Y, TRUE);
        }
        totalRedraw=true;
    }
    if(width!=WIDTH||height!=HEIGHT){
        if(height>HEIGHT){
            COORD windowSize = { WIDTH, HEIGHT-2};
            SetConsoleScreenBufferSize( hStdout, windowSize);
        }
        COORD windowSize = { WIDTH, HEIGHT};
        SetConsoleScreenBufferSize( hStdout, windowSize);
        width=WIDTH;
        height=HEIGHT;
        totalRedraw=true;
    }
    makeCursorInvisible();
    return output;
}
#undef WIDTH
#undef HEIGHT
#undef ADDITIONAL_X
#undef ADDITIONAL_Y

Screen::Screen(){
    cHandle=GetConsoleWindow();
    hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
    makeCursorInvisible();
    calibrateSize();
    totalRedraw=true;
    CONSOLE_FONT_INFO cInfo;
    GetCurrentConsoleFont(hStdout,false,&cInfo);
    chWidth=cInfo.dwFontSize.X;
    chHeight=cInfo.dwFontSize.Y;
    nFont=cInfo.nFont;
}

void Screen::makeCursorInvisible(){
    _CONSOLE_CURSOR_INFO info;
    info.dwSize=1;
    info.bVisible=false;
    SetConsoleCursorInfo(hStdout,&info);
}

/*inline long long milliseconds_now() {
    static LARGE_INTEGER s_frequency;
    static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
    if (s_use_qpc) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / s_frequency.QuadPart;
    } else {
        return GetTickCount();
    }
}*/

void Screen::swapBuffers(){
    Screen* inst=&getInstance();
    if(inst->calibrateSize()){
        for(int x=0;x<100;x++){
            for(int y=0;y<30;y++){
                inst->bufferA[x][y]^=inst->bufferB[x][y];
                inst->bufferB[x][y]^=inst->bufferA[x][y];
                inst->bufferA[x][y]^=inst->bufferB[x][y];

                inst->colorBufferA[x][y]^=inst->colorBufferB[x][y];
                inst->colorBufferB[x][y]^=inst->colorBufferA[x][y];
                inst->colorBufferA[x][y]^=inst->colorBufferB[x][y];
            }
        }
        if(inst->totalRedraw){
            inst->totalPrint();
            inst->totalRedraw=false;
        }else{
            inst->printDifferences();
        }
    }
    /*static long pastTime;
    static long time;
    static double tps(0);
    pastTime=time;
    time=milliseconds_now();
    tps=(tps*59+(time-pastTime))/60;
    inst->moveCursor(80,29);
    printf("                    ");
    inst->moveCursor(80,29);
    printf("%f",(1000.0f/tps));*/
}

void Screen::totalPrint(){
    clearScreen();
    moveCursor(0,0);
    //moveCursor(0,1);
    for(int y=0;y<30;y++){
        for(int x=0;x<100;x++){
            SetConsoleTextAttribute(hStdout,colorBufferA[x][y]);
            printf("%c",bufferA[x][y]);
            SetConsoleTextAttribute(hStdout,0x0F);
        }
        printf("\n");
    }
    makeCursorInvisible();
}

void Screen::printDifferences(){
    for(int y=0;y<30;y++){
        for(int x=0;x<100;x++){
            if(bufferA[x][y]!=bufferB[x][y]||colorBufferA[x][y]!=colorBufferB[x][y]){
                moveCursor(x,y);
                SetConsoleTextAttribute(hStdout,colorBufferA[x][y]);
                printf("%c",bufferA[x][y]);
            }
        }
    }
    makeCursorInvisible();
}

void Screen::clearScreen() {
    char fill = ' ';
    COORD tl = {0,0};
    SetConsoleTextAttribute(hStdout,0x0F);
    CONSOLE_SCREEN_BUFFER_INFO s;
    GetConsoleScreenBufferInfo(hStdout, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(hStdout, fill, cells, tl, &written);
    FillConsoleOutputAttribute(hStdout, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(hStdout, tl);
    makeCursorInvisible();
}

void Screen::moveCursor(int x,int y){
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hStdout, pos);
}

void Screen::clearBuffer(){
    Screen* inst=&getInstance();
    for(int y=0;y<30;y++){
        for(int x=0;x<100;x++){
            inst->bufferB[x][y]=' ';
            inst->colorBufferB[x][y]=0x0F;
        }
    }
}

void Screen::fill2d(char color,char chr,int rect2d[4]){
    Screen* inst=&getInstance();
    for(int x=min(rect2d[0],rect2d[2]);x<=max(rect2d[2],rect2d[0]);x++){
        for(int y=min(rect2d[1],rect2d[3]);y<=max(rect2d[3],rect2d[1]);y++){
            inst->setCell_priv(x,y,chr,color);
        }
    }
}

void Screen::setCell_priv(int x,int y,char chr,char color){
    if(x>99||x<0||y>29||y<0) return;
    if(chr!=' '){
        this->bufferB[x][y]=chr;
    }
    if((color&0x0F)!=0x0F){
        this->colorBufferB[x][y]=(((this->colorBufferB[x][y])&0xF0)|(color&0x0F));
    }
    if((color&0xF0)!=0x00){
        this->colorBufferB[x][y]=(((this->colorBufferB[x][y])&0x0F)|(color&0xF0));
    }
}

void Screen::setCell(int x,int y,char chr,char color){
    getInstance().setCell_priv(x,y,chr,color);
}

void Screen::write(int x,int y,const char* str,const char* color,int length){
    Screen& inst=getInstance();
    for(int i=0;i<length;i++){
        inst.setCell_priv(x+i,y,str[i],color[i]);
    }
}
