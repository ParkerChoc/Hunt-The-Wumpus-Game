/******************************************************
** Program: Map.cpp
** Author: Parker Choc
** Date: 05/24/2021
** Description: Map class functions
** Input: depends
** Output: depends
******************************************************/

#include "Map.h"

/*********************************************************************  
** Functions: Map(), Map(cosnt int &size)
** Description: constructs the Map class 
** Parameters: none, const int &size
** Pre-Conditions: size of the map that should be constructed, or nothing
** Post-Conditions: constructs a Map class either of size 4, or size
**  based on passed number
*********************************************************************/
Map::Map()
{
    srand(time(NULL));
    size_of_map = 4;
    grid.resize(size_of_map, vector<Room>(size_of_map));
}

Map::Map(const int &size)
{
    srand(time(NULL));
    size_of_map = size;
    grid.resize(size_of_map, vector<Room>(size_of_map));
}

/*********************************************************************  
** Functions: get_size()
** Description: returns the size of the map 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns the size of the map
*********************************************************************/
int Map::get_size()
{
    return size_of_map;
}

/*********************************************************************  
** Functions: operator()(int gx, int gy)
** Description: overloads the () operator to return a specific room
**  address given two passed coordinates
** Parameters: int gx, int gy
** Pre-Conditions: coordinates for a room
** Post-Conditions: returns a room address
*********************************************************************/
Room& Map::operator()(int gx, int gy)
{
    return grid.at(gx).at(gy);
}

/*********************************************************************  
** Functions: border_check()
** Description: returns if the given room coordinates are within the map 
** Parameters: int x, int y
** Pre-Conditions: room coordinates
** Post-Conditions: returns true if the coordinates are in the map.
**  returns false otherwise
*********************************************************************/
bool Map::border_check(int x, int y)
{
    if ((x < 0) || (y < 0))
        return false;
    if ((x >= size_of_map) || (y >= size_of_map))
        return false;
    return true;
}

/*********************************************************************  
** Functions: fill_rooms()
** Description: fills the map with the right number of events, sets 
**  rooms to debug mode or not
** Parameters: bool debug
** Pre-Conditions: whether or not the user has selected debug mode 
** Post-Conditions: assigns rooms in the map to event pointers pointing
**  to the mem addresses of specific children events. Returns itself
*********************************************************************/
Map& Map::fill_rooms(bool debug)
{
    const int nb = 2;   //number of bats
    const int np = 2;   //number of pits
    
    int y_counter = 0;
    int x_counter = 0;
    
    //fill the map with events
    //Note: this function will not work for size_of_map < 4
    for (int i = 0; i < 2; i++)
    {
        if (i < nb)
        {     
            grid.at(x_counter).at(y_counter).set_event(&b1).set_event_char('b');
            grid.at(x_counter).at(y_counter).set_debug_mode(debug);
            x_counter++;
        }
        if (i < np)
        {
            grid.at(x_counter).at(y_counter).set_event(&p1).set_event_char('p');
            grid.at(x_counter).at(y_counter).set_debug_mode(debug);
            x_counter++;
        }
        if (i < 1)
        {
            grid.at(x_counter).at(y_counter).set_event(&w1).set_event_char('w');
            grid.at(x_counter).at(y_counter).set_debug_mode(debug);
            x_counter++;
        }
        if (i < 1)
        {
            grid.at(x_counter).at(y_counter).set_event(&g1).set_event_char('g');
            grid.at(x_counter).at(y_counter).set_debug_mode(debug);
            x_counter++;
        }
        if (x_counter >= 4)
        {
            y_counter++;
            x_counter = 0;
        }
    }
    return *this;
}

/*********************************************************************  
** Functions: swap_rooms()
** Description: swithces the pinters of the two rooms
** Parameters: Room *a, Room *b
** Pre-Conditions: two room pointers
** Post-Conditions: the pointers are now pointing to each others
*********************************************************************/
void Map::swap_rooms(Room *a, Room *b)
{
    Room temp = *a;
    *a = *b;
    *b = temp;
}

/*********************************************************************  
** Functions: find_rand_room()
** Description: finds a random room in the map 
** Parameters: int &x, int &y
** Pre-Conditions: coordinates to be modified
** Post-Conditions: modifies x and y to be two rand coordinates
*********************************************************************/
void Map::find_rand_room(int &x, int &y)
{
    x = rand() % (size_of_map);
    y = rand() % (size_of_map);
}

/*********************************************************************  
** Functions: find_rand_hallway()
** Description: finds a random hallway in the map 
** Parameters: int &x, int &y
** Pre-Conditions: coordinates to be modified
** Post-Conditions: x and y modified to be the coordinates of a random
**  hallway
*********************************************************************/
void Map::find_rand_hallway(int &x, int &y)
{
    x = -1;
    y = -1;
    int x_new;
    int y_new;
    do
    {
        find_rand_room(x_new, y_new);
        if (grid.at(x_new).at(y_new).get_event_type() == ' ')
        {
            x = x_new;
            y = y_new;
        }
    } while((x < 0) && (y < 0));
}

/*********************************************************************  
** Functions: player_drop()
** Description: places the player in the map, either removing where the 
**  player origionally was or not. Also either in an empty room or not
** Parameters: int &player_x, int &player_y, bool hall, bool jump
** Pre-Conditions: the player coordinates to be modified, whether or
**  not the player should be droped in an empty room, and if the player
**  should be removed from where they currently are
** Post-Conditions: places the player as specified and modifies the 
**  given coordinates to reflect where the player is now
*********************************************************************/
void Map::player_drop(int &player_x, int &player_y, bool hall, bool jump)
{
    if (jump)
        grid.at(player_x).at(player_y).set_player(false);
    if (hall)
        find_rand_hallway(player_x, player_y);
    else
        find_rand_room(player_x, player_y);
    grid.at(player_x).at(player_y).set_player(true);
}

/*********************************************************************  
** Functions: find_type()
** Description: loops through the map and modifies the passed coordinates
**  to the coordinates of the first room found that matches the char that
**  is passed. Does not modify the coordinates if the char cannot be found 
** Parameters: int &x, int &y, char type
** Pre-Conditions: the coordinates to be modified, the char being found
** Post-Conditions: the coordinates of the char event on the map
*********************************************************************/
void Map::find_type(int &x, int &y, char type)
{
    for (int i = 0; i < size_of_map; i++)
        for (int j = 0; j < size_of_map; j++)
        {
            if (grid.at(i).at(j).get_event_type() == type)
            {
                x = i;
                y = j;
                return;
            } 
        }
}

/*********************************************************************  
** Functions: shuffle()
** Description: randomizes the map, modifies the passed coordinates
**  to reflect where the wumpus and gold start 
** Parameters: int &w_x, int &w_y, int &g_x, int &g_y
** Pre-Conditions: wumpus and gold starting coordinates
** Post-Conditions: randomizes the map, modifies wumpus and gold 
**  start coordinates
*********************************************************************/
void Map::shuffle(int &w_x, int &w_y, int &g_x, int &g_y)
{
    int x_old = 0;
    int y_old = 0;
    srand(time(NULL));

    //This loop should iterate a number of times equal to the total special events
	for (int i = 0; i < 6; i++)
	{
        //finds a random location to insert
        int x_new = rand() % (size_of_map); //gives 0 - 3
        int y_new = rand() % (size_of_map);
        swap_rooms(&grid.at(x_old).at(y_old), &grid.at(x_new).at(y_new));
        x_old++;
        if (x_old >= 4)
        {
            y_old++;
            x_old = 0;
        }
	}
    find_type(w_x, w_y, 'w');
    find_type(g_x, g_y, 'g');
}

/*********************************************************************  
** Functions: print_map()
** Description: prints to the screen the map 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: prints to the sceen the map
*********************************************************************/
void Map::print_map()
{
    cout << " /";
    for (int i = 0; i < size_of_map; i++)
    {
        cout << "---";
        if (i != size_of_map - 1)
            cout << "+";
    }
    cout << "\\\n";
    for (int y = 0; y < size_of_map; y++)
    {
        for (int x = 0; x < size_of_map; x++)
        {
            cout << " | ";
            grid.at(x).at(y).print_room();
        }
        if (y + 1 != size_of_map)
            cout << " |\n |";
        else
            cout << " |\n \\";
        for (int i = 0; i < size_of_map; i++)
        {
            cout << "---";
            if (i != size_of_map - 1)
                cout << "+";
        }
        if (y + 1 != size_of_map)
            cout << "|\n";
        else
            cout << "/\n"; 
    }
    cout << "\n";
}

/*********************************************************************  
** Functions: wumpus_moves()
** Description: the wumpus moves (75% chance) to a random empty location
**  on the map 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: displays if the wumpus woke up or not, if the 
**  wumpus woke up, it is swaped with a hallway
*********************************************************************/
void Map::wumpus_moves()
{
    int num = rand() % (4); //gives 0 - 3
    if (num > 0)
    {
        int w_x;
        int w_y;  
        bool debug_mode;
        cout << "You woke the Wumpus up, now it has moved somewhere else.\n";
        //finds where the wumpus is now
        find_type(w_x, w_y, 'w');
        //set debug mode 
        debug_mode = grid.at(w_x).at(w_y).is_debug_mode();
        //removes the wumpus entireley
        grid.at(w_x).at(w_y).set_event(nullptr).set_event_char(' ');
        //finds coordinates for a new empty location
        find_rand_hallway(w_x, w_y);
        //fils in room info where the wumpus has moved to
        grid.at(w_x).at(w_y).set_event(&w1).set_event_char('w');
        grid.at(w_x).at(w_y).set_debug_mode(debug_mode);
    }
    else
        cout << "You got lucky and the Wumpus is still asleep.\n";
}

/*********************************************************************  
** Functions: reset_stuff()
** Description: puts the gold and wumpus where they started, resurects
**  the wumpus if the wumpus has been killed 
** Parameters: int &w_x, int &w_y, int &g_x, int &g_y, bool wumpus_dead
** Pre-Conditions: wumpus and gold start coordinates, whether or not
**  the wumpus is dead
** Post-Conditions: resets the map to how it was when it started minus
**  the player
*********************************************************************/
void Map::reset_stuff(int &w_x, int &w_y, int &g_x, int &g_y, bool wumpus_dead)
{
    int old_x;
    int old_y;
    if (!wumpus_dead)
    {
        //finds where the wumpus is now
        find_type(old_x, old_y, 'w');
        //swaps that location with where the wumpus started
        swap_rooms(&grid.at(old_x).at(old_y), &grid.at(w_x).at(w_y));
    }
    else
        grid.at(w_x).at(w_y).set_event(&w1).set_event_char('w');
    //puts the gold where it started
    grid.at(g_x).at(g_y).set_event(&g1).set_event_char('g');
}