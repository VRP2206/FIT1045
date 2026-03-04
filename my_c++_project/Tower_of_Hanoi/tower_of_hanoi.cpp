#include "splashkit.h"
int frame= 0;

/**
 * Procredure that contain instruction on how to generate all 15 frames for solving a tower of hanoi-4 block problem.
 * 
 * @param block contain which block has been moved 
 * @param from_pole store the pole number of which the block has been move from
 * @param destination_pole store the pole number of which the block has been move to
 */
void frames(int block, int from_pole,int destination_pole)
{
    load_font("main","Roboto-Light.ttf"); 
    clear_screen(color_white_smoke());
    fill_rectangle(color_burly_wood(),210, 100, 80, 700);
    fill_rectangle(color_burly_wood(),610, 100, 80, 700);
    fill_rectangle(color_burly_wood(),1010, 100, 80, 700);

    switch (frame)
    {
    case 1:
        fill_rectangle(color_aqua(),600,650,100,150);
        draw_rectangle(color_blue(),600,650,100,150);

        fill_rectangle(color_aqua(),150,350,200,150);
        draw_rectangle(color_blue(),150,350,200,150);

        fill_rectangle(color_aqua(),100,500,300,150);
        draw_rectangle(color_blue(),100,500,300,150);
 
        fill_rectangle(color_aqua(),50,650,400,150);
        draw_rectangle(color_blue(),50,650,400,150);
        break;

    case 2:
        fill_rectangle(color_aqua(),600,650,100,150);
        draw_rectangle(color_blue(),600,650,100,150);

        fill_rectangle(color_aqua(),950,650,200,150);
        draw_rectangle(color_blue(),950,650,200,150);

        fill_rectangle(color_aqua(),100,500,300,150);
        draw_rectangle(color_blue(),100,500,300,150);

        fill_rectangle(color_aqua(),50,650,400,150);
        draw_rectangle(color_blue(),50,650,400,150);
        break;


    case 3:
        fill_rectangle(color_aqua(),1000,500,100,150);
        draw_rectangle(color_blue(),1000,500,100,150);

        fill_rectangle(color_aqua(),950,650,200,150);
        draw_rectangle(color_blue(),950,650,200,150);

        fill_rectangle(color_aqua(),100,500,300,150);
        draw_rectangle(color_blue(),100,500,300,150);

        fill_rectangle(color_aqua(),50,650,400,150);
        draw_rectangle(color_blue(),50,650,400,150);
        break;

    case 4:
        fill_rectangle(color_aqua(),1000,500,100,150);
        draw_rectangle(color_blue(),1000,500,100,150);

        fill_rectangle(color_aqua(),950,650,200,150);
        draw_rectangle(color_blue(),950,650,200,150);

        fill_rectangle(color_aqua(),500,650,300,150);
        draw_rectangle(color_blue(),500,650,300,150);

        fill_rectangle(color_aqua(),50,650,400,150);
        draw_rectangle(color_blue(),50,650,400,150);
        break;

    case 5:
        fill_rectangle(color_aqua(),200,500,100,150);
        draw_rectangle(color_blue(),200,500,100,150);

        fill_rectangle(color_aqua(),950,650,200,150);
        draw_rectangle(color_blue(),950,650,200,150);

        fill_rectangle(color_aqua(),500,650,300,150);
        draw_rectangle(color_blue(),500,650,300,150);

        fill_rectangle(color_aqua(),50,650,400,150);
        draw_rectangle(color_blue(),50,650,400,150);
        break;

    case 6:
        fill_rectangle(color_aqua(),200,500,100,150);
        draw_rectangle(color_blue(),200,500,100,150);

        fill_rectangle(color_aqua(),550,500,200,150);
        draw_rectangle(color_blue(),550,500,200,150);

        fill_rectangle(color_aqua(),500,650,300,150);
        draw_rectangle(color_blue(),500,650,300,150);

        fill_rectangle(color_aqua(),50,650,400,150);
        draw_rectangle(color_blue(),50,650,400,150);
        break;

    case 7:
        fill_rectangle(color_aqua(),600,350,100,150);
        draw_rectangle(color_blue(),600,350,100,150);

        fill_rectangle(color_aqua(),550,500,200,150);
        draw_rectangle(color_blue(),550,500,200,150);

        fill_rectangle(color_aqua(),500,650,300,150);
        draw_rectangle(color_blue(),500,650,300,150);

        fill_rectangle(color_aqua(),50,650,400,150);
        draw_rectangle(color_blue(),50,650,400,150);
        break;

    case 8:
        fill_rectangle(color_aqua(),600,350,100,150);
        draw_rectangle(color_blue(),600,350,100,150);

        fill_rectangle(color_aqua(),550,500,200,150);
        draw_rectangle(color_blue(),550,500,200,150);

        fill_rectangle(color_aqua(),500,650,300,150);
        draw_rectangle(color_blue(),500,650,300,150);

        fill_rectangle(color_aqua(),850,650,400,150);
        draw_rectangle(color_blue(),850,650,400,150);
        break;

    case 9:
        fill_rectangle(color_aqua(),1000,500,100,150);
        draw_rectangle(color_blue(),1000,500,100,150);

        fill_rectangle(color_aqua(),550,500,200,150);
        draw_rectangle(color_blue(),550,500,200,150);

        fill_rectangle(color_aqua(),500,650,300,150);
        draw_rectangle(color_blue(),500,650,300,150);

        fill_rectangle(color_aqua(),850,650,400,150);
        draw_rectangle(color_blue(),850,650,400,150);
        break;

    case 10:
        fill_rectangle(color_aqua(),1000,500,100,150);
        draw_rectangle(color_blue(),1000,500,100,150);

        fill_rectangle(color_aqua(),150,650,200,150);
        draw_rectangle(color_blue(),150,650,200,150);

        fill_rectangle(color_aqua(),500,650,300,150);
        draw_rectangle(color_blue(),500,650,300,150);

        fill_rectangle(color_aqua(),850,650,400,150);
        draw_rectangle(color_blue(),850,650,400,150);
        break;

    case 11:
        fill_rectangle(color_aqua(),200,500,100,150);
        draw_rectangle(color_blue(),200,500,100,150);

        fill_rectangle(color_aqua(),150,650,200,150);
        draw_rectangle(color_blue(),150,650,200,150);

        fill_rectangle(color_aqua(),500,650,300,150);
        draw_rectangle(color_blue(),500,650,300,150);

        fill_rectangle(color_aqua(),850,650,400,150);
        draw_rectangle(color_blue(),850,650,400,150);
        break;

    case 12:
        fill_rectangle(color_aqua(),200,500,100,150);
        draw_rectangle(color_blue(),200,500,100,150);

        fill_rectangle(color_aqua(),150,650,200,150);
        draw_rectangle(color_blue(),150,650,200,150);

        fill_rectangle(color_aqua(),900,500,300,150);
        draw_rectangle(color_blue(),900,500,300,150);

        fill_rectangle(color_aqua(),850,650,400,150);
        draw_rectangle(color_blue(),850,650,400,150);
        break;

    case 13:
        fill_rectangle(color_aqua(),600,650,100,150);
        draw_rectangle(color_blue(),600,650,100,150);

        fill_rectangle(color_aqua(),150,650,200,150);
        draw_rectangle(color_blue(),150,650,200,150);

        fill_rectangle(color_aqua(),900,500,300,150);
        draw_rectangle(color_blue(),900,500,300,150);

        fill_rectangle(color_aqua(),850,650,400,150);
        draw_rectangle(color_blue(),850,650,400,150);
        break;

    case 14:
        fill_rectangle(color_aqua(),600,650,100,150);
        draw_rectangle(color_blue(),600,650,100,150);

        fill_rectangle(color_aqua(),950,350,200,150);
        draw_rectangle(color_blue(),950,350,200,150);

        fill_rectangle(color_aqua(),900,500,300,150);
        draw_rectangle(color_blue(),900,500,300,150);

        fill_rectangle(color_aqua(),850,650,400,150);
        draw_rectangle(color_blue(),850,650,400,150);
        break;

    case 15:
        fill_rectangle(color_aqua(),1000,200,100,150);
        draw_rectangle(color_blue(),1000,200,100,150);

        fill_rectangle(color_aqua(),950,350,200,150);
        draw_rectangle(color_blue(),950,350,200,150);

        fill_rectangle(color_aqua(),900,500,300,150);
        draw_rectangle(color_blue(),900,500,300,150);

        fill_rectangle(color_aqua(),850,650,400,150);
        draw_rectangle(color_blue(),850,650,400,150);
        break;

    }
    draw_text(("Move block " + std::to_string(block) + " from pole " + std::to_string(from_pole)+ " to pole " + std::to_string(destination_pole)),color_black(),"main",60,10,10); 
    refresh_screen();
    delay(1000);
    
}

/**
 * Move block from a pole 1 to another pole 3 with the uses of a third temporary pole so that no bigger block is every on the smaller block
 * @param n the disc number to move
 * @param from_pole the number of the pole to move from
 * @param destination_pole the number of the pole to move to
 * @param other_pole the number of the temporary holding pole
 */
void rearrange_block(int block, int from_pole, int destination_pole, int other_pole)
{
    if (block <= 0) 
    {
        return;
    }

    rearrange_block(block-1, from_pole, other_pole, destination_pole);
    frame +=1;
    frames(block,from_pole,destination_pole);
    rearrange_block(block-1, other_pole,destination_pole,from_pole);
}

/**
 * Procedure to generate initial screen
 */
void frame_0()
{
    open_window("Tower of Hanoi",1300,800);
    clear_screen(color_white_smoke());
    fill_rectangle(color_burly_wood(),210, 100, 80, 700); 
    fill_rectangle(color_burly_wood(),610, 100, 80, 700);  
    fill_rectangle(color_burly_wood(),1010, 100, 80, 700);  

    fill_rectangle(color_aqua(),200,200,100,150);
    draw_rectangle(color_blue(),200,200,100,150);

    fill_rectangle(color_aqua(),150,350,200,150);
    draw_rectangle(color_blue(),150,350,200,150);

    fill_rectangle(color_aqua(),100,500,300,150);
    draw_rectangle(color_blue(),100,500,300,150);

    fill_rectangle(color_aqua(),50,650,400,150);
    draw_rectangle(color_blue(),50,650,400,150);

    refresh_screen();
    delay(1000);
}

int main()
{
    int n = 4;
    int pole_A = 1;
    int pole_B = 2;
    int pole_c = 3;

    load_font("main","Roboto-Light.ttf"); 

    frame_0();

    rearrange_block(n, pole_A,pole_c,pole_B);
}