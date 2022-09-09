/******************************************************
** Program: Gold.h
** Author: Parker Choc
** Date: 05/24/2021
** Description: Gold class header
** Input: depends
** Output: depends
******************************************************/

#ifndef H_Gold
#define H_Gold

#include "Event.h"

class Gold : public Event
{
   public:
        Gold();
        void encounter() override;
        void percept() override;
};

#endif