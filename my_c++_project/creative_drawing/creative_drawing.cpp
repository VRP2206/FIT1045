#include "splashkit.h"

int main()
{
    int speed;

    // Initial text:
    write("Hello friend, have you ever felt the thrill of driving? (yes/no)");
    read_line();
    write_line("Oh interesting.");
    write_line("Well, let's go for a drive...");
    write_line("Let's take the lambo");

    //Load all sound that will be used in the program
    load_music("reving", "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/reving.wav");
    load_music("breaking", "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/breaking.wav");
    load_music("boom", "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/592388__magnuswaker__car-crash-with-glass.wav");
    load_music("driving", "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/706077__robinhood76__11657-low-sounding-car-driving-away-in-rain.wav");

    //create the screen and load 'frame' No-0
    open_window("Driving", 600, 600);
    clear_screen(color_green());

    fill_rectangle(color_black(), 250, 0, 100, 5000);
    fill_rectangle(color_orange_red(), 260, 200, 80, 125);
    fill_triangle(color_orange_red(), 260, 200, 340, 200, 300, 150);
    fill_triangle(color_orange_red(), 260, 325, 300, 325, 280, 350);
    fill_triangle(color_orange_red(), 340, 325, 300, 325, 320, 350);
    refresh_screen();
    play_music("driving");
    delay(3000);
    stop_music();
    close_window("Driving");

    write_line("Want to go a little faster...");
    write_line("How fast do you want to go(100-500km/h)");
    speed = stoi(read_line());
    write_line();

    write_line("OH what do we have here- a speedster, huh?");
    write_line();

    //create the screen for the rest of the frames and load 'frame' No-1
    open_window("speed kills", 600, 600);
    clear_screen(color_green());

    fill_rectangle(color_black(), 250, 250, 100, 500);
    fill_rectangle(color_black(), 250, 250, 500, 100);
    fill_rectangle(color_firebrick(), 150, 25, 200, 200);
    draw_line(color_white(), 150, 75, 350, 75);
    draw_line(color_white(), 150, 125, 350, 125);
    draw_line(color_white(), 150, 175, 350, 175);
    draw_line(color_white(), 200, 25, 200, 225);
    draw_line(color_white(), 250, 25, 250, 225);
    draw_line(color_white(), 300, 25, 300, 225);

    fill_rectangle(color_firebrick(), 400, 25, 200, 200);
    draw_line(color_white(), 400, 75, 600, 75);
    draw_line(color_white(), 400, 125, 600, 125);
    draw_line(color_white(), 400, 175, 600, 175);
    draw_line(color_white(), 450, 25, 450, 225);
    draw_line(color_white(), 500, 25, 500, 225);
    draw_line(color_white(), 550, 25, 550, 225);

    fill_rectangle(color_firebrick(), 25, 275, 200, 200);
    draw_line(color_white(), 25, 325, 225, 325);
    draw_line(color_white(), 25, 375, 225, 375);
    draw_line(color_white(), 25, 425, 225, 425);
    draw_line(color_white(), 75, 275, 75, 475);
    draw_line(color_white(), 125, 275, 125, 475);
    draw_line(color_white(), 175, 275, 175, 475);

    fill_rectangle(color_orange_red(), 260, 500, 80, 125);
    fill_triangle(color_orange_red(), 260, 500, 340, 500, 300, 450);
    fill_triangle(color_orange_red(), 260, 625, 300, 625, 280, 650);
    fill_triangle(color_orange_red(), 340, 625, 300, 625, 320, 650);

    refresh_screen();
    play_music("reving");

    delay(5000 - speed * 10); //time for which the current 'frame' stays on screen;
                              //sec *10 gives time in milisec; it is subtracted from 5000(5sec)
    stop_music();

    //load 'frame' No-2
    clear_screen(color_green());

    fill_rectangle(color_black(), 250, 250, 100, 500);
    fill_rectangle(color_black(), 250, 250, 500, 100);

    fill_rectangle(color_firebrick(), 150, 25, 200, 200);
    draw_line(color_white(), 150, 75, 350, 75);
    draw_line(color_white(), 150, 125, 350, 125);
    draw_line(color_white(), 150, 175, 350, 175);
    draw_line(color_white(), 200, 25, 200, 225);
    draw_line(color_white(), 250, 25, 250, 225);
    draw_line(color_white(), 300, 25, 300, 225);

    fill_rectangle(color_firebrick(), 400, 25, 200, 200);
    draw_line(color_white(), 400, 75, 600, 75);
    draw_line(color_white(), 400, 125, 600, 125);
    draw_line(color_white(), 400, 175, 600, 175);
    draw_line(color_white(), 450, 25, 450, 225);
    draw_line(color_white(), 500, 25, 500, 225);
    draw_line(color_white(), 550, 25, 550, 225);

    fill_rectangle(color_firebrick(), 25, 275, 200, 200);
    draw_line(color_white(), 25, 325, 225, 325);
    draw_line(color_white(), 25, 375, 225, 375);
    draw_line(color_white(), 25, 425, 225, 425);
    draw_line(color_white(), 75, 275, 75, 475);
    draw_line(color_white(), 125, 275, 125, 475);
    draw_line(color_white(), 175, 275, 175, 475);

    fill_rectangle(color_orange_red(), 260, 300, 80, 125);
    fill_triangle(color_orange_red(), 260, 300, 340, 300, 300, 250);
    fill_triangle(color_orange_red(), 260, 425, 300, 425, 280, 450);
    fill_triangle(color_orange_red(), 340, 425, 300, 425, 320, 450);
    write_line("FRICK, CAN'T SLOW DOWN FAST ENOUGH!!!");
    write_line();

    refresh_screen();
    play_music("breaking");

    delay(5000 - speed * 5);//time for which the current 'frame' stays on screen;
                            //sec * 5 gives time. it is multiplied by only 5 as the driver is trying to slow down
    stop_music();

    //load 'frame' No-3
    clear_screen(color_green());

    fill_rectangle(color_black(), 250, 250, 100, 500);
    fill_rectangle(color_black(), 250, 250, 500, 100);
    fill_rectangle(color_firebrick(), 150, 25, 200, 200);
    draw_line(color_white(), 150, 75, 350, 75);
    draw_line(color_white(), 150, 125, 350, 125);
    draw_line(color_white(), 150, 175, 350, 175);
    draw_line(color_white(), 200, 25, 200, 225);
    draw_line(color_white(), 250, 25, 250, 225);
    draw_line(color_white(), 300, 25, 300, 225);

    fill_rectangle(color_firebrick(), 400, 25, 200, 200);
    draw_line(color_white(), 400, 75, 600, 75);
    draw_line(color_white(), 400, 125, 600, 125);
    draw_line(color_white(), 400, 175, 600, 175);
    draw_line(color_white(), 450, 25, 450, 225);
    draw_line(color_white(), 500, 25, 500, 225);
    draw_line(color_white(), 550, 25, 550, 225);

    fill_rectangle(color_firebrick(), 25, 275, 200, 200);
    draw_line(color_white(), 25, 325, 225, 325);
    draw_line(color_white(), 25, 375, 225, 375);
    draw_line(color_white(), 25, 425, 225, 425);
    draw_line(color_white(), 75, 275, 75, 475);
    draw_line(color_white(), 125, 275, 125, 475);
    draw_line(color_white(), 175, 275, 175, 475);

    fill_rectangle(color_orange_red(), 260, 225, 80, 125);
    fill_triangle(color_orange_red(), 260, 350, 300, 350, 280, 375);
    fill_triangle(color_orange_red(), 340, 350, 300, 350, 320, 375);

    refresh_screen();
    play_music("boom");

    delay(5000 - speed * 5);
    stop_music();

    write_line("BOOM");
    write_line();

    write_line("BREAKING NEWs; Two adult died in a supercar crash. It was reported that the lambo driver was speeding,");
    write_line("causing them to crash into a building as the they were unable to slow down to take the up comming turn.");
    write_line();
    write_line("PLEASE DRIVE CAREFULLY!!!");
    write_line("DO NOT DRIVE FAST!!!");
}