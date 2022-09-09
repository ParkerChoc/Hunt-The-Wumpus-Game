/******************************************************
** Program: Event.cpp
** Author: Parker Choc
** Date: 05/24/2021
** Description: Event class functions
** Input: depends
** Output: depends
******************************************************/

#include "Event.h"

/*********************************************************************  
** Functions: Event()
** Description: constructs the Event class 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: constructs a Event class
*********************************************************************/
Event::Event()
{
    event_type = 'Z';
}

/*********************************************************************  
** Functions: get_type()
** Description: returns what event this is in the form of a char 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns a char
*********************************************************************/
char Event::get_type()
{
    return event_type;
}