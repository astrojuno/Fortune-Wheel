// holds the phrase struct, and deals with all things to do with the phrase

#ifndef PHRASE_H
#define PHRASE_H

#include "splashkit.h"
#include "tile.h"

/****************************************
 * A struct to hold the phrase to be    *
 * guessed.                             *
 * *************************************/
struct phrase
{
    string phrase_string;
    int true_count = 0;
    string phrase_title;
};

/****************************************
 * creates a new phrase to guess and    *
 * returns it.                          *
 *                                      *
 * @return phrase struct                *
 * *************************************/
phrase get_new_phrase();

/****************************************
 * allocates the letters to tiles in a  *
 * short phrase                         *
 *                                      *
 * @param game_board the vector of      *
 *          vectors that makes up the   *
 *          game board                  *
 * @param phrase    the phrase to guess *
 *          for the game                *
 * *************************************/
void allocate_phrase(vector<vector<tile>> &game_board, phrase &phrase_to_guess);

/****************************************
 * allocates the letters to tiles in a  *
 * short phrase                         *
 *                                      *
 * @param game_board the vector of      *
 *          vectors that makes up the   *
 *          game board                  *
 * @param phrase    the phrase to guess *
 *          for the game                *
 * *************************************/
void allocate_medium_phrase(vector<vector<tile>> &game_board, phrase &phrase_to_guess);

#endif