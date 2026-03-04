using static SplashKitSDK.SplashKit;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int HILL_HEIGHT = SCREEN_HEIGHT * 2 / 3;
const int BOTTOM_GAP = 100;

int houseSize, wallx, wally, roofleft,roofmiddle,roofright,rooftop, roofoverhang, roofheight;
string userInput;

Write("Enter the size of the house: ");
userInput = ReadLine();
houseSize = ConvertToInteger(userInput);

wallx = (SCREEN_WIDTH - houseSize) / 2;
wally = SCREEN_HEIGHT - BOTTOM_GAP - houseSize;

roofoverhang = houseSize / 4;
roofheight = houseSize * 3 / 4;
roofleft = wallx - roofoverhang;
roofmiddle = wallx + houseSize / 2;
roofright = wallx + houseSize + roofoverhang;
rooftop = wally - roofheight;

OpenWindow("house drawing scalable", SCREEN_WIDTH, SCREEN_HEIGHT);

ClearScreen(ColorWhite());
FillEllipse(ColorBrightGreen(), 0, HILL_HEIGHT, SCREEN_WIDTH, HILL_HEIGHT);
FillRectangle(ColorGray(), wallx, wally, houseSize, houseSize);
FillTriangle(ColorFirebrick(), roofleft, wally, roofmiddle, rooftop, roofright, wally);

RefreshScreen();
Delay(5000);