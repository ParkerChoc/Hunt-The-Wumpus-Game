/******************************************************
** Program: Bats.h
** Author: Parker Choc
** Date: 05/24/2021
** Description: Bats class header
** Input: depends
** Output: depends
******************************************************/

#ifndef H_Bats
#define H_Bats

#include "Event.h"

class Bats : public Event
{
   public:
        Bats();
        void encounter() override;
        void percept() override;
};

#endif