using static SplashKitSDK.SplashKit;

int speed;


Write("Hello friend, have you ever felt the thrill of driving? (yes/no)");
ReadLine();
WriteLine("Oh interesting.");
WriteLine("Well, let's go for a drive...");
WriteLine("Let's take the lambo");

LoadMusic("reving", "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/reving.wav");
LoadMusic("breaking", "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/breaking.wav");
LoadMusic("boom", "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/592388__magnuswaker__car-crash-with-glass.wav");
LoadMusic("driving", "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/706077__robinhood76__11657-low-sounding-car-driving-away-in-rain.wav");

OpenWindow("Driving", 600, 600);
ClearScreen(ColorGreen());

FillRectangle(ColorBlack(), 250, 0, 100, 5000);
FillRectangle(ColorOrangeRed(), 260, 200, 80, 125);
FillTriangle(ColorOrangeRed(), 260, 200, 340, 200, 300, 150);
FillTriangle(ColorOrangeRed(), 260, 325, 300, 325, 280, 350);
FillTriangle(ColorOrangeRed(), 340, 325, 300, 325, 320, 350);
RefreshScreen();
PlayMusic("driving");
Delay(3000);
StopMusic();
CloseWindow("Driving");

WriteLine("Want to go a little faster...");
WriteLine("How fast do you want to go(100-500km/h)");
speed = ConvertToInteger(ReadLine());
WriteLine();

WriteLine("OH what do we have here- a speedster, huh?");
WriteLine();

OpenWindow("speed kills", 600, 600);
ClearScreen(ColorGreen());

FillRectangle(ColorBlack(), 250, 250, 100, 500);
FillRectangle(ColorBlack(), 250, 250, 500, 100);
FillRectangle(ColorFirebrick(), 150, 25, 200, 200);
DrawLine(ColorWhite(), 150, 75, 350, 75);
DrawLine(ColorWhite(), 150, 125, 350, 125);
DrawLine(ColorWhite(), 150, 175, 350, 175);
DrawLine(ColorWhite(), 200, 25, 200, 225);
DrawLine(ColorWhite(), 250, 25, 250, 225);
DrawLine(ColorWhite(), 300, 25, 300, 225);

FillRectangle(ColorFirebrick(), 400, 25, 200, 200);
DrawLine(ColorWhite(), 400, 75, 600, 75);
DrawLine(ColorWhite(), 400, 125, 600, 125);
DrawLine(ColorWhite(), 400, 175, 600, 175);
DrawLine(ColorWhite(), 450, 25, 450, 225);
DrawLine(ColorWhite(), 500, 25, 500, 225);
DrawLine(ColorWhite(), 550, 25, 550, 225);

FillRectangle(ColorFirebrick(), 25, 275, 200, 200);
DrawLine(ColorWhite(), 25, 325, 225, 325);
DrawLine(ColorWhite(), 25, 375, 225, 375);
DrawLine(ColorWhite(), 25, 425, 225, 425);
DrawLine(ColorWhite(), 75, 275, 75, 475);
DrawLine(ColorWhite(), 125, 275, 125, 475);
DrawLine(ColorWhite(), 175, 275, 175, 475);


FillRectangle(ColorOrangeRed(), 260, 500, 80, 125);
FillTriangle(ColorOrangeRed(), 260, 500, 340, 500, 300, 450);
FillTriangle(ColorOrangeRed(), 260, 625, 300, 625, 280, 650);
FillTriangle(ColorOrangeRed(), 340, 625, 300, 625, 320, 650);

RefreshScreen();
PlayMusic("reving");

Delay(5000 - speed * 10);
StopMusic();

ClearScreen(ColorGreen());

FillRectangle(ColorBlack(), 250, 250, 100, 500);
FillRectangle(ColorBlack(), 250, 250, 500, 100);

FillRectangle(ColorFirebrick(), 150, 25, 200, 200);
DrawLine(ColorWhite(), 150, 75, 350, 75);
DrawLine(ColorWhite(), 150, 125, 350, 125);
DrawLine(ColorWhite(), 150, 175, 350, 175);
DrawLine(ColorWhite(), 200, 25, 200, 225);
DrawLine(ColorWhite(), 250, 25, 250, 225);
DrawLine(ColorWhite(), 300, 25, 300, 225);

FillRectangle(ColorFirebrick(), 400, 25, 200, 200);
DrawLine(ColorWhite(), 400, 75, 600, 75);
DrawLine(ColorWhite(), 400, 125, 600, 125);
DrawLine(ColorWhite(), 400, 175, 600, 175);
DrawLine(ColorWhite(), 450, 25, 450, 225);
DrawLine(ColorWhite(), 500, 25, 500, 225);
DrawLine(ColorWhite(), 550, 25, 550, 225);


FillRectangle(ColorFirebrick(), 25, 275, 200, 200);
DrawLine(ColorWhite(), 25, 325, 225, 325);
DrawLine(ColorWhite(), 25, 375, 225, 375);
DrawLine(ColorWhite(), 25, 425, 225, 425);
DrawLine(ColorWhite(), 75, 275, 75, 475);
DrawLine(ColorWhite(), 125, 275, 125, 475);
DrawLine(ColorWhite(), 175, 275, 175, 475);


FillRectangle(ColorOrangeRed(), 260, 300, 80, 125);
FillTriangle(ColorOrangeRed(), 260, 300, 340, 300, 300, 250);
FillTriangle(ColorOrangeRed(), 260, 425, 300, 425, 280, 450);
FillTriangle(ColorOrangeRed(), 340, 425, 300, 425, 320, 450);
WriteLine("FRICK, CAN'T SLOW DOWN FAST ENOUGH!!!");
WriteLine();

RefreshScreen();
PlayMusic("breaking");

Delay(5000 - speed * 5);
StopMusic();


ClearScreen(ColorGreen());

FillRectangle(ColorBlack(), 250, 250, 100, 500);
FillRectangle(ColorBlack(), 250, 250, 500, 100);
FillRectangle(ColorFirebrick(), 150, 25, 200, 200);
DrawLine(ColorWhite(), 150, 75, 350, 75);
DrawLine(ColorWhite(), 150, 125, 350, 125);
DrawLine(ColorWhite(), 150, 175, 350, 175);
DrawLine(ColorWhite(), 200, 25, 200, 225);
DrawLine(ColorWhite(), 250, 25, 250, 225);
DrawLine(ColorWhite(), 300, 25, 300, 225);

FillRectangle(ColorFirebrick(), 400, 25, 200, 200);
DrawLine(ColorWhite(), 400, 75, 600, 75);
DrawLine(ColorWhite(), 400, 125, 600, 125);
DrawLine(ColorWhite(), 400, 175, 600, 175);
DrawLine(ColorWhite(), 450, 25, 450, 225);
DrawLine(ColorWhite(), 500, 25, 500, 225);
DrawLine(ColorWhite(), 550, 25, 550, 225);

FillRectangle(ColorFirebrick(), 25, 275, 200, 200);
DrawLine(ColorWhite(), 25, 325, 225, 325);
DrawLine(ColorWhite(), 25, 375, 225, 375);
DrawLine(ColorWhite(), 25, 425, 225, 425);
DrawLine(ColorWhite(), 75, 275, 75, 475);
DrawLine(ColorWhite(), 125, 275, 125, 475);
DrawLine(ColorWhite(), 175, 275, 175, 475);


FillRectangle(ColorOrangeRed(), 260, 225, 80, 125);
FillTriangle(ColorOrangeRed(), 260, 350, 300, 350, 280, 375);
FillTriangle(ColorOrangeRed(), 340, 350, 300, 350, 320, 375);

RefreshScreen();
PlayMusic("boom");

Delay(5000 - speed * 5);
StopMusic();

WriteLine("BOOM");
WriteLine();

WriteLine("BREAKING NEWs; Two adult died in a supercar crash. It was reported that the lambo driver was speeding,");
WriteLine("causing them to crash into a building as the they were unable to slow down to take the up comming turn.");
WriteLine();
WriteLine("PLEASE DRIVE CAREFULLY!!!");
WriteLine("DO NOT DRIVE FAST!!!");

