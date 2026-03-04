using static SplashKitSDK.SplashKit;

string name, temp;
double how_much_to_save, money_have, save_per_week;
int time_before_purchace;

Write("What are you saving for? Enter title: ");
name = ReadLine();

Write("How much do you need to save? Enter dollars: ");
temp = ReadLine();
how_much_to_save = ConvertToInteger(temp);
temp = "";
WriteLine();

Write("How long before the purchase? Enter weeks: ");
temp = ReadLine();
time_before_purchace = ConvertToInteger(temp);
temp = "";

Write("How much do you have already? Enter dollars: ");
temp = ReadLine();
money_have = ConvertToInteger(temp);
temp = "";

Write("How much can you save each week? Enter dollars: ");
temp = ReadLine();
save_per_week = ConvertToInteger(temp);
temp = "";
WriteLine();

WriteLine($"For the Holiday, you need to save {(how_much_to_save - money_have) / time_before_purchace} dollars a week");
WriteLine($"Based on current savings you will need {(how_much_to_save - money_have) / save_per_week} weeks to save ${how_much_to_save}");
