// deals with the brains behind the game

#ifndef GAME_H
#define GAME_H

#include "phrase.h"
#include "tile.h"

/****************************************
 * A struct to hold the wheel info.     *
 * Mostly used to keep track of it's    *
 * rotation.                            *
 * *************************************/
struct wheel 
{
    bitmap image;
    int image_rotation;
};

/****************************************
 * A struct to hold the game data       *
 * *************************************/
struct game_data
{
    phrase phrase_to_guess;
    vector<string> guessed_letters;
    int score = 0;
    vector<vector<tile>> game_board;
    wheel fortune_wheel;
}; 

/****************************************
 * creates a new game and returns it.   *
 *                                      *
 * @return game struct                  *
 * *************************************/
game_data new_game();

/****************************************
 * The actual game. Returns false when  *
 * it's game over.                      *
 *                                      *
 * @param game_data the game being      *
 *                  played              *
 * @return bool     returns false when  *
 *                  game over           *
 * *************************************/
bool play_game(game_data &game);

#endif