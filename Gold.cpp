/******************************************************
** Program: Gold.cpp
** Author: Parker Choc
** Date: 05/24/2021
** Description: Gold class functions
** Input: depends
** Output: depends
******************************************************/

#include "Gold.h"

/*********************************************************************  
** Functions: Gold()
** Description: constructs the Gold class 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: constructs a Gold class
*********************************************************************/
Gold::Gold()
{
    event_type = 'G';
}

/*********************************************************************  
** Functions: encounter() and percept()
** Description: displays text specific to Gold
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: displays text either when a player is close and
**      when a player is sharing a room
*********************************************************************/
void Gold::encounter()
{
    cout << "You have found the gold!\n";
}

void Gold::percept()
{
    cout << "You see a glimmer nearby.\n";
}