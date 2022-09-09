/******************************************************
** Program: Pit.h
** Author: Parker Choc
** Date: 05/24/2021
** Description: Pit class header
** Input: depends
** Output: depends
******************************************************/

#ifndef H_Pit
#define H_Pit

#include "Event.h"

class Pit : public Event
{
   public:
        Pit();
        void encounter() override;
        void percept() override;
};

#endif