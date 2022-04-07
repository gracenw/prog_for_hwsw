#ifndef GRAPHICS_H
#define GRAPHICS_H


/**
 * Draws the player. This depends on the player state, so it is not a DrawFunc.
 */
void draw_player(int u, int v, int has_catnip, int has_key);

//returns a time value 
//the amount of time it takes the player to click out of the start screen is 
//used to seed the rand() function for placing the cat, gate, plants, and bamboo
int draw_start();

void draw_game_over();

/**
 * Takes a string image and draws it to the screen. The string is 121 characters
 * long, and represents an 11x11 tile in row-major ordering (across, then down,
 * like a regular multi-dimensional array).
 */
void draw_img(int u, int v, const char* img);

/**
 * DrawFunc functions.
 * These can be used as the MapItem draw functions.
 */
void draw_nothing(int u, int v);
void draw_wall(int u, int v);
void draw_plant(int u, int v);
void draw_entrance(int u, int v);
void draw_cat(int u, int v);
void draw_ramen(int u, int v);
void draw_gate(int u, int v);
void draw_catnip(int u, int v);
void draw_bamboo(int u, int v);

void draw_exclamation(int u, int v);

/**
 * Draw the upper status bar.
 */
void draw_upper_status(int x, int y, int has_quest);

/**
 * Draw the upper status bar.
 */
void draw_lower_status(int key, int omni);

/**
 * Draw the border for the map.
 */
void draw_border();

void draw_menu(int has_key,int has_catnip,int has_quest, int map_num, int bamboo_count, int catx, int caty, int gatex, int gatey, int omni);

void draw_dead();

#endif // GRAPHICS_H
