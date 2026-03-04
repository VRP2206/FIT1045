using static SplashKitSDK.SplashKit;

string name;
double distance_travelled, time_taken, distance_to_go, time_left;

Write("What is your name: ");
name = ReadLine();
WriteLine();

WriteLine($"Hi {name}.");
WriteLine();

Write("How far have you travelled so far? Enter km: ");
distance_travelled = ConvertToDouble(ReadLine());
Write("How long has it taken? Enter minutes: ");
time_taken = ConvertToDouble(ReadLine());
WriteLine();

WriteLine($"Your average speed is {distance_travelled / (time_taken/60)} km/h");
WriteLine();

Write("How far do you have to go? Enter in km: ");
distance_to_go = ConvertToDouble(ReadLine());
WriteLine();

time_left = distance_to_go / (distance_travelled / time_taken);
WriteLine($"you will atke another {time_left} minutes before you arrived.");
WriteLine($"Total distance will be {distance_travelled + distance_to_go}");
WriteLine($"Total time will be {time_left + time_taken} minutes.");


