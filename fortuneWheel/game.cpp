#include "game.h"
#include "constants.h"
#include "tile.h"
#include <vector>
#include "input_output.h"

using namespace::std;

/****************************************
 * Functions not exposed in the header  *
 * *************************************/

// fills the board vector with empty tiles and returns it
vector<vector<tile>> fill_empty_rows()
{
    vector<vector<tile>> v_to_return;
    vector<tile> row_1_of_tiles;
    vector<tile> row_2_of_tiles;
    vector<tile> row_3_of_tiles;
    vector<tile> row_4_of_tiles;
    
    double rect_x = TILE_X;
    double rect_y = TILE_Y;

    // assign the top row
    for (int i = 0; i < NUM_TILES_IN_TOP_ROW; i++)
    {
        tile tile_to_push;
        tile_to_push.is_revealed = false;
        tile_to_push.tile_character = "";
        tile_to_push.image.tile_rectangle = rectangle_from(rect_x, rect_y, TILE_WIDTH, TILE_HEIGHT);
        tile_to_push.image.background_colour = TILE_BACK_COLOUR;
        row_1_of_tiles.push_back(tile_to_push);
        rect_x += TILE_WIDTH;
    }
    v_to_return.push_back(row_1_of_tiles);

    rect_x = TILE_X - TILE_WIDTH;
    rect_y += TILE_HEIGHT;

    // assign the middle two rows
    for (int i = 0; i < 2; i++)
    {
        vector<tile> vector_to_use = row_3_of_tiles;
        if (i == 0)
        {
            vector_to_use = row_2_of_tiles;
        }

        for (int j = 0; j < NUM_TILES_IN_TOP_ROW + 2; j++)
        {
            tile tile_to_push;
            tile_to_push.is_revealed = false;
            tile_to_push.tile_character = "";
            tile_to_push.image.tile_rectangle = rectangle_from(rect_x, rect_y, TILE_WIDTH, TILE_HEIGHT);
            tile_to_push.image.background_colour = TILE_BACK_COLOUR;
            vector_to_use.push_back(tile_to_push);
            rect_x += TILE_WIDTH;
        }
        rect_x = TILE_X - TILE_WIDTH;
        rect_y += TILE_HEIGHT;
        v_to_return.push_back(vector_to_use);
    }
    
    rect_x = TILE_X;

    // assigs the last row
    for (int i = 0; i < NUM_TILES_IN_TOP_ROW; i++)
    {
        tile tile_to_push;
        tile_to_push.is_revealed = false;
        tile_to_push.tile_character = "";
        tile_to_push.image.tile_rectangle = rectangle_from(rect_x, rect_y, TILE_WIDTH, TILE_HEIGHT);
        tile_to_push.image.background_colour = TILE_BACK_COLOUR;
        row_4_of_tiles.push_back(tile_to_push);
        rect_x += TILE_WIDTH;
    }
    v_to_return.push_back(row_4_of_tiles);
    
    return v_to_return;
}

/****************************************
 * places the chosen phrase in the tile *
 * structure.                           *
 *                                      *
 * @return phrase struct                *
 * *************************************/
void place_phrase_in_tiles(game_data &game)
{
    game.game_board = fill_empty_rows();
    allocate_phrase(game.game_board, game.phrase_to_guess);
}

/****************************************
 * Functions exposed in the header      *
 * *************************************/

// creates a new game and returns it
game_data new_game()
{
    game_data new_game;
    do 
    {
        new_game.phrase_to_guess = get_new_phrase();
    } while (new_game.phrase_to_guess.phrase_string.length() < 12);
    
    write_line("phrase: " + new_game.phrase_to_guess.phrase_string);

    place_phrase_in_tiles(new_game);

    return new_game;
}

// the actual playing of the game. Returns false when it's game over
bool play_game(game_data &game)
{
    process_events();
    int spin_score = spin_wheel(game);
    if (game.phrase_to_guess.true_count == game.phrase_to_guess.phrase_string.length())
    {
        return true;
    }
    draw_game(game);
    // -1 is bankrupt
    if (spin_score < 0)
    {
        game.score = 0;
    }
    else if (spin_score != 0)
    {
        game.score += (spin_score * get_letter(game, spin_score)); 
    }
    draw_game(game);

    return (game.phrase_to_guess.true_count == game.phrase_to_guess.phrase_string.length());
}