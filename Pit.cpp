/******************************************************
** Program: Pit.cpp
** Author: Parker Choc
** Date: 05/24/2021
** Description: Pit class functions
** Input: depends
** Output: depends
******************************************************/

#include "Pit.h"

/*********************************************************************  
** Functions: Pit()
** Description: constructs the Pit class 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: constructs a Pit class
*********************************************************************/
Pit::Pit()
{
    event_type = 'P';
}

/*********************************************************************  
** Functions: encounter() and percept()
** Description: displays text specific to Pit
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: displays text either when a player is close and
**      when a player is sharing a room
*********************************************************************/
void Pit::encounter()
{
    cout << "you have fallen to your death.\n";
}

void Pit::percept()
{
    cout << "You feel a breeze.\n";
}