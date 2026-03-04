using static SplashKitSDK.SplashKit;

string music_path, music_name;
int play_for;
double initial_vol, repeat_vol;

WriteLine("Welcome to the music play test");

Write("What file would you like to load? Enter path: ");
music_path = ReadLine();
//music_path = "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/817843__josefpres__piano-loops-158-efect-4-octave-long-loop-120-bpm.wav";

Write("What should I call this music? Enter name: ");
music_name = ReadLine();

WriteLine();
WriteLine("Loading Test1 music from " + music_path);

WriteLine();
Write("How long do you want to play it for? Enter seconds: ");
play_for = ConvertToInteger(ReadLine());

Write("At what initial volume? Enter percent (0 to 1): ");
initial_vol = ConvertToDouble(ReadLine());

Write("At what repeat volume? Enter percent (0 to 1): ");
repeat_vol = ConvertToDouble(ReadLine());
//"C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/817843__josefpres__piano-loops-158-efect-4-octave-long-loop-120-bpm.wav"

LoadMusic(music_name, music_path);

WriteLine();
WriteLine($"Playing {music_name} at {initial_vol} volume for {play_for} seconds...");
PlayMusic(music_name);
SetMusicVolume(initial_vol);
Delay(play_for * 1000);
WriteLine("Stopping music");
StopMusic();

WriteLine();
WriteLine($"Playing {music_name} at {repeat_vol} volume for {play_for} seconds...");
PlayMusic(music_name);
SetMusicVolume(repeat_vol);
Delay(play_for * 1000);
WriteLine("Stopping music");
StopMusic();





