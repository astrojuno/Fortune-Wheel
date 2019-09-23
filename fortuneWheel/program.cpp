#include "splashkit.h"
#include "constants.h"
#include "phrase.h"
#include "game.h"
#include "input_output.h"

using namespace::std;

// loads any needed resources
void load_resources()
{
    load_bitmap("background", "background.jpg");
    load_bitmap("wheel", "wheel.png");
    load_bitmap("popper", "popper.png");
    load_font("roboto", "Roboto-Bold.ttf");
}

// the entry point
int main()
{
    game_data game = new_game();

    load_resources();
    
    wheel fortune_wheel;
    fortune_wheel.image = bitmap_named("wheel");
    fortune_wheel.image_rotation = 0;
    game.fortune_wheel = fortune_wheel;

    open_window("Fortune Wheel!", WINDOW_WIDTH, WINDOW_HEIGHT);
    
    draw_game(game);

    bool stop_playing = false;

    while (!quit_requested() && !stop_playing)
    {
        process_events();
        stop_playing = play_game(game);

        delay(500);
    }

    return 0;
}