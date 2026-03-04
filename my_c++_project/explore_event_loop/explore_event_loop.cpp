#include "splashkit.h"

int main()
{
    int radius = 50;

    open_window("screen", 600, 600);
    clear_screen(color_white());
    refresh_screen();

    while (!quit_requested())
    {
        process_events();
        

        if (key_down(C_KEY)) //clear screen to a radom color
        {
            clear_screen(random_color());
            refresh_screen();
            
        }

        if (key_down(S_KEY)) // Set radius to 10 when key s is pressed
        {
            radius = 10;
        }

        if (key_down(M_KEY)) // set radius to 50 when key m is pressed
        {
            radius = 50;
        }

        if (key_down(L_KEY)) // set radius to 100 when key l is pressed
        {
            radius = 100;
        }

        if (key_down(NUM_5_KEY)) //create 100 circle
        {
            for (int i = 0; i < 100; i++)
            {
                fill_circle(random_color(), rnd(1, 600), rnd(1, 600), radius);
            }
            refresh_screen();
            
        }

        if (mouse_clicked(LEFT_BUTTON)) // create a circle at the position of the mouse position when the mouse left button is pressed
        {
            fill_circle(random_color(), mouse_x(), mouse_y(), radius);
            refresh_screen();
    
        }
    }
    close_window("Screen");

    return 0;
}