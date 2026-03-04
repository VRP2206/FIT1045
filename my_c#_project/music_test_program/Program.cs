using static SplashKitSDK.SplashKit;



LoadMusic("track1", "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/hello-world-snippet-saddle-club.ogg");
LoadMusic("track2", "C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/hello-world-snippet-saddle-club.ogg");

PlayMusic("track1");
Delay(2500);

FadeMusicOut(2000); // Fade out
Delay(2500);

FadeMusicIn("track2", 2); // Play it twice
Delay(2500);

SetMusicVolume(0.5f); // 50 %
Delay(500);

SetMusicVolume(0.75f); // 75 %
Delay(500);

StopMusic();
Delay(2500);