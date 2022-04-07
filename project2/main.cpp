// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"
 
// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map (int time_d);
void init_quest_map();
int main ();
void reset_map();

//secret cat and gate coordinates
int catx=0;
int caty=0;
int gatex=0;
int gatey=0;

 
/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_catnip;
    int has_key;
    int omni;
    int has_quest;
    int bamboo_count;
} Player;

int time_d; 

int saved_x;
int saved_y;

 
/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define CAT_FOUND 7
#define ENTRANCE_FOUND 8
#define GATE_FOUND 9
#define OMNI_PRESS 10
#define RAMEN_FOUND 11
#define CATNIP_FOUND 12
#define GO_RIGHT_FAST 13
#define GO_LEFT_FAST 14
#define GO_UP_FAST 15
#define GO_DOWN_FAST 16
#define BAMBOO_FOUND 17
 
int get_action(GameInputs inputs)
{
    int action=inputs.b1;
    int omnipotent=inputs.b2;
    int menu=inputs.b3;
    
    double xacc=inputs.ax;
    double yacc=inputs.ay;
    
    MapItem* south=get_south(Player.x,Player.y);
    MapItem* north=get_north(Player.x,Player.y);
    MapItem* east=get_east(Player.x,Player.y);
    MapItem* west=get_west(Player.x,Player.y);
    MapItem* here=get_here(Player.x,Player.y);
    
    MapItem* far_south=get_south(Player.x,Player.y-1);
    MapItem* far_north=get_north(Player.x,Player.y+1);
    MapItem* far_east=get_east(Player.x+1,Player.y);
    MapItem* far_west=get_west(Player.x-1,Player.y);
    
    //actions requiring a button press
    if(here->type==CATNIP && action==0) return CATNIP_FOUND;
    if(here->type==BAMBOO && action==0) return BAMBOO_FOUND;
    if((east->type==CAT || west->type==CAT || north->type==CAT || south->type==CAT) && action==0)
    {
        return CAT_FOUND;    
    }
    if((east->type==ENTRANCE || west->type==ENTRANCE || north->type==ENTRANCE || south->type==ENTRANCE) && action==0)
    {
        return ENTRANCE_FOUND;    
    }
    if((east->type==GATE || west->type==GATE || north->type==GATE || south->type==GATE) && action==0)
    {
        return GATE_FOUND;    
    }
    if((east->type==RAMEN || west->type==RAMEN || north->type==RAMEN || south->type==RAMEN) && action==0)
    {
        return RAMEN_FOUND;    
    }
    if(menu==0) return MENU_BUTTON;
    if(omnipotent==0) return OMNI_PRESS;
    
    //actions requiring accelerometer input
    //sprint below
    if((yacc<= -.5) && ( (far_east->walkable && east->walkable) || Player.omni==1))
    {
        return GO_RIGHT_FAST;
    }
    else if((yacc>= 0.5) && ( (far_west->walkable && west->walkable) || Player.omni==1))
    {
        return GO_LEFT_FAST;
    }
    else if((xacc<= -0.5) && ( (far_north->walkable && north->walkable) || Player.omni==1))
    {
        return GO_UP_FAST;
    }
    else if((xacc>= 0.5) && ( (far_south->walkable && south->walkable) || Player.omni==1))
    {
        return GO_DOWN_FAST;
    }//normal motion below
    else if((yacc<= -0.2) && (east->walkable || Player.omni==1))
    {
        return GO_RIGHT;
    }
    else if((yacc>= 0.2) && (west->walkable || Player.omni==1))
    {
        return GO_LEFT;
    }
    else if((xacc<= -0.2) && (north->walkable || Player.omni==1))
    {
        return GO_UP;
    }
    else if((xacc>= 0.2) && (south->walkable || Player.omni==1))
    {
        return GO_DOWN;
    }
    
    //fall through
    return NO_ACTION;
}
 
/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {       
        case GO_DOWN:  
        { 
            Player.y = Player.y - 1; 
            return FULL_DRAW; 
        }
        case GO_UP:
        {
            Player.y = Player.y + 1; 
            return FULL_DRAW;
        }
        case GO_RIGHT:
        {
            Player.x = Player.x + 1; 
            return FULL_DRAW;  
        }         
        case GO_LEFT:   
        {
            Player.x = Player.x - 1; 
            return FULL_DRAW;  
        }   
        case GO_DOWN_FAST:  
        { 
            Player.y = Player.y - 2; 
            return FULL_DRAW; 
        }
        case GO_UP_FAST:
        {
            Player.y = Player.y + 2; 
            return FULL_DRAW;
        }
        case GO_RIGHT_FAST:
        {
            Player.x = Player.x + 2; 
            return FULL_DRAW;  
        }         
        case GO_LEFT_FAST:   
        {
            Player.x = Player.x - 2; 
            return FULL_DRAW;  
        }   
        case ENTRANCE_FOUND:
        {
            if(Player.has_key==false)
            {
                const char* line[]={"You don't","have a key!"};
                speech(line,2);
            }
            else if(Player.bamboo_count>=5)
            {
                const char* line[]={"You open the","gate and eat","some special","ramen with","rare bamboo","shoots!"};
                speech(line,6);
                map_erase(23,10);
                map_erase(24,10);
                map_erase(25,10);
                map_erase(26,10);
                map_erase(27,10);
                map_erase(28,10);
            }
            else
            {
                const char* line[]={"You open the","gate and eat","some ramen!"," "};
                speech(line,4);
                map_erase(23,10);
                map_erase(24,10);
                map_erase(25,10);
                map_erase(26,10);
                map_erase(27,10);
                map_erase(28,10);
            }  
            return FULL_DRAW;
        }
        case GATE_FOUND:
        {
            if(Player.has_quest==true)
            {
                if(Player.has_catnip==false)
                {
                    const char* line[]={"Entering the","quest."};
                    speech(line,2);
                    saved_x=Player.x;
                    saved_y=Player.y;
                    reset_map();
                    set_active_map(1);
                    init_quest_map();
                    Player.x=Player.y=1;
                    //set active map to 1
                    //draw map 1
                }
                else if(Player.has_catnip && map_width()==60)
                {
                    const char* line[]={"You already","completed the","quest!"," "};
                    speech(line,4);
                }
                else
                {
                    const char* line[]={"Returning to","the village."};
                    speech(line,2);
                    reset_map();
                    set_active_map(0);
                    init_main_map(time_d);
                    Player.x=saved_x;
                    Player.y=saved_y;
                    //set active map to 0
                    //redraw map 0
                }
            }
            else
            {
                const char* line[]={"Come back when","you have a","quest!"," "};
                speech(line,4);
            }
            return FULL_DRAW; 
        }
        case CAT_FOUND:
        {
            if(get_south(Player.x,Player.y)->type==CAT) draw_exclamation(58,38);
            else if(get_north(Player.x,Player.y)->type==CAT) draw_exclamation(47,70);
            else if(get_east(Player.x,Player.y)->type==CAT) draw_exclamation(69,48); 
            else draw_exclamation(47,47);
            if(Player.has_key)
            {
                const char* line[]={"You already","have the key!"};
                speech(line,2);
            }
            else if(Player.has_catnip)
            {
                const char* line[]={"Wow! Maybe","humans aren't","so terrible.","Here is ","your key."," "};
                speech(line,6);
                Player.has_key=true;
            }
            else if(Player.has_quest &&  !Player.has_catnip)
            {
                const char* line[]={"You already","talked to me!"};
                speech(line,2);
            }
            else
            {
                const char* line[]={"Hello young ","ninja. What","do you seek?","*Your stomach","growls*","Ha! I have","just the fix","for that. But","it will need","payment. Bring","me catnip,","and I will","give you the","key to some","yummy ramen."," "};
                speech(line,16);
                const char* special[]={"Another note,","if you can","collect at","least 5 bamboo","shoots around","this field,","you will","receive a","special type","of ramen!","Go on, now!"," "};
                speech(special,12);
                Player.has_quest=true;
            }
            return FULL_DRAW;
        }
        case CATNIP_FOUND:
        {
             Player.has_catnip=true;
             map_erase(Player.x,Player.y);
             return FULL_DRAW;
        }
        case BAMBOO_FOUND:
        {
             Player.bamboo_count++;
             map_erase(Player.x,Player.y);
             return FULL_DRAW;
        }
        case RAMEN_FOUND:
        {
            const char* line[]={"*SCHLURP*","Yum!!"};
            speech(line,2);
            return GAME_OVER;
        }
        case OMNI_PRESS:
        {
            Player.omni=!Player.omni;
            return FULL_DRAW;
        }
        case MENU_BUTTON:
        {
            draw_menu(Player.has_key,Player.has_catnip,Player.has_quest,map_width(),Player.bamboo_count,catx,caty,gatex,gatey,Player.omni);
            return FULL_DRAW;
        }
        default:        break;
    }
    return NO_RESULT;
}
 
/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init)
    {
        draw_border();
    }
    
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (i == 0 && j == 0) // Only draw the player on init
            {
                draw_player(u, v, Player.has_catnip, Player.has_key);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }
            
            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }
 
    // Draw status bars    
    draw_upper_status(Player.x,Player.y,Player.has_quest);
    draw_lower_status(Player.has_key,Player.omni);
}

//reset that map, baby
void reset_map()
{
    for(int i=0;i<map_width();i++)
    {
        for(int j=0;j<map_height();j++)
        {
            map_erase(i,j); 
        }
    }
}
 
 
/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map(int time_d)
{
    srand(time_d);
    // "Random" plants
    for(int i=1;i<map_width();i++)
    {
        int random=rand();
        random=random%map_width();
        add_plant(i,random);
    }
    
    // "Random" bamboo
    for(int i=1;i<map_width();i++)
    {
        int random=rand();
        random=random%map_width();
        add_bamboo(i,random);
    }
    
    add_wall(20,1,VERTICAL,10);
    add_wall(31,1,VERTICAL,10);
    add_wall(20,10,HORIZONTAL,11);
    add_entrance(23,10);
    add_ramen(25,5);
    
    int xc=rand() % ( (map_width()-2) +1);
    int yc=rand() % ( (map_height()-2) +1);
    int xg=rand() % ( (map_width()-6) +2);
    int yg=rand() % ( (map_height()-2) +2);
    while(xc==xg && yc==yg && !(xc>=20 && xc<=31 && yc>=1 && yc<=10) && !(xg>=17 && xg<=31 && yg>=1 && yg<=10))
    {
        xc=rand() % ( (map_width()-2) +1);
        yc=rand() % ( (map_height()-2) +1);
        xg=rand() % ( (map_width()-6) +2);
        yg=rand() % ( (map_height()-2) +2);
    }
   
    add_gate(xg,yg);
    add_cat(xc,yc);
    
    catx=xc;
    caty=yc;
    gatex=xg;
    gatey=yg;
    
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
 
    print_map();
}

void init_quest_map()
{
    Map* map = set_active_map(1);
    
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    
    add_gate(5,18);
    
    add_catnip(17,2);
    
    add_wall(16,1,VERTICAL,3);
    add_wall(13,3,VERTICAL,3);
    add_wall(13,5,HORIZONTAL,6);
    add_wall(2,3,HORIZONTAL,6);
    add_wall(2,3,VERTICAL,12);
    add_wall(2,8,HORIZONTAL,14);
    add_wall(6,6,VERTICAL,3);
    add_wall(16,8,VERTICAL,3);
    add_wall(17,14,HORIZONTAL,4);
    add_wall(4,14,VERTICAL,6);
    add_wall(10,1,VERTICAL,5);
    add_wall(12,9,VERTICAL,10);
    add_wall(7,14,HORIZONTAL,5);
    
    print_map();
}
 
/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    
    
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 5;
    Player.omni = false;
    Player.has_catnip=false;
    Player.has_key=false;
    Player.has_quest=false;
    Player.bamboo_count=0;
    
    time_d=draw_start();
    
    // Initialize the maps
    maps_init();
    init_main_map(time_d);
    
    // Initial drawing
    draw_game(true);
    
    // Main game loop
    while(1)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        // Actually do the game update:
        // 1. Read inputs
        GameInputs game=read_inputs();
        // 2. Determine action (get_action)
        int action=get_action(game);
        // 3. Update game (update_game)
        int game_state=update_game(action);
        // 3b. Check for game over
        if(game_state==GAME_OVER)
        {
          draw_game_over();
          wait(100);
        }
        // 4. Draw frame (draw_game)
        draw_game(game_state);
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
}