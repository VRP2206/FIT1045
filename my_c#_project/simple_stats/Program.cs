using static SplashKitSDK.SplashKit;

string tempval, choice;
int count;
double val, total, min, max;

WriteLine("Welcom to the simpke stats calculator: ");
WriteLine();

Write("Enter value: ");
tempval = ReadLine();
min = ConvertToDouble(tempval);
max = ConvertToDouble(tempval);
total = ConvertToDouble(tempval);
count = 1;
tempval = "";

WriteLine($"Count: {count}");
WriteLine($"Total: {total}");
WriteLine($"Min: {min}");
WriteLine($"Max: {max}");
WriteLine($"Average: {total / count}");
WriteLine();

Write("Add another value: [y/n] ");
choice = ReadLine();

do
{
    Write("Enter value: ");
    tempval = ReadLine();
    val = ConvertToDouble(tempval);
    if (val < min)

    {
        min = val;
    }

    if (val > max)
    {
        max = val;
    }

    total += ConvertToDouble(tempval);
    count += 1;
    tempval = "";

    WriteLine($"Count: {count}");
    WriteLine($"Total: {total}");
    WriteLine($"Min: {min}");
    WriteLine($"Max: {max}");
    WriteLine($"Average: {total / count}");
    WriteLine();

    Write("Add another value: [y/n] ");
    choice = ReadLine();

} while (choice == "y");

WriteLine("I hope you got the information you are after!");
