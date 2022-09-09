/******************************************************
** Program: Bats.cpp
** Author: Parker Choc
** Date: 05/24/2021
** Description: Bats class functions
** Input: depends
** Output: depends
******************************************************/

#include "Player.h"

/*********************************************************************  
** Functions: Player(), Player(int &x_start, int &y_start)
** Description: constructs the Player class 
** Parameters: none, &x_start, &y_start
** Pre-Conditions: none, x and y start coordinates
** Post-Conditions: constructs a Player class either at (0, 0) or at
**  (x_start, y_start)
*********************************************************************/
Player::Player()
{
    x = 0;
    y = 0;
    alive = true;
    has_gold = false;
    has_killed_wumpus = false;
}

Player::Player(int &x_start, int &y_start)
{
    x = x_start;
    y = y_start;
    alive = true;
    has_gold = false;
    has_killed_wumpus = false;
}

/*********************************************************************  
** Functions: get_x()
** Description: returns the x coordinate value 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns the int x coordinate value
*********************************************************************/
int Player::get_x()
{
    return x;
}

/*********************************************************************  
** Functions: get_y()
** Description: returns the y coordinate value 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns the int y coordinate value
*********************************************************************/
int Player::get_y()
{
    return y;
}

/*********************************************************************  
** Functions: set_coordinates()
** Description: sets the player coordinates to two passed integers 
** Parameters: int &new_x, int &new_y
** Pre-Conditions: x and y coordinates to set the player location
** Post-Conditions: player coordinates modified
*********************************************************************/
void Player::set_coordinates(int &new_x, int &new_y)
{
    x = new_x;
    y = new_y;
}

/*********************************************************************  
** Functions: reset_status()
** Description: resets the variables in this class 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: resets the variables in this class
*********************************************************************/
void Player::reset_stats()
{
    alive = true;
    has_gold = false;
    has_killed_wumpus = false;
}

/*********************************************************************  
** Functions: trigger_adjacent_rooms()
** Description: activates all of the events percept ability adjacent to
**  the player 
** Parameters: Map &my_map
** Pre-Conditions: the map that the player is in
** Post-Conditions: encounters printed to screen if any
*********************************************************************/
void Player::trigger_adjacent_rooms(Map &my_map)
{
    /*
    ** First checks if the adjacent room exists at all (not beyond border)
    ** Second checks if the adjacent room is an event
    ** Third executes percept of adjacent event
    */
    if (my_map.border_check(x + 1, y))  //right
        if (my_map(x + 1, y).not_hallway())
            my_map(x + 1, y).get_event()->percept();
    if (my_map.border_check(x - 1, y))  //left
        if (my_map(x - 1, y).not_hallway())
            my_map(x - 1, y).get_event()->percept();
    if (my_map.border_check(x, y + 1))  //down
        if (my_map(x, y + 1).not_hallway())
            my_map(x, y + 1).get_event()->percept();
    if (my_map.border_check(x, y - 1))  //up
        if (my_map(x, y - 1).not_hallway())
            my_map(x, y - 1).get_event()->percept();
}

/*********************************************************************  
** Functions: trigger_my_room()
** Description: activates the encounter on the event the player is in
** Parameters: Map &my_map
** Pre-Conditions: the map that the player is in
** Post-Conditions: does what the event does in the room the player is
**  in. Can call itself recursively in case of bats event
*********************************************************************/
void Player::trigger_my_room(Map &my_map)
{
    if (my_map(x, y).not_hallway())
    {
        my_map(x, y).get_event()->encounter();
        if (my_map(x, y).get_event_type() == 'b')   //super bats
        {
            my_map.player_drop(x, y, false, true);
            trigger_my_room(my_map);
            /*
            if ((my_map(x, y).get_event_type() != 'p') 
            && (my_map(x, y).get_event_type() != 'w'))
                trigger_adjacent_rooms(my_map); //user not dead
            */
        }
        if ((my_map(x, y).get_event_type() == 'p')  //pit and wumpus
        || (my_map(x, y).get_event_type() == 'w'))
            alive = false;
        if (my_map(x, y).get_event_type() == 'g')   //gold
        {
            has_gold = true;
            my_map(x, y).set_event(nullptr).set_event_char(' ');
        }
    }
}

/*********************************************************************  
** Functions: move()
** Description: moves the player based on the passed horizontal and
**  vertical changes, then triggers the room encounter the player moved to
** Parameters: Map &my_map, int hc, int vc
** Pre-Conditions: the map the player is in, the horizontal change 
**  and the vertical change
** Post-Conditions: moves the player and triggers the event they
**  moved to
*********************************************************************/
void Player::move(Map &my_map, int hc, int vc)
{
    if (my_map.border_check(x + hc, y + vc))
    {
        my_map(x, y).set_player(false);
        x += hc;
        y += vc;
        my_map(x, y).set_player(true);
    }
    trigger_my_room(my_map);
}

/*********************************************************************  
** Functions: shoot()
** Description: shoots an arrow in the direction of hd and vd  
** Parameters: Map &my_map, int hd, int vd, int rooms
** Pre-Conditions: the map the player is in, the direction the arrow
**  is being shot, and how many rooms the arrow has traveled + 1
** Post-Conditions: calls itself until the arrow has traveled through
**  3 rooms or has killed the wumpus or has hit a wall
*********************************************************************/
void Player::shoot(Map &my_map, int hd, int vd, int rooms)
{
    //function initially called with 1 rooms
    if (my_map.border_check(x + (hd * rooms), y + (vd * rooms)))
    {
        if (my_map(x + (hd * rooms), y + (vd * rooms)).get_event_type() == 'w')
        {
            cout << "You have killed the Wumpus!\n";
            my_map(x + (hd * rooms), y + (vd * rooms)).set_event_char(' ');
            has_killed_wumpus = true;
            return;
        }
        if (rooms >= 3)
        {
            cout << "Your arrow flew through 3 rooms and did not hit anything.\n";
            my_map.wumpus_moves();
            //trigger_adjacent_rooms(my_map);
            return;
        }
        rooms++;
        shoot(my_map, hd, vd, rooms);
    }
    else
    {
        cout << "You hit a wall.\n";
        my_map.wumpus_moves();
        //trigger_adjacent_rooms(my_map);
        return;
    }  
}