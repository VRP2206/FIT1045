using static SplashKitSDK.SplashKit;



int radius = 50;


OpenWindow("Screen", 600, 600);
ClearScreen(ColorWhite());
RefreshScreen();
//WriteLine("before loop"); // test

while (!QuitRequested())
{
    ProcessEvents();
    //WriteLine("In loop before ifs"); //test

    if (KeyDown(SplashKitSDK.KeyCode.CKey))
    {
        ClearScreen(RandomColor());
        RefreshScreen();
        //WriteLine("In c"); //test
    }

    if (KeyDown(SplashKitSDK.KeyCode.SKey))
    {
        radius = 10;
        //WriteLine("r10"); //test
    }

    if (KeyDown(SplashKitSDK.KeyCode.MKey))
    {
        radius = 50;
        //WriteLine("r50"); //test
    }

    if (KeyDown(SplashKitSDK.KeyCode.LKey))
    {
        radius = 100;
        //WriteLine("r100"); //test
    }

    if (KeyDown(SplashKitSDK.KeyCode.Num5Key))
    {
        for (int i = 0; i < 100; i++)
        {
            FillCircle(RandomColor(), Rnd(1, 600), Rnd(1, 600), radius);
        }
        RefreshScreen();
        //WriteLine("5 press"); //test
    }

    if (MouseClicked(SplashKitSDK.MouseButton.LeftButton))
    {
        FillCircle(RandomColor(), MouseX(), MouseY(), radius);
        RefreshScreen();
        //WriteLine("mouse"); //test
    }

}
CloseWindow("Screen");