// holds the tile struct

#ifndef TILE_H
#define TILE_H

#include "splashkit.h"

// a struct to hold the tile image information
struct tile_image
{
    rectangle tile_rectangle;
    color background_colour;
};

// a tile to be shown on screen
struct tile
{
    // why is this a string, you ask? Because using char caused so many headaches 
    // I decided to change it to string. Future me (or another dev) feel free to implement
    // a change to put it back to char...
    string tile_character;
    bool is_revealed;
    tile_image image;
};


#endif