// A file to hold all the constants for the all original, definetly not subject to copyright,
// fortune wheel game

#ifndef CONSTANTS_H
#define CONSTANTS_H

// window constants
// screen size for a 13" macbook
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// background image offsets
// these are all linked, so if you're changing one (or the background image)
// you should probably check them all
const double BACKGROUND_IMAGE_X_OFFSET = -600;
const double BACKGROUND_IMAGE_Y_OFFSET = -270;
const double BACKGROUND_IMAGE_X_SCALE_FACTOR = 0.5;
const double BACKGROUND_IMAGE_Y_SCALE_FACTOR = 0.6;

// wheel constants
// wheel image is 512*512
const double WHEEL_X = (WINDOW_WIDTH - 512) / 2;
const double WHEEL_Y = WINDOW_HEIGHT * 0.66;

// tile constants
// top and bottom rows have 2 less tiles than middle rows
const int NUM_TILES_IN_TOP_ROW = 12;
const int NUM_TILE_ROWS = 4;
const double TILE_WIDTH = WINDOW_WIDTH / (NUM_TILES_IN_TOP_ROW + 6);
const double TILE_HEIGHT = TILE_WIDTH * 1.3;
const color TILE_BACK_COLOUR = COLOR_DARK_GREEN;
const color TILE_FRONT_COLOUR = COLOR_WHITE;
const color TILE_BORDER = COLOR_BLACK;
const color TILE_TEXT_COLOUR = COLOR_BLACK;
const double TILE_X = TILE_WIDTH * 3;
const double TILE_Y = TILE_HEIGHT;
const double TILE_FONT_SIZE = 32;

// general game display constants
const color TITLE_COLOUR = COLOR_BLACK;
const double TITLE_FONT_SIZE = 36;
// in degrees the min and max amount the wheel could spin
const int MIN_SPIN_POSSIBLE = 90;
const int MAX_SPIN_POSSIBLE = 450;
const string CLICK_PROMPT = "Click to spin the wheel";
const color PROMPT_COLOUR = COLOR_WHITE;
const int PROMPT_FONT_SIZE = 36;
const int SCORE_FONT_SIZE = 28;
const double SCORE_X = 20;
const double SCORE_y = 10;
const color SCORE_COLOUR = COLOR_DARK_RED;
const string KEY_PROMPT = "Choose a letter";
const color SOLVE_COLOUR = COLOR_RED;
const double SOLVE_X = TILE_WIDTH * 16;
const double SOLVE_Y = WHEEL_Y;
const double SOLVE_RADIUS = TILE_WIDTH;
const color SOLVE_TEXT_COLOUR = COLOR_BLACK;
const double SOLVE_TEXT_X = SOLVE_X - SOLVE_RADIUS + 2;
const double SOLVE_TEXT_Y = SOLVE_Y - (SOLVE_RADIUS / 3);
const int SOLVE_FONT_SIZE = 28;
const color VOWEL_COLOUR = COLOR_BLUE;
const double VOWEL_X = TILE_WIDTH * 2;
const double VOWEL_Y = WHEEL_Y;
const double VOWEL_RADIUS = TILE_WIDTH;
const color VOWEL_TEXT_COLOUR = COLOR_BLACK;
const double VOWEL_TEXT_X = VOWEL_X - VOWEL_RADIUS + 2;
const double VOWEL_TEXT_Y = VOWEL_Y - (VOWEL_RADIUS / 4);
const int VOWEL_FONT_SIZE = 16;
const int ANSWER_FONT_SIZE = 24;
const color ANSWER_TEXT_COLOUR = COLOR_BLACK;
const string ANSWER_PROMPT = "Enter your guess:";
const color ANSWER_BOX_COLOUR = COLOR_WHITE;
const double LEFT_POPPER_X = -100;
const double RIGHT_POPPER_X = 400;
const double POPPER_Y = TILE_HEIGHT * 3;
const double POPPER_SCALE_FACTOR = 0.7;
const string VOWEL_PROMPT = "Enter the vowel you would like to buy:";

// files with word/phrase lists
// add any additional files before the last item count
// last item count used to easily get the size of the enum
// also, update the vector below if you add a word, it's used
// to display the phrase type on the game board.
enum wordlist
{
    AROUND_THE_HOUSE,
    BEFORE_AND_AFTER,
    CLASSIC_CULTURE,
    EVENT,
    FICTIONAL_CHARACTERS,
    FOOD_AND_DRINK,
    FUN_AND_GAMES,
    IN_THE_KITCHEN,
    LIVING_THING,
    OCCUPATION,
    ON_THE_MAP,
    LAST_ITEM_USED_FOR_COUNT_ONLY
};

// keep this in the same order as the enum, and add any new titles here as well as in the enum
static const vector<string> PHRASE_TITLES = {"Around the House", 
                                        "Before and After", 
                                        "Culture Classic", 
                                        "Event", 
                                        "Fictional Characters",
                                        "Food and Drink", 
                                        "Fun and Games", 
                                        "In the Kitchen", 
                                        "Living Thing", 
                                        "Occupation",
                                        "On the Map"};

// the possible money amounts you can get from a spin
static const vector<int> WHEEL_VALUES = {-1, 750, 300, 100, 1000, 550, 800, 600, 250, -1, 5000, 175, 200, 350, 900, 500, 150, 400, 850, 200, 1500};

#endif

/****************************************
 * References                           *
 * *************************************/
// All phrases and words used to guess in the game are sourced from 
// https://whatswithjeff.com/wheel-of-fortune-platinum-answers-solutions/ on 19 Sept 2019 

// Background image used under public domain. Sourced from
// https://www.goodfreephotos.com/brazil/sao-paulo/night-time-city-skyline-of-sao-paulo-brazil.jpg.php on 20 Sept 2019

// Font sourced from
//FontSquirrel 2019, Roboto Font, font, retrieved 4 July 2019, <https://www.fontsquirrel.com/fonts/list/popular>

// Party popper image sourced from 
// https://commons.wikimedia.org/wiki/File:Emojione_1F389.svg on 23 Sept 2019