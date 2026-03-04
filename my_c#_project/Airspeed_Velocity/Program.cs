using static SplashKitSDK.SplashKit;

string BirdName, line;
double freq, amp, resultmax, resultmin;
const double STROUHAL_LOW_EFFICIENCY = 0.4;
const double STROUHAL_HIGH_EFFICIENCY = 0.2;

Write("Enter bird name: ");
BirdName = ReadLine();
WriteLine();

Write("Enter " + BirdName + "'s frequency: ");
line = ReadLine();
WriteLine();
freq = ConvertToDouble(line);
line = "";

Write("Enter " + BirdName + "'s amplitude: ");
line = ReadLine();
WriteLine();
amp = ConvertToDouble(line);
line = "";

resultmax = freq * amp / STROUHAL_HIGH_EFFICIENCY;
resultmin = freq * amp / STROUHAL_LOW_EFFICIENCY;

WriteLine(BirdName + "maximum air speed is " + resultmax.ToString() + "m/s and its minimum air speed is " + resultmin.ToString() + "m/s");
ReadLine();


