#include "splashkit.h"

int main()
{
  const int GAME_SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const int GAME_SCREEN_HEIGHT = SCREEN_HEIGHT -100;
  const int SPIDER_RADIUS = 25;
  const int SPIDER_SPEED = 3;
  const int FLY_RADIUS= 10;

  const string GAME_TIMER = "GameTimer";

  int spiderX = GAME_SCREEN_WIDTH/2;
  int spiderY = GAME_SCREEN_HEIGHT/2;
  int flyX = rnd(GAME_SCREEN_WIDTH);
  int flyY = 100 + rnd(GAME_SCREEN_HEIGHT);
  int countgame = 0;
  int countwin = 0;
  
  bool flag = false;
  bool flypresent = false;

  long presentfor = 1000 + rnd(2000);
  long leaveat = 0;

  load_font("main","Roboto-Light.ttf"); //Load front for text on screen

  open_window("Fly Catch", GAME_SCREEN_WIDTH, SCREEN_HEIGHT); //create the screen

  create_timer(GAME_TIMER); //create a timer for the game to based off of.
  start_timer(GAME_TIMER);

  while (!quit_requested())
  {
    //Spider movement code
    if ((key_down(RIGHT_KEY)) && (spiderX + SPIDER_RADIUS < GAME_SCREEN_WIDTH))//spider move right
    {
        spiderX += SPIDER_SPEED;
    }
    if ((key_down(LEFT_KEY)) && (spiderX - SPIDER_RADIUS > 0)) //spider move left
    {
        spiderX -= SPIDER_SPEED;
    }

   if ((key_down(DOWN_KEY)) && (spiderY + SPIDER_RADIUS < SCREEN_HEIGHT)) //spider move down
    {
        spiderY += SPIDER_SPEED;
    }
    if ((key_down(UP_KEY)) && (spiderY - SPIDER_RADIUS > 100)) //spider move up
    {
        spiderY -= SPIDER_SPEED;
    }
    //spider movenent code end
    
    if (!flypresent && timer_ticks(GAME_TIMER)> presentfor) //generate fly
    {
        flypresent = true;

        flyX= rnd(GAME_SCREEN_WIDTH);
        flyY = 100 + rnd(GAME_SCREEN_HEIGHT);
        countgame += 1;
        
        leaveat = timer_ticks(GAME_TIMER) + 2000 + rnd(5000);
    }
    else if (flypresent && timer_ticks(GAME_TIMER)> leaveat)
    {
      flypresent = false;
      presentfor = timer_ticks(GAME_TIMER)+1000 + rnd(2000);
    }
    
    flag = flypresent;
    if (circles_intersect(spiderX,spiderY, SPIDER_RADIUS, flyX,flyY,FLY_RADIUS))// check if spider ate fly
    {
        flypresent=false;
        presentfor = timer_ticks(GAME_TIMER)+1000 + rnd(2000);
    }
    if (flag && !flypresent)//counts the number of rounds/games played
    {
        countwin += 1;
    }

    clear_screen(color_white()); 
    fill_circle(color_black(), spiderX, spiderY, SPIDER_RADIUS);
    
    //generate the game counter on screen
    draw_text("You won "+ std::to_string(countwin) + " out of " + std::to_string(countgame) + " games!",color_black(),"main",60,10,10); 

    if (flypresent)
    {
        fill_circle(color_dark_green(), flyX, flyY, FLY_RADIUS);
    }
    
    refresh_screen(60);
    process_events();
    
  }
    
}




