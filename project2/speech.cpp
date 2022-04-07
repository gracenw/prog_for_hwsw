#include "speech.h"

#include "globals.h"
#include "hardware.h"
#include "map.h"

#define TOP 0
#define BOTTOM 1

static void draw_speech(const char* line, int spot)
{
    if(spot==TOP) uLCD.locate(3,11);
    else uLCD.locate(3,12);
    uLCD.printf(line);
}

/**
 * Display a speech bubble.
 */
void speech(const char* lines[], int length)
{
    uLCD.textbackground_color(WHITE);
    uLCD.color(BLACK);
    uLCD.filled_rectangle(20,85,123,107,WHITE);
    uLCD.line(20,85,123,85,BLACK);
    uLCD.line(20,85,20,107,BLACK);
    uLCD.line(123,85,123,108,BLACK);
    uLCD.line(20,107,123,107,BLACK);
    for(int i=0;i<length;i++)
    {
        int spot=TOP;
        if(i%2 != 0) spot=BOTTOM;
        draw_speech(lines[i],spot);
        if(spot==BOTTOM) {
            while(button1) continue;
            uLCD.filled_rectangle(20,85,123,107,WHITE);//erase bubble
            uLCD.line(20,85,123,85,BLACK);
            uLCD.line(20,85,20,107,BLACK);
            uLCD.line(123,85,123,108,BLACK);
            uLCD.line(20,107,123,107,BLACK);
        }
        else wait(.5);
    }
}
