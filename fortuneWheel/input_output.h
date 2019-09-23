// deals with all things in and out of the program

#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "splashkit.h"
#include "game.h"

/****************************************
 * Takes the filename and returns a     *
 * vector with every phrase in each     *
 * index point.                         *
 *                                      *
 * @param   string  filename.txt        *
 * @return  vector of phrases           *
 * *************************************/
vector<string> get_contents_of_file(string filename);

/****************************************
 * Draws the game to screen             *
 * *************************************/
void draw_game(const game_data &game);

/****************************************
 * Waits for the user to click, then    *
 * spins the wheel                      *
 * @return the value of the spin (0 for)*
 *          bankrupt)                   *
 * *************************************/
int spin_wheel(game_data &game);

/****************************************
 * Waits for the user to enter a letter *
 * then scores that letter              *
 * @return the number of times the      *
 *          was placed                  *
 * *************************************/
int get_letter(game_data &game, int spin_score);

#endif