#include "map.h"

#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the get_active_map()->
 */
struct Map {
    HashTable* items;
    int w, h;
};

/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static Map map;
static Map quest;
static int active_map;

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y)
{
  int shift_X=X & 0x0000FFFF;
  shift_X=shift_X<<8;
  unsigned key=shift_X | Y;
  return key;
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
  return key%50;
}

void maps_init()
{
	map.w=60;
  	map.h=60;
  	map.items=createHashTable(map_hash,50);
  	quest.w=20;
  	quest.h=20;
  	quest.items=createHashTable(map_hash,50);
}

Map* get_active_map()
{
    if(active_map==0) return &map;
    else return &quest;
}

Map* set_active_map(int m)
{
    active_map = m;
    if(active_map==0) return &map;
    else return &quest;
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
	return get_active_map()->w;
}

int map_height()
{
	return get_active_map()->h;
}

int map_area()
{
	return get_active_map()->w * get_active_map()->h;
}

MapItem* get_north(int x, int y)
{
	return (MapItem*)getItem(get_active_map()->items,XY_KEY(x,y+1));
}

MapItem* get_south(int x, int y)
{
  return (MapItem*)getItem(get_active_map()->items,XY_KEY(x,y-1));
}

MapItem* get_east(int x, int y)
{
  return (MapItem*)getItem(get_active_map()->items,XY_KEY(x+1,y));
}

MapItem* get_west(int x, int y)
{
  return (MapItem*)getItem(get_active_map()->items,XY_KEY(x-1,y));
}

MapItem* get_here(int x, int y)
{
  return (MapItem*)getItem(get_active_map()->items,XY_KEY(x,y));
}

void map_erase(int x, int y)
{
  if(getItem(get_active_map()->items,XY_KEY(x,y)))
    deleteItem(get_active_map()->items,XY_KEY(x,y)); //dont really need
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_entrance(int x, int y) {
  for(int i=0;i<6;i++) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = ENTRANCE;
    w1->draw = draw_entrance;
    w1->walkable = false;
    w1->data = NULL;
    unsigned key = XY_KEY(x+i, y);
    void* val = insertItem(get_active_map()->items, key, w1);
    if (val) free(val); // If something is already there, free it
  }
}

void add_cat(int x, int y)
 {
   MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
   w1->type = CAT;
   w1->draw = draw_cat;
   w1->walkable = false;
   // boolean: whether or not cat has given the player the key yet
   w1->data = false;
   void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
   if (val) free(val); // If something is already there, free it
 }

  void add_ramen(int x, int y)
   {
     MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
     w1->type = RAMEN;
     w1->draw = draw_ramen;
     w1->walkable = false;
     w1->data = NULL;
     void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
     if (val) free(val); // If something is already there, free it
   }

void add_gate(int x, int y) {
  for(int i=0;i<4;i++) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GATE;
    w1->draw = draw_gate;
    w1->walkable = false;
    w1->data = NULL;
    unsigned key = XY_KEY(x+i, y);
    void* val = insertItem(get_active_map()->items, key, w1);
    if (val) free(val); // If something is already there, free it
  }
}

  void add_catnip(int x, int y)
   {
     MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
     w1->type = CATNIP;
     w1->draw = draw_catnip;
     w1->walkable = true;
     w1->data = NULL;
     void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
     if (val) free(val); // If something is already there, free it
   }
   
void add_bamboo(int x, int y)
{
     MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
     w1->type = BAMBOO;
     w1->draw = draw_bamboo;
     w1->walkable = true;
     w1->data = NULL;
     void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
     if (val) free(val); // If something is already there, free it
   }
