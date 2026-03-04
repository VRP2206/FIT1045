using static SplashKitSDK.SplashKit;

double scale = 1;

Write("What scale do you want the house to be drawn(0-2): ");
scale = ConvertToDouble(ReadLine());

OpenWindow("House drawing", 800, 600);

ClearScreen(ColorWhite());
FillEllipse(ColorBrightGreen(), 0, 400, 800, 400);
FillRectangle(ColorGray(), 300, 300, 200, 200);
FillTriangle(ColorRed(), 250, 300, 400, 150, 550, 300);
FillCircle(ColorYellow(), 0, 0, 200);
DrawLine(ColorYellow(), 210, 25, 310, 25);
DrawLine(ColorYellow(), 25, 210, 25, 310);
DrawLine(ColorYellow(), 150, 150, 250, 250);
DrawLine(ColorYellow(), 200, 100, 300, 125);
DrawLine(ColorYellow(), 100, 200, 125, 300);

RefreshScreen();

Delay(50000);