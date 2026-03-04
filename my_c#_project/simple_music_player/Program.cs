using static SplashKitSDK.SplashKit;

string opt, song, song_path, song_to_play;
bool flag;
flag = false;
song = "";
//"C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/817843__josefpres__piano-loops-158-efect-4-octave-long-loop-120-bpm.wav"

WriteLine("Welcome to my simple music player:");
WriteLine();
WriteLine("1: Load song");
WriteLine("2: Play song");
WriteLine("3: Stop song");
WriteLine("4: Quit");
Write("Option: ");
opt = ReadLine();


while (opt != "4")
{

    switch (opt)
    {
        case "1":
            WriteLine();
            Write("What is the name of the song: ");
            song = ReadLine();
            Write("Path to file: ");
            song_path = ReadLine();
            WriteLine();

            if (File.Exists(song_path))
            {
                LoadMusic(song, song_path);
                WriteLine($"Loading {song_path} Passed!");
            }
            else
            {
                WriteLine($"Loading {song_path} failed!");
            }
            WriteLine();

            break;

        case "2":
            Write("What is the song name: ");
            song_to_play = ReadLine();

            if (song_to_play != song)
            {
                WriteLine($"There is nothing called {song_to_play} loaded");
                WriteLine();
                break;
            }
            else
            {
                PlayMusic(song);
                flag = true;
                break;

            }

            
        case "3":

            if (flag)
            {
                StopMusic();
                flag = false;
                break;
            }
            else
            {
                WriteLine();
                WriteLine("No music is playing");
                WriteLine();
                break;
            }

        case "4":
            break;

        default:
            WriteLine("ERROR! Please enter number between 1 and 4");
            WriteLine();
            break;


    }
    WriteLine("1: Load song");
    WriteLine("2: Play song");
    WriteLine("3: Stop song");
    WriteLine("4: Quit");
    Write("Option: ");
    opt = ReadLine();
    WriteLine();

}
WriteLine("Bye");

