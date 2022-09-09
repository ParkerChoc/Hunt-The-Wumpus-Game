/******************************************************
** Program: Event.h
** Author: Parker Choc
** Date: 05/24/2021
** Description: Event class header
** Input: depends
** Output: depends
******************************************************/

#ifndef H_Event
#define H_Event

using namespace std;

#include <iostream>

class Event
{
    protected:
        char event_type;
    public:
    //Constructors
        Event();
    //Getters
        char get_type();
    //Other functions
        virtual void encounter() = 0;
        virtual void percept() = 0;
};

#endif