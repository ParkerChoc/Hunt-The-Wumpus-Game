/******************************************************
** Program: Bats.cpp
** Author: Parker Choc
** Date: 05/24/2021
** Description: Bats class functions
** Input: depends
** Output: depends
******************************************************/

#include "Room.h"

/*********************************************************************  
** Functions: Room()
** Description: constructs the Room class 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: constructs a Room class
*********************************************************************/
Room::Room()
{
    has_player = false;
    debug = true;
    event_inside = ' ';
    whats_inside = nullptr;
}

/*********************************************************************  
** Functions: get_event()
** Description: returns a pointer to the event inside the room 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns a pointer to the event inside the room
*********************************************************************/
Event* Room::get_event()
{
    return whats_inside;
}

/*********************************************************************  
** Functions: get_event_type()
** Description: returns a char representing the event inside the room 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns a char representing the event inside the
**  room
*********************************************************************/
char Room::get_event_type()
{
    return event_inside;
}

/*********************************************************************  
** Functions: contains_player()
** Description: returns true if the room has the player inside 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns true if the room has the player inside, 
**  returns false otherwise
*********************************************************************/
bool Room::contains_player()
{
    return has_player;
}

/*********************************************************************  
** Functions: not_hallway()
** Description: returns true if the room is not a hallway 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns true if the room is not a hallway, returns
**  false otherwise
*********************************************************************/
bool Room::not_hallway()
{
    if (event_inside == ' ')
        return false;
    return true;
}

/*********************************************************************  
** Functions: is_debug_mode()
** Description: returns whether or not it is in debug mode
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns whether or not it is in debug mode
*********************************************************************/
bool Room::is_debug_mode()
{
    return debug;
}

/*********************************************************************  
** Functions: set_event()
** Description: sets the event to the passed event pointer 
** Parameters: Event* type
** Pre-Conditions: event pointer
** Post-Conditions: returns itself after setting its event to the passed
**  event pointer
*********************************************************************/
Room& Room::set_event(Event* type)
{
    whats_inside = type;
    return *this;
}

/*********************************************************************  
** Functions: set_event_char()
** Description: sets the char representing the event to the passed char
** Parameters: char c
** Pre-Conditions: the char to set the representative char to
** Post-Conditions: sets the char representing the event
*********************************************************************/
void Room::set_event_char(char c)
{
    event_inside = c;
}

/*********************************************************************  
** Functions: set_player()
** Description: sets player to bool value passed
** Parameters: bool b
** Pre-Conditions: direction to add or remove player
** Post-Conditions: either adds or removes the player from this room
*********************************************************************/
void Room::set_player(bool b)
{
    has_player = b;
}

/*********************************************************************  
** Functions: set_debug_mode()
** Description: sets the debug mode of the room to be true or false 
** Parameters: bool mode
** Pre-Conditions: whether or not to set to debug mode
** Post-Conditions: sets the room debug mode
*********************************************************************/
void Room::set_debug_mode(bool mode)
{
    debug = mode;
}

/*********************************************************************  
** Functions: print_room()
** Description: prints the room to the screen 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: prints the room to the screen
*********************************************************************/
void Room::print_room()
{
    if (has_player)
        cout << "*";
    else
    {
        if (debug)
            cout << event_inside;
        else
            cout << " ";
    }
}