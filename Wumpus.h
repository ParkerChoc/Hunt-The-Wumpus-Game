/******************************************************
** Program: Wumpus.h
** Author: Parker Choc
** Date: 05/24/2021
** Description: Wumpus class header
** Input: depends
** Output: depends
******************************************************/

#ifndef H_Wumpus
#define H_Wumpus

#include "Event.h"

class Wumpus : public Event
{
   public:
        Wumpus();
        void encounter() override;
        void percept() override;
};

#endif