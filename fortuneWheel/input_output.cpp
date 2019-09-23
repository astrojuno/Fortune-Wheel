#include "input_output.h"
#include <iostream>
#include <fstream>
#include "splashkit.h"
#include "constants.h"

using namespace::std;

/****************************************
 * Functions not exposed in the header  *
 * *************************************/

// draws the tiles for the game
void draw_tiles(const vector<vector<tile>> &board)
{
    for (int i = 0; i < NUM_TILE_ROWS; i++)
    {
        vector<tile> vector_to_draw = board[i];
        for (int j = 0; j < vector_to_draw.size(); j++)
        {
            tile tile_to_draw  = vector_to_draw[j];
            fill_rectangle(tile_to_draw.image.background_colour, tile_to_draw.image.tile_rectangle);
            if ((tile_to_draw.is_revealed) && (tile_to_draw.tile_character != " "))
            {
                int char_width = text_width(tile_to_draw.tile_character, "roboto", TILE_FONT_SIZE);
                int char_height = text_height(tile_to_draw.tile_character, "roboto", TILE_FONT_SIZE);
                double char_x = ((tile_to_draw.image.tile_rectangle.width - char_width) / 2) + tile_to_draw.image.tile_rectangle.x;
                double char_y = ((tile_to_draw.image.tile_rectangle.height - char_height) / 2) + tile_to_draw.image.tile_rectangle.y;
                draw_text(tile_to_draw.tile_character, TILE_TEXT_COLOUR, "roboto", TILE_FONT_SIZE, char_x, char_y);
            }
            draw_rectangle(TILE_BORDER, tile_to_draw.image.tile_rectangle);
        }
    }
}

// draws the prompt given to the centre of screen area
void draw_prompt(string prompt)
{
    int text_box_width = text_width(prompt, "roboto", TITLE_FONT_SIZE);
    int text_box_height = text_height(prompt, "roboto", TITLE_FONT_SIZE);
    double prompt_x = (WINDOW_WIDTH - text_box_width) / 2;
    double prompt_y = ((WHEEL_Y - (TILE_Y + (TILE_HEIGHT * 4)) - text_box_height) / 2) + (TILE_Y + (TILE_HEIGHT * 4));
    draw_text(prompt, PROMPT_COLOUR, "roboto", PROMPT_FONT_SIZE, prompt_x, prompt_y);
    refresh_screen(60);
}

// draws the game score to the board
void draw_score(int score)
{
    string score_string = "Score: $" + to_string(score);
    draw_text(score_string, SCORE_COLOUR, "roboto", SCORE_FONT_SIZE, SCORE_X, SCORE_y);
    refresh_screen(60);
}

// draws the solve button
circle draw_solve()
{
    circle solve = circle_at(SOLVE_X, SOLVE_Y, SOLVE_RADIUS);
    fill_circle(SOLVE_COLOUR, solve);
    draw_text("SOLVE", SOLVE_TEXT_COLOUR, "roboto", SOLVE_FONT_SIZE, SOLVE_TEXT_X, SOLVE_TEXT_Y);
    refresh_screen(60);

    return solve;
}

// draws the buy a vowel button
circle draw_vowel()
{
    circle vowel = circle_at(VOWEL_X, VOWEL_Y, VOWEL_RADIUS);
    fill_circle(VOWEL_COLOUR, vowel);
    draw_text("BUY VOWEL", VOWEL_TEXT_COLOUR, "roboto", VOWEL_FONT_SIZE, VOWEL_TEXT_X, VOWEL_TEXT_Y);
    refresh_screen(60);

    return vowel;
}

// forward declaration to keep my nice formatting
void draw_title(string title);

// draws an input box to type the guess
string get_user_guess(const game_data &game)
{
    int text_box_width = text_width(game.phrase_to_guess.phrase_string, "roboto", ANSWER_FONT_SIZE);
    int text_box_height = text_height(game.phrase_to_guess.phrase_string, "roboto", ANSWER_FONT_SIZE);
    double text_box_x = (WINDOW_WIDTH - text_box_width) / 2;
    double text_box_y = WHEEL_Y;
    rectangle text_box = rectangle_from(text_box_x, text_box_y, text_box_width, text_box_height);

    start_reading_text(text_box);

    string answer = "";
    while (answer.length() == 0)
    {
        process_events();
        if (!reading_text())
        {
            answer = text_input();
        }

        fill_rectangle(ANSWER_BOX_COLOUR, text_box);

        if (reading_text())
        {
            draw_collected_text(ANSWER_TEXT_COLOUR, font_named("roboto"), ANSWER_FONT_SIZE, option_defaults());
        }
        
        refresh_screen(60);
    }
    end_reading_text();
    
    return answer;
}

// draws some winning stuff
void draw_winning()
{
    draw_bitmap("popper", LEFT_POPPER_X, POPPER_Y, option_scale_bmp(POPPER_SCALE_FACTOR, POPPER_SCALE_FACTOR, option_flip_y()));
    draw_bitmap("popper", RIGHT_POPPER_X, POPPER_Y, option_scale_bmp(POPPER_SCALE_FACTOR, POPPER_SCALE_FACTOR));
    refresh_screen(60);
}

// handles the solving of the puzzle
void solve_puzzle(game_data &game)
{
    clear_screen(COLOR_WHITE);
    draw_bitmap("background", BACKGROUND_IMAGE_X_OFFSET, BACKGROUND_IMAGE_Y_OFFSET, option_scale_bmp(BACKGROUND_IMAGE_X_SCALE_FACTOR, BACKGROUND_IMAGE_Y_SCALE_FACTOR));
    draw_tiles(game.game_board);
    draw_title(game.phrase_to_guess.phrase_title);
    draw_score(game.score);
    string guess = get_user_guess(game);

    // if they guessed correctly
    if (to_uppercase(guess) == to_uppercase(game.phrase_to_guess.phrase_string))
    {
        game.phrase_to_guess.true_count = game.phrase_to_guess.phrase_string.length();
        for (int i = 0; i < NUM_TILE_ROWS; i++)
        {
            for (int j = 0; j < game.game_board[i].size(); j++)
            {
                if (game.game_board[i][j].tile_character != "")
                {
                    game.game_board[i][j].is_revealed = true;
                }
            }
        }
        draw_game(game);
        draw_winning();
        
        delay(3000);
    }
}

// gets a vowel from the user
void get_vowel(game_data &game)
{
    bool keep_waiting = true;
    string selected_letter = "9";
    // couldn't figure out a more elegant way to do this. 
    // future me (or other programmers) please feel free to optimise this
    while (selected_letter == "9")
    {
        process_events();
        if (key_typed(A_KEY))
        {
            keep_waiting = false;
            selected_letter = "A";
        }
        else if (key_typed(E_KEY))
        {
            keep_waiting = false;
            selected_letter = "E";
        }
        else if (key_typed(I_KEY))
        {
            keep_waiting = false;
            selected_letter = "I";
        }
        else if (key_typed(O_KEY))
        {
            keep_waiting = false;
            selected_letter = "O";
        }
        else if (key_typed(U_KEY))
        {
            keep_waiting = false;
            selected_letter = "U";
        }
    }
    for (int i = 0; i < NUM_TILE_ROWS; i++)
    {
        for (int j = 0; j < game.game_board[i].size(); j++)
        {
            if (to_uppercase(game.game_board[i][j].tile_character) == selected_letter)
            {
                game.game_board[i][j].is_revealed = true;
                game.phrase_to_guess.true_count++;
                draw_game(game);
            }
        }
    }

}

// handles buying a vowel
void buy_vowel(game_data &game)
{
    game.score -= 500;
    draw_game(game);
    draw_prompt(VOWEL_PROMPT);
    get_vowel(game);
}

/****************************************
 * Functions exposed in the header      *
 * *************************************/

// loads all the phrases from the file, then chooses and returns a random one
vector<string> get_contents_of_file(string filename)
{
    ifstream load_file;
    load_file.open(filename, ifstream::in);
    string file_contents = "";
    vector<string> all_phrases;

    while (load_file.good())
    {
        char current_char = load_file.get();
        if (current_char == '\n')
        {
            all_phrases.push_back(file_contents);
            file_contents = "";
        }
        else 
        {
            file_contents += current_char;
        }
    }
    load_file.close();

    return all_phrases;
}

// draws the title the phrase relates to
void draw_title(string title)
{
    int text_box_width = text_width(title, "roboto", TITLE_FONT_SIZE);
    int text_box_height = text_height(title, "roboto", TITLE_FONT_SIZE);
    double title_x = (WINDOW_WIDTH - text_box_width) / 2;
    double title_y = (TILE_Y - text_box_height) / 2;
    draw_text(title, TITLE_COLOUR, "roboto", TITLE_FONT_SIZE, title_x, title_y);
}

// draws the game to screen
void draw_game(const game_data &game)
{
    clear_screen(COLOR_WHITE);
    draw_bitmap("background", BACKGROUND_IMAGE_X_OFFSET, BACKGROUND_IMAGE_Y_OFFSET, option_scale_bmp(BACKGROUND_IMAGE_X_SCALE_FACTOR, BACKGROUND_IMAGE_Y_SCALE_FACTOR));
    draw_bitmap(game.fortune_wheel.image, WHEEL_X, WHEEL_Y, option_rotate_bmp(game.fortune_wheel.image_rotation));
    draw_tiles(game.game_board);
    draw_title(game.phrase_to_guess.phrase_title);
    draw_score(game.score);

    refresh_screen(60);
}

// spins the wheel when the user clicks. returns the result of the spin
// -1 for bankrupt
int spin_wheel(game_data &game)
{
    bool keep_waiting = true;
    int random_spin_degree = rnd(MIN_SPIN_POSSIBLE, MAX_SPIN_POSSIBLE);
    draw_prompt(CLICK_PROMPT);
    circle solve = draw_solve();
    circle vowel = draw_vowel();

    while (keep_waiting && !quit_requested())
    {
        process_events();
        if (mouse_clicked(LEFT_BUTTON))
        {
            keep_waiting = false;
            point_2d mouse_loc = mouse_position();
            
            if (point_in_circle(mouse_loc, solve))
            {
                solve_puzzle(game);
                break;
            }
            else if (point_in_circle(mouse_loc, vowel))
            {
                buy_vowel(game);
                return 0;
            }
            // rotate if clicked anywhere else
            else
            {
                for (int i = 0; i < random_spin_degree; i++) 
                {
                    draw_bitmap(game.fortune_wheel.image, WHEEL_X, WHEEL_Y, option_rotate_bmp(i + game.fortune_wheel.image_rotation));
                    refresh_screen(60);
                    delay(50);
                }
                game.fortune_wheel.image_rotation = (game.fortune_wheel.image_rotation + random_spin_degree) % 360;
            }
        }
    }
    
    // return a random prize value from the array
    // the secret here is that the spinning wheel is just for looks and doesn't 
    // affect the prize
    return WHEEL_VALUES[rnd(0, WHEEL_VALUES.size() - 1)];
}

// gets a letter from the user and checks it
int get_letter(game_data &game, int spin_score)
{
    bool keep_waiting = true;
    string selected_letter = "9";
    int selected_letter_count = 0;
    // couldn't figure out a more elegant way to do this. 
    // future me (or other programmers) please feel free to optimise this
    while (selected_letter == "9")
    {
        process_events();
        draw_prompt("$" + to_string(spin_score) + " " + KEY_PROMPT);
        // vowels omitted as you have to buy them
        if (key_typed(B_KEY))
        {
            keep_waiting = false;
            selected_letter = "B";   
        }
        else if (key_typed(C_KEY))
        {
            keep_waiting = false;
            selected_letter = "C";
        }
        else if (key_typed(D_KEY))
        {
            keep_waiting = false;
            selected_letter = "D";
        }
        else if (key_typed(F_KEY))
        {
            keep_waiting = false;
            selected_letter = "F";
        }
        else if (key_typed(G_KEY))
        {
            keep_waiting = false;
            selected_letter = "G";
        }
        else if (key_typed(H_KEY))
        {
            keep_waiting = false;
            selected_letter = "H";
        }
        else if (key_typed(J_KEY))
        {
            keep_waiting = false;
            selected_letter = "J";
        }
        else if (key_typed(K_KEY))
        {
            keep_waiting = false;
            selected_letter = "K";
        }
        else if (key_typed(L_KEY))
        {
            keep_waiting = false;
            selected_letter = "L";
        }
        else if (key_typed(M_KEY))
        {
            keep_waiting = false;
            selected_letter = "M";
        }
        else if (key_typed(N_KEY))
        {
            keep_waiting = false;
            selected_letter = "N";
        }
        else if (key_typed(P_KEY))
        {
            keep_waiting = false;
            selected_letter = "P";
        }
        else if (key_typed(Q_KEY))
        {
            keep_waiting = false;
            selected_letter = "Q";
        }
        else if (key_typed(R_KEY))
        {
            keep_waiting = false;
            selected_letter = "R";
        }
        else if (key_typed(S_KEY))
        {
            keep_waiting = false;
            selected_letter = "S";
        }
        else if (key_typed(T_KEY))
        {
            keep_waiting = false;
            selected_letter = "T";
        }
        else if (key_typed(V_KEY))
        {
            keep_waiting = false;
            selected_letter = "V";
        }
        else if (key_typed(W_KEY))
        {
            keep_waiting = false;
            selected_letter = "W";
        }
        else if (key_typed(X_KEY))
        {
            keep_waiting = false;
            selected_letter = "X";
        }
        else if (key_typed(Y_KEY))
        {
            keep_waiting = false;
            selected_letter = "Y";
        }
        // (just in case you're singing along) aaaand..
        else if (key_typed(Z_KEY))
        {
            keep_waiting = false;
            selected_letter = "Z";
        }
    }

    // check to see if the letter has been guessed alread
    if (count(game.guessed_letters.begin(), game.guessed_letters.end(), selected_letter))
    {
        return 0;
    }
    else 
    {
        game.guessed_letters.push_back(selected_letter);

        for (int i = 0; i < NUM_TILE_ROWS; i++)
        {
            for (int j = 0; j < game.game_board[i].size(); j++)
            {
                if (to_uppercase(game.game_board[i][j].tile_character) == selected_letter)
                {
                    selected_letter_count++;
                    game.game_board[i][j].is_revealed = true;
                    game.phrase_to_guess.true_count++;
                    draw_game(game);
                }
            }
        }
    }

    return selected_letter_count;
}