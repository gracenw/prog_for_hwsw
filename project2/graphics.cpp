#include "graphics.h"
#include "speech.h"
#include "globals.h"

#include <stdint.h>


//SPRITE SKINS
int exclamation[121]={
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff000000, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff000000, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff000000, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff000000, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff000000, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff000000, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff0087ff, 0xff0087ff, 0xff0087ff, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00
};

int bamboo[121]={
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff0b7c0b, 0xff0b7c0b, 0xff1fc94c, 0xff0b7c0b, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff0b7c0b, 0xff1fc94c, 0xff1fc94c, 0xff0b7c0b, 0xff085108, 0xff085108, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff0b7c0b, 0xff1fc94c, 0xff0b7c0b, 0xff085108, 0xff085108, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff085108, 0xff085108, 0xff0b7c0b, 0xff1fc94c, 0xff1fc94c, 0xff085108, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff085108, 0xff085108, 0xff0b7c0b, 0xff1fc94c, 0xff0b7c0b, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff085108, 0xff1fc94c, 0xff1fc94c, 0xff0b7c0b, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff0b7c0b, 0xff1fc94c, 0xff0b7c0b, 0xff0b7c0b, 0xff085108, 0xff085108, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff0b7c0b, 0xff1fc94c, 0xff0b7c0b, 0xff085108, 0xff085108, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff085108, 0xff085108, 0xff0b7c0b, 0xff1fc94c, 0xff1fc94c, 0xff085108, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff085108, 0xff085108, 0xff0b7c0b, 0xff1fc94c, 0xff0b7c0b, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff085108, 0xff1fc94c, 0xff1fc94c, 0xff0b7c0b, 0xff00ff00, 0xff00ff00, 0xff00ff00
};

int ramen[121]={
0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695,
0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xff606066, 0xff606066, 0xffead695,
0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xff606066, 0xff606066, 0xffead695, 0xffead695,
0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xff606066, 0xff606066, 0xffead695, 0xffead695, 0xffead695,
0xffead695, 0xffffffff, 0xffffffff, 0xff85bff9, 0xff85f9a4, 0xff85e3f9, 0xff85bff9, 0xff859cf9, 0xffffffff, 0xffffffff, 0xffead695,
0xffead695, 0xffead695, 0xffffffff, 0xff859cf9, 0xff85bff9, 0xff85f9a4, 0xff859cf9, 0xff85bff9, 0xffffffff, 0xffead695, 0xffead695,
0xffead695, 0xffead695, 0xffffffff, 0xffffffff, 0xff85e3f9, 0xff85bff9, 0xff85e3f9, 0xffffffff, 0xffffffff, 0xffead695, 0xffead695,
0xffead695, 0xffead695, 0xffead695, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffead695, 0xffead695, 0xffead695,
0xff245561, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff245561,
0xff245561, 0xff245561, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff0a4e1c, 0xff245561, 0xff245561,
0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561
};

int catnip[121]={
0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 
0xffead695, 0xffead695, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xffead695, 0xffead695, 
0xffead695, 0xff000000, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff000000, 0xffead695, 
0xffead695, 0xff000000, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff000000, 0xffead695, 
0xffead695, 0xffead695, 0xff000000, 0xff245561, 0xff17642b, 0xff17642b, 0xff17642b, 0xff245561, 0xff000000, 0xffead695, 0xffead695, 
0xffead695, 0xff000000, 0xff245561, 0xff245561, 0xff17642b, 0xff17642b, 0xff17642b, 0xff245561, 0xff245561, 0xff000000, 0xffead695, 
0xff000000, 0xff245561, 0xff245561, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff245561, 0xff245561, 0xff000000, 
0xff000000, 0xff245561, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff245561, 0xff000000, 
0xff000000, 0xff245561, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff245561, 0xff000000, 
0xff000000, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff245561, 0xff000000, 
0xffead695, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xffead695
};

int gate[121]={
0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 0xffead695, 
0xffead695, 0xff06326d, 0xffead695, 0xff06326d, 0xffead695, 0xff06326d, 0xffead695, 0xff06326d, 0xffead695, 0xff06326d, 0xffead695, 
0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 
0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 
0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 
0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 
0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 
0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 
0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 0xff094d91, 0xff06326d, 
0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 
0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b, 0xff17642b
};

int plant[121]={
0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff000000, 0xff1fc94c, 0xff1fc94c, 0xff1fc94c, 0xff1fc94c, 0xff1fc94c, 0xff1fc94c, 0xff1fc94c, 0xff000000, 0xff00ff00, 
0xff000000, 0xff1fc94c, 0xff1fc94c, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff000000, 
0xff000000, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff000000, 
0xff00ff00, 0xff000000, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff099117, 0xff000000, 0xff000000, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff094d91, 0xff094d91, 0xff245561, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff094d91, 0xff094d91, 0xff245561, 0xff000000, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff094d91, 0xff094d91, 0xff245561, 0xff000000, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff094d91, 0xff094d91, 0xff245561, 0xff000000, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff094d91, 0xff094d91, 0xff245561, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 
0xff00ff00, 0xff00ff00, 0xff000000, 0xff094d91, 0xff094d91, 0xff094d91, 0xff094d91, 0xff245561, 0xff000000, 0xff00ff00, 0xff00ff00
};

void draw_player(int u, int v, int has_catnip, int has_key)
{
    const char* img;
    if(has_catnip==YES)
    {
      img="GG0YYYYY0GGG0YYYYYYY0GG0YVVDDVY0GG0VVDDVVV0GG0VSSSSSV0GG0SSUSUSS0GGG0SSSSS0GGGGG0OSO0GGGGG0OO0OO0GGG0OOO0OBBBGG0OOO0OBBBG";
    }
    else if(has_key==YES)
    {
       img="GG0YYYYY0GGG0YYYYYYY0GG0YVVDDVY0GG0VVDDVVV0GG0VSSSSSV0GG0SSUSUSS0GGG0SSSSS0GGGGG0OSO0GGGGG0OO0OO0GGG0OOO0OLLLGG0OOO0OLLLG";
    }
    else
    {
      img="GG0YYYYY0GGG0YYYYYYY0GG0YVVDDVY0GG0VVDDVVV0GG0VSSSSSV0GG0SSUSUSS0GGG0SSSSS0GGGGG0OSO0GGGGG0OO0OO0GGG0OOO0OOO0GG0OOO0OOO0G";
    }
    draw_img(u, v, img);
}

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'W') colors[i] = WHITE;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'B') colors[i] = BROWN;
        else if (img[i] == 'O') colors[i] = ORANGE;
        else if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'U') colors[i] = BLUE;
        else if (img[i] == 'L') colors[i] = LGREY;
        else if (img[i] == 'D') colors[i] = DGREY;
        else if (img[i] == 'E') colors[i] = YGREEN;
        else if (img[i] == 'N') colors[i] = LGREEN;
        else if (img[i] == 'C') colors[i] = CYAN;
        else if (img[i] == 'S') colors[i] = SKIN;
        else if (img[i] == 'V') colors[i] = NAVY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_nothing(int u, int v)
{
    // Fill a tile with white
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_plant(int u, int v)
{
    uLCD.BLIT(u, v, 11, 11, plant);
}

void draw_entrance(int u, int v)
{
  const char* img="WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
  draw_img(u, v, img);
}

void draw_cat(int u, int v)
{
  const char* img="GGGGGGGGGGGGGGGGGGGGGGGGG0GGG0GGGGG0L000L0GGG0LLLLLLL0GG0L0LLL0L0GG0LLLDLLL0GG0LLDDDLL0GGG0LLLLL0GGGGG00000GGGGGGGGGGGGGG";
  draw_img(u, v, img);
}

void draw_ramen(int u, int v)
{
    uLCD.BLIT(u,v,11,11,ramen);
}

void draw_game_over()
{
    uLCD.filled_rectangle(0,0,127,127,BLACK);
    uLCD.textbackground_color(BLACK);
    uLCD.text_bold(ON);
    uLCD.locate(1,4);
    uLCD.color(WHITE);
    uLCD.printf("GAME OVER");
    uLCD.locate(1,7);
    uLCD.printf("Enjoy ur ramen :)");
}

int draw_start()
{
    Timer time; time.start();
    uLCD.color(NAVY);
    uLCD.locate(3,1);
    uLCD.printf("Road to Ramen");
    uLCD.color(ORANGE);
    uLCD.locate(2,4);
    uLCD.printf("RETRIEVE THE");
    uLCD.locate(2,6);
    uLCD.printf("CATNIP, GET");
    uLCD.locate(2,8);
    uLCD.printf("RAMEN!");
    uLCD.color(WHITE);
    uLCD.locate(1,12);
    uLCD.printf("Press button 1");
    uLCD.locate(1,14);
    uLCD.printf("to start");
    while(button1) continue;
    uLCD.filled_rectangle(0,0,127,127,BLACK);
    time.stop();
    return time.read_ms();
}

void draw_gate(int u, int v)
{
    uLCD.BLIT(u,v,11,11,gate);
}

void draw_catnip(int u, int v)
{
    uLCD.BLIT(u,v,11,11,catnip);
}

void draw_bamboo(int u, int v)
{
    uLCD.BLIT(u,v,11,11,bamboo);
}

void draw_exclamation(int u, int v)
{
    uLCD.BLIT(u,v,11,11,exclamation);
}

void draw_upper_status(int x, int y, int has_quest)
{
    uLCD.color(WHITE);
    uLCD.textbackground_color(BLACK);
    uLCD.line(0, 9, 127, 9, WHITE); //bottom border of status bar
    uLCD.locate(0,0);
    uLCD.printf("(%i,", x);
    uLCD.printf("%i) ", y);
    //if(has_quest==true) uLCD.printf("Quest:on ");
    //else uLCD.printf("Quest:off");
}

void draw_lower_status(int key, int omni)
{
    uLCD.color(WHITE);
    uLCD.textbackground_color(BLACK);
    uLCD.line(0, 118, 127, 118, WHITE);
    uLCD.locate(0,15);
    if(key==false) uLCD.printf("Key:no ");
    else uLCD.printf("Key:yes ");
    if(omni==false) uLCD.printf("Omni:off");
    else uLCD.printf("Omni:on ");
}

void draw_menu(int has_key, int has_catnip, int has_quest, int map_num, int bamboo_count, int catx, int caty, int gatex, int gatey, int omni)
{
    uLCD.filled_rectangle(0,0,127,127,BLACK);
    uLCD.locate(1,3);
    uLCD.printf("Game Status:");
    uLCD.locate(1,5);
    if(has_key) uLCD.printf("Go find the       ramen!");
    else if(map_num==60 && has_catnip || !has_quest) uLCD.printf("Go find the       cat!");
    else if(map_num==60 && has_quest && !has_catnip) uLCD.printf("Go find the       quest gate!");
    else if(map_num==20 && !has_catnip) uLCD.printf("Go find the       catnip!");
    else if(map_num==20 && has_catnip) uLCD.printf("Go find the       return gate!");
    else uLCD.printf("missing condition");
    uLCD.locate(1,9);
    uLCD.printf("Bamboo count= %i",bamboo_count);
    if(omni)
    {
        uLCD.locate(1,12);
        uLCD.printf("Cat= (%i,%i)",catx,caty);
        uLCD.locate(1,13);
        uLCD.printf("Gate= (%i,%i)",gatex,gatey);
    }
    while(button3) continue;
}

void draw_dead()
{
    const char* line[]={"I don't feel","so good..."};
    speech(line,2);
    wait(3);
    uLCD.filled_rectangle(0,0,127,127,BLACK);
    uLCD.textbackground_color(BLACK);
    uLCD.text_bold(ON);
    uLCD.locate(1,4);
    uLCD.color(WHITE);
    uLCD.printf("GAME OVER");
    uLCD.locate(1,7);
    uLCD.printf("You were poisoned and died!");
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, BROWN); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, BROWN); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, BROWN); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, BROWN); // Right
}
