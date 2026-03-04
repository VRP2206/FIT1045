#include "splashkit.h"

typedef struct room_data *room_ptr;

struct path_data
{
    string description;
    room_ptr destination;
};

struct room_data
{
    string title;
    string description;
};

int read_integer(string prompt)
{
    write(prompt);
    string line = read_line();
    while (!is_integer(line))
    {
        write_line("Please enter a whole number.");
        line = read_line();
    }
    return stoi(line);
}

path_data new_path(string description, room_ptr destination)
{
    path_data path;
    path.description = description;
    path.destination = destination;

    return path;
}

room_data new_room(string title, string description)
{
    room_data room;
    room.title = title;
    room.description = description;

    return room;
}

void print_path(int idx, const path_data &path)
{
    write_line(std::to_string(idx) + ". " + path.description);
}

void print_room(room_ptr room)
{
    write_line(room->title + ", " + room->description);
}

void move_player(room_ptr &current_room, const path_data &path)
{
    current_room = path.destination;
}

int main()
{
    room_data r1 = new_room("Room 1", "You are in a happy place");
    room_data r2 = new_room("Room 2", "This is room 2");
    room_data r3 = new_room("Room 3", "This is room 3");

    path_data p1 = new_path("A large sliding door", &r2);
    path_data p2 = new_path("An open corridor", &r3);

    room_ptr current_room = &r1;

    print_room(current_room);
    print_path(0, p1);
    print_path(1, p2);

    int option = read_integer("Option: ");

    while (option < 0 || option > 1)
    {
        printf("Choose a value between 0 and 1\n");
        option = read_integer("Option: ");
    }

    if (option == 0)
    {
        move_player(current_room, p1);
    }
    else
    {
        move_player(current_room, p2);
    }

    print_room(current_room);
}
