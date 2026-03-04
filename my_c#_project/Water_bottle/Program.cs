using static SplashKitSDK.SplashKit;
string line;
int percentfull;
double waterHeight, waterY;

const int window_height = 600;
const int window_width = 600;
const int BOTTLE_RADIUS = 80;
const int BOTTLE_HEIGHT = 400;
const int BOTTLe_diameter = 2 * BOTTLE_RADIUS;
const int BOTTLE_CENTER_X = window_width / 2;
const int BOTTLE_LEFT_X = BOTTLE_CENTER_X - BOTTLE_RADIUS;
const int BOTTLE_RIGHT_X = BOTTLE_CENTER_X + BOTTLE_RADIUS;
const int BOTTLE_BASE_Y = window_height - BOTTLE_RADIUS - 5;
const int BOTTLE_TOP_Y = BOTTLE_BASE_Y - BOTTLE_HEIGHT;

Write("Enter the percentage at which the bottle is full: ");
line = ReadLine();

percentfull = ConvertToInteger(line);
line = "";

waterHeight = BOTTLE_HEIGHT * percentfull / 100;
waterY = BOTTLE_BASE_Y - waterHeight;

OpenWindow("Water Bottle Visualiser!", 600, 600);
ClearScreen(ColorWhite());

FillCircle(ColorBlue(), BOTTLE_CENTER_X, waterY, BOTTLE_RADIUS);
FillCircle(ColorBlue(), BOTTLE_CENTER_X, BOTTLE_BASE_Y, BOTTLE_RADIUS);
FillRectangle(ColorBlue(), BOTTLE_LEFT_X, waterY, BOTTLe_diameter, waterHeight);
DrawLine(ColorBlack(), BOTTLE_LEFT_X, BOTTLE_TOP_Y, BOTTLE_LEFT_X, BOTTLE_BASE_Y);
DrawLine(ColorBlack(), BOTTLE_RIGHT_X, BOTTLE_TOP_Y, BOTTLE_RIGHT_X, BOTTLE_BASE_Y);
DrawCircle(ColorBlack(), BOTTLE_CENTER_X, BOTTLE_TOP_Y, BOTTLE_RADIUS);

RefreshScreen();
Delay(50000);














