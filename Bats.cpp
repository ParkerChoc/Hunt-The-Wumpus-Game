/******************************************************
** Program: Bats.cpp
** Author: Parker Choc
** Date: 05/24/2021
** Description: Bats class functions
** Input: depends
** Output: depends
******************************************************/

#include "Bats.h"

/*********************************************************************  
** Functions: Bats()
** Description: constructs the Bats class 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: constructs a Bats class
*********************************************************************/
Bats::Bats()
{
    event_type = 'B';
}

/*********************************************************************  
** Functions: encounter() and percept()
** Description: displays text specific to bats
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: displays text either when a player is close and
**      when a player is sharing a room
*********************************************************************/
void Bats::encounter()
{
    cout << "you have encountered the super bats!\n";
    cout << "you have been dropped to a random location on the map\n";
}

void Bats::percept()
{
    cout << "You hear wings flapping.\n";
}