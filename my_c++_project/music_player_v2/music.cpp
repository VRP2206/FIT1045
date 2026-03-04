#include "splashkit.h"
#include <filesystem>
#include <stdio.h>

const int MAX_SONG = 100;

/**
 * struct representing details of a single song
 *
 * @field name - the name of the song
 * @field ID - a unique identifier generated for the song
 * @field path - the file path of the song on disk
 * @field love - boolean flag; true if the song is "loved"
 * @field played - the number of times the song has been played
 */
struct song_data
{
    string name;
    string ID;
    string path;
    bool love;
    int played = 0;
};

/**
 * struct representing the music player
 *
 * @field songs - an array containing all songs in the player
 * @field next_song_id - the index of the next song to be added
 */
struct music_player
{
    song_data songs[MAX_SONG];
    int next_song_id = 0;
};

/** Add a new song to the music player.
 *
 * Prompts the user for song name, path, and love status.
 * Validates that the provided path exists.
 *
 * @param m - passed by reference; the music player where the song is added
 */
void add(music_player &m)
{
    if (m.next_song_id < 100)
    {
        write("Enter the name of the song: ");
        m.songs[m.next_song_id].name = read_line();

        write("Enter the path of the song: ");
        m.songs[m.next_song_id].path = read_line();
        while (!std::filesystem::exists(m.songs[m.next_song_id].path))
        {
            write_line("The file path you entered does not exsist, try again");
            write("Enter the path of the song: ");
            m.songs[m.next_song_id].path = read_line();
        }

        string temp;
        do
        {
            write("Do you love this song[y/n]: ");
            temp = read_line();
        } while (!(temp == "y" || temp == "Y" || temp == "n" || temp == "N"));

        if (temp == "y" || temp == "Y")
        {

            m.songs[m.next_song_id].love = true;
        }
        else
        {
            m.songs[m.next_song_id].love = false;
        }

        temp = "";
        temp = "song-" + std::to_string(m.next_song_id);
        m.songs[m.next_song_id].ID = temp;

        m.songs[m.next_song_id].played = 0;

        m.next_song_id += 1;
    }
    else
    {
        write_line("No space left for new song :(");
        return;
    }

    write_line("");
    write_line("The song has been added successfully :)");
    load_music(m.songs[m.next_song_id - 1].ID, m.songs[m.next_song_id - 1].path);
}


/**
 * Search for songs by name in the music player.
 *
 * @param m passed by reference; the music player to search
 * @param name the search keyword to match against song names
 * @param matches output array; stores indexes of matching songs
 *
 * @return the number of matching songs found
 */
int search_song(music_player &m, string name, int matches[])
{
    int count = 0;
    for (int i = 0; i < m.next_song_id; i++)
    {
        if (contains(m.songs[i].name, name))
        {
            write_line(std::to_string(count + 1) + ". " + m.songs[i].name);
            matches[count] = i;
            count++;
        }
    }
    return count;
}

/**
 * Delete a song from the music player by name (and user selection).
 *
 * @param m passed by reference; the song is removed from the player
 */
void delete_song(music_player &m)
{
    write("Enter name to search: ");
    string name = read_line();
    int matches[MAX_SONG];
    int count = search_song(m, name, matches);

    if (count == 0)
    {
        write_line("No song found.");
        return;
    }

    write("Select song number to be delete: {Enter -1 if you want to cancel}");
    int choice = stoi(read_line());

    while (choice != -1 && !(choice > 0 && choice <= count))
    {
        write_line("Invalid choice.  {Enter -1 if you want to cancel}");
        write("Select song number to delete: ");
        choice = stoi(read_line());
    }
    if (choice == -1)
    {
        return;
    }

    int idx = matches[choice - 1];
    for (int i = idx; i < m.next_song_id - 1; i++)
    {
        m.songs[i] = m.songs[i + 1];
    }
    m.next_song_id--;

    write_line("Product deleted.");
}

/**
 * Update details of an existing song.
 *
 * Allows updating the song name, toggling love, and resetting play count.
 *
 * @param m passed by reference; the song details are updated
 */
void update(music_player &m)
{
    write("Enter name to search: ");
    string name = read_line();
    int matches[MAX_SONG];
    int count = search_song(m, name, matches);

    if (count == 0)
    {
        write_line("No song found.");
        return;
    }

    write("Select song number to update: ");
    int choice = stoi(read_line());

    while (!(choice > 0 && choice <= count))
    {
        write_line("Invalid choice.");
        write("Select song number to update: ");
        choice = stoi(read_line());
    }

    int idx = matches[choice - 1];

    do
    {
        write_line("What is it you wish to update");
        write_line("1. Update name");
        write_line("2. Update love");
        write_line("3. Reset times played");
        write_line("4. Quit");
        choice = stoi(read_line());

        switch (choice)
        {
        case 1:
            write("Enter new name: ");
            m.songs[idx].name = read_line();
            write_line("Name successfully updated");
            break;

        case 2:
            m.songs[idx].love = !m.songs[idx].love;
            write_line("Love successfully switch");
            break;

        case 3:
            m.songs[idx].played = 0;
            write_line("No od time played successfully reset");
            break;

        case 4:
            write_line("");
            write_line("Updated records(if any); ");
            write_line("name: " + m.songs[idx].name + " | Love: " + std::to_string(m.songs[idx].love) + " | Number of time played: " + std::to_string(m.songs[idx].played));
            return;
            break;

        default:
            write_line("Invalid choice, try again...");
            break;
        }
    } while (choice != 4);
}

/**
 * Play a selected song from the music player.
 *
 * Prompts the user to search and choose a song.
 * Increases the play count of the chosen song.
 * @param m passed by reference; the chosen song is played
 */
void play(music_player &m)
{
    write("Enter name to search: ");
    string name = read_line();
    int matches[MAX_SONG];
    int count = search_song(m, name, matches);

    if (count == 0)
    {
        write_line("No song found.");
        return;
    }

    write("Select song number to play: ");
    int choice = stoi(read_line());

    while (!(choice > 0 && choice <= count))
    {
        write_line("Invalid choice.");
        write("Select song number to update: ");
        choice = stoi(read_line());
    }

    int idx = matches[choice - 1];

    write_line("Playing music...");
    play_music(m.songs[idx].ID);
    m.songs[idx].played += 1;
}


/**
 * Pause or resume the currently playing music.
 *
 * @param is_paused passed by reference; tracks whether music is paused
 */
void pause_resume(bool &is_paused)
{
    if (music_playing() && !is_paused)
    {
        pause_music();
        is_paused = true;
        write_line("Music paused.");
    }
    else if (is_paused)
    {
        resume_music();
        is_paused = false;
        write_line("Music resumed.");
    }
    else
    {
        write_line("No music is currently playing or paused.");
    }
}

/**
 * Print details of the music player.
 *
 * Displays the number of songs, total times played,
 * and how many songs are marked as loved.
 *
 * @param m passed by constant reference; no changes are made
 */
void print_details(const music_player &m)
{
    printf("=================REPORT=================\n");
    printf("Total number of song: %d\n", m.next_song_id);

    int song_played = 0;
    for (int i = 0; i < m.next_song_id; i++)
    {
        song_played += m.songs[i].played;
    }
    printf("Total time song played: %d\n", song_played);

    int love_song = 0;
    for (int i = 0; i < m.next_song_id; i++)
    {
        if (m.songs[i].love)
        {
            love_song += 1;
        }
    }
    printf("The number of love song is: %d\n", love_song);
}

/**  Main entry point of the program.
 *
 * Provides a menu-based interface to manage songs:
 * adding, deleting, updating, playing, pausing/resuming, and printing status.
 *
 * @return program exit code (0 for successful termination)
 */

int main()
{
    music_player music;

    bool is_paused = false;
    int choice;

    do
    {
        write_line("===== Music Player =====");
        write_line("1. Add song");
        write_line("2. Delete song");
        write_line("3. Update song");
        write_line("4. Play song");
        write_line("5. Pause/resume");
        write_line("6. Print Status");
        write_line("7. Quit");

        write("Enter choice: ");
        choice = stoi(read_line());

        switch (choice)
        {
        case 1:
            write_line("");
            add(music);
            break;
        case 2:
            write_line("");
            delete_song(music);
            break;
        case 3:
            write_line("");
            update(music);
            break;
        case 4:
            write_line("");
            play(music);
            break;
        case 5:
            write_line("");
            pause_resume(is_paused);
            break;
        case 6:
            write_line("");
            print_details(music);
            break;

        case 7:
            write_line();
            write_line("Exiting...");
            break;
        default:
            write_line("");
            write_line("Invalid choice. Try again.");
        }
        write_line("");
    } while (choice != 7);

    return 0;
}


// C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/reving.wav
// C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/breaking.wav
//C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/592388__magnuswaker__car-crash-with-glass.wav
//C:/Users/Vedant/Desktop/mycode/my_c#_project/music_list/706077__robinhood76__11657-low-sounding-car-driving-away-in-rain.wav