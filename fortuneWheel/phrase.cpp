#include "phrase.h"
#include "constants.h"
#include "splashkit.h"
#include "input_output.h"

using namespace::std;

/****************************************
 * Functions not exposed in the header  *
 * *************************************/

/****************************************
 * Takes a wordlist reference and       *
 * returns a random phrase from that    *
 * wordlist.                            *
 *                                      *
 * @param   wordlist reference          *
 * @return  string                      *
 * *************************************/
string get_phrase_from_wordlist(wordlist wordlist_index)
{
    vector<string> full_wordlist;
    
    switch (wordlist_index)
    {
        case AROUND_THE_HOUSE:
            full_wordlist = get_contents_of_file("around_the_house.txt");
            break;
        case BEFORE_AND_AFTER:
            full_wordlist = get_contents_of_file("before_and_after.txt");
            break;
        case CLASSIC_CULTURE:
            full_wordlist = get_contents_of_file("classic_culture.txt");
            break;
        case EVENT:
            full_wordlist = get_contents_of_file("event.txt");
            break;
        case FICTIONAL_CHARACTERS:
            full_wordlist = get_contents_of_file("fictional_characters.txt");
            break;
        case FOOD_AND_DRINK:
            full_wordlist = get_contents_of_file("food_and_drink.txt");
            break;
        case FUN_AND_GAMES:
            full_wordlist = get_contents_of_file("fun_and_games.txt");
            break;
        case IN_THE_KITCHEN:
            full_wordlist = get_contents_of_file("in_the_kitchen.txt");
            break;
        case LIVING_THING:
            full_wordlist = get_contents_of_file("living_thing.txt");
            break;
        case OCCUPATION:
            full_wordlist = get_contents_of_file("occupation.txt");
            break;
        case ON_THE_MAP:
            full_wordlist = get_contents_of_file("on_the_map.txt");
            break;
        case LAST_ITEM_USED_FOR_COUNT_ONLY:
            break;
    }

    int rand_index = rnd(0, full_wordlist.size());

    return full_wordlist[rand_index];
}

// takes a string and a board row and allocates the correct tiles
// returns the true count, which at this stage would just be any spaces in the string
int put_string_into_row(string phrase_to_allocate, vector<tile> &game_board)
{
    int starting_tile_index = ((NUM_TILES_IN_TOP_ROW + 2) - phrase_to_allocate.length()) / 2;
    int true_count = 0;

    for (int i = 0; i < phrase_to_allocate.length(); i++)
    {
        string char_string = phrase_to_allocate.substr(i, 1);
        game_board[i + starting_tile_index].tile_character = char_string;
        if ((char_string == " ") || (char_string == "\'"))
        {
            game_board[i + starting_tile_index].is_revealed = true;
            true_count += 1;
            game_board[i + starting_tile_index].image.background_colour = TILE_BACK_COLOUR;
        }
        else 
        {
            game_board[i + starting_tile_index].is_revealed = false;
            game_board[i + starting_tile_index].image.background_colour = TILE_FRONT_COLOUR;
        }
    }
    
    return true_count;
}

/****************************************
 * Functions exposed in the header      *
 * *************************************/

// Creates a new phrase and returns it
phrase get_new_phrase()
{
    phrase phrase_to_return;
    // get a random wordlist from the enum
    int random_topic_index = rnd(0, LAST_ITEM_USED_FOR_COUNT_ONLY);
    wordlist random_topic_wordlist = static_cast<wordlist>(random_topic_index);

    phrase_to_return.phrase_title = PHRASE_TITLES[random_topic_index];

    phrase_to_return.phrase_string = get_phrase_from_wordlist(random_topic_wordlist);

    return phrase_to_return;
}

// allocates the phrase to tiles
void allocate_phrase(vector<vector<tile>> &game_board, phrase &phrase_to_guess)
{
    vector<string> phrase_words;
    string word;
    // break the phrase into words
    for (int i = 0; i < phrase_to_guess.phrase_string.length(); i++)
    {
        if (phrase_to_guess.phrase_string[i] != ' ')
        {
            word += phrase_to_guess.phrase_string[i];
        }
        else 
        {
            phrase_words.push_back(word);
            word = "";
        }
    }

    // obe: catch the last word
    if ((phrase_words.size() == 0) || (phrase_words.back() != word))
    {
        phrase_words.push_back(word);
    }
    
    // check to see how many words fit into each row
    vector<string> board_rows;
    int board_row_index = 0;
    board_rows.push_back(phrase_words[0]);

    for (int i = 1; i < phrase_words.size(); i++)
    {
        if (board_rows[board_row_index].length() + phrase_words[i].length() < NUM_TILES_IN_TOP_ROW)
        {
            board_rows[board_row_index] += " ";
            board_rows[board_row_index] += phrase_words[i];
        }
        else
        {
            board_row_index++;
            board_rows.push_back(phrase_words[i]);
        }
    }

    // one row goes into the second top row
    if (board_rows.size() == 1)
    {
        phrase_to_guess.true_count = put_string_into_row(board_rows[0], game_board[1]);
    }
    // two rows go in the centre
    else if (board_rows.size() == 2)
    {
        phrase_to_guess.true_count = put_string_into_row(board_rows[0], game_board[1]);
        phrase_to_guess.true_count += put_string_into_row(board_rows[1], game_board[2]);
    }
    // three go in the bottom three
    else if (board_rows.size() == 3)
    {
        phrase_to_guess.true_count = put_string_into_row(board_rows[0], game_board[1]);
        phrase_to_guess.true_count += put_string_into_row(board_rows[1], game_board[2]);
        phrase_to_guess.true_count += put_string_into_row(board_rows[2], game_board[3]);
    }
    // four takes all four, obviously
    else if (board_rows.size() == 4)
    {
        phrase_to_guess.true_count = put_string_into_row(board_rows[0], game_board[0]);
        phrase_to_guess.true_count += put_string_into_row(board_rows[1], game_board[1]);
        phrase_to_guess.true_count += put_string_into_row(board_rows[2], game_board[2]);
        phrase_to_guess.true_count += put_string_into_row(board_rows[3], game_board[3]);
    }    
}
