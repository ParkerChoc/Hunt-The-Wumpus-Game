/******************************************************
** Program: Wumpus.cpp
** Author: Parker Choc
** Date: 05/24/2021
** Description: Wumpus class functions
** Input: depends
** Output: depends
******************************************************/

#include "Wumpus.h"

/*********************************************************************  
** Functions: Wumpus()
** Description: constructs the Wumpus class 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: constructs a Wumpus class
*********************************************************************/
Wumpus::Wumpus()
{
    event_type = 'W';
}

/*********************************************************************  
** Functions: encounter() and percept()
** Description: displays text specific to Wumpus
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: displays text either when a player is close and
**      when a player is sharing a room
*********************************************************************/
void Wumpus::encounter()
{
    cout << "you have been eaten by the Wumpus\n";
}

void Wumpus::percept()
{
    cout << "You smell a terrible stench.\n";
}