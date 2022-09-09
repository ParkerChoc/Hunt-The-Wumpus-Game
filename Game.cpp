/******************************************************
** Program: Game.cpp
** Author: Parker Choc
** Date: 05/24/2021
** Description: Game class functions
** Input: depends
** Output: depends
******************************************************/

#include "Game.h"

/*********************************************************************  
** Functions: Game()
** Description: constructs the Game class 
** Parameters: const int &size, bool debug_mode
** Pre-Conditions: the size of map and if this game is in debug mode
** Post-Conditions: constructs a Game class
*********************************************************************/
Game::Game(const int &size, bool debug_mode)
{
    srand(time(NULL));
    debug = debug_mode;
    my_map = Map(size);
    my_map.fill_rooms(debug);
    my_map.shuffle(w_x, w_y, g_x, g_y);
    my_map.player_drop(p_x, p_y, true, false);
    
    user = Player(p_x, p_y);
    arrows = 3;
}

/*********************************************************************  
** Functions: getch()
** Description: gets a user inputed char without them pressing enter
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns a char
*********************************************************************/
char Game::getch() 
{
    /*
    **  This is not my code. I found it online to solve the problem of having to 
    **  press enter with every key press. Credit:
    **  https://stackoverflow.com/questions/421860/
    */
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}

/*********************************************************************  
** Functions: player_shoot()
** Description: shoots an arrow in a given direction 
** Parameters: none
** Pre-Conditions: user has selectd to shoot
** Post-Conditions: promps for a direction and then calls function to
**  shoot in that direction, removing an arrow.
*********************************************************************/
void Game::player_shoot()
{
    char direction = getch();
    switch(direction)
    {
        case 'w' :
            cout << "shooting arrow up\n";
            user.shoot(my_map, 0, -1, 1);
            break;
        case 'a' :
            cout << "shooting arrow left\n";
            user.shoot(my_map, -1, 0, 1);
            break;
        case 's' :
            cout << "shooting arrow down\n";
            user.shoot(my_map, 0, 1, 1);
            break;
        case 'd' :
            cout << "shooting arrow right\n";
            user.shoot(my_map, 1, 0, 1);
            break;
        default :
            cout << "invalid input\n";
            break;
    }
}

/*********************************************************************  
** Functions: robot_shoot()
** Description: shoots an arrow in a semi-random direction 
** Parameters: none
** Pre-Conditions: robot has selected to shoot
** Post-Conditions: calls function to shoot in semi-random direction,
**  removing an arrow.
*********************************************************************/
void Game::robot_shoot()
{
    int direction = rand() % (4); //gives 0 - 3
    int hd; //horizontal direction
    int vd; //vertical direction
    switch(direction)
    {
        case 0 :
            //cout << "shooting arrow up\n";
            hd = 0;
            vd = -1;
            break;
        case 1 :
            //cout << "shooting arrow left\n";
            hd = -1;
            vd = 0;
            break;
        case 2 :
            //cout << "shooting arrow down\n";
            hd = 0;
            vd = 1;
            break;
        case 3 :
            //cout << "shooting arrow right\n";
            hd = 1;
            vd = 0;
            break;
        default :
            cout << "invalid input in shooting\n";
            break;       
    }

    //if where the ai wants to shoot is not at a wall
    if (my_map.border_check(user.get_x() + hd, user.get_y() + vd))
        user.shoot(my_map, hd, vd, 1);
    else
        robot_shoot();  //calls itself again if its a bad direction
}

/*********************************************************************  
** Functions: player_input()
** Description: takes in player input and calls either move or shoot
**  shoot functions 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: causes the player to move or shoot
*********************************************************************/
void Game::player_input()
{
    char test = getch();
    switch(test)
    {
        case 'w' :
            user.move(my_map, 0, -1);
            break;
        case 'a' :
            user.move(my_map, -1, 0);
            break;
        case 's' :
            user.move(my_map, 0, 1);
            break;
        case 'd' :
            user.move(my_map, 1, 0);
            break;
        case ' ' :
            if (arrows <= 0)
            {
                cout << "Sorry, you are out of arrows\n";
                break;
            }
            cout << "arrow direction:\n";
            arrows -= 1;
            player_shoot();
            break;
        default :
            cout << "invalid input\n";
            break;
    }
}

/*********************************************************************  
** Functions: robot_input()
** Description: randomly picks an input and then moves or shoots
**  according to that input
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: causes the robot to move or shoot
*********************************************************************/
void Game::robot_input()
{
    int what_to_do;
    if (arrows > 0)
        what_to_do = rand() % (5); //gives 0 - 4
    else
        what_to_do = rand() % (4); //gives 0 - 3

    switch(what_to_do)
    {
        case 0 :
            user.move(my_map, 0, -1);
            break;
        case 1 :
            user.move(my_map, -1, 0);
            break;
        case 2 :
            user.move(my_map, 0, 1);
            break;
        case 3 :
            user.move(my_map, 1, 0);
            break;
        case 4 :
            //inteliginetly decides to not shoot at walls
            arrows -= 1;
            robot_shoot();
            break;
        default :
            cout << "invalid input in movement\n";
            break;
    }
}

/*********************************************************************  
** Functions: print_status()
** Description: prints the percept() of each adjacent room, displays
**  if the user has aquired gold, has killed wumpus, and displays the
**  map.
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: prints many pieces of information to the screen
*********************************************************************/
void Game::print_status()
{
    user.trigger_adjacent_rooms(my_map);

    cout << "\tAquired gold: ";
    if (user.has_gold)
        cout << "Yes.\n";
    else
        cout << "No.\n";
    
    cout << "\tKilled Wumpus: ";
    if (user.has_killed_wumpus)
        cout << "Yes.\n";
    else
        cout << "No.\n";
    
    cout << "\tArrows left: " << arrows << "\n";       
    
    my_map.print_map();
}

/*********************************************************************  
** Functions: game_flow()
** Description: loops through, and only ends if the player dies or wins.
**  this functions as a turn facilitator
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns nothing, but only after the player has 
**  won or died
*********************************************************************/
void Game::game_flow()
{
    bool machine_plays;
    cout << "Do you wish an AI to play this round? (1 - yes) (0 - no): ";
    cin >> machine_plays;
    do
    {
        print_status();
        
        if (!machine_plays)
            player_input();
        else
            robot_input();

        //if the user is in the spot they started in and they have the gold
        if ((user.get_x() == p_x) && (user.get_y() == p_y) && (user.has_gold))
        {
            cout << "You have escaped the cave!\n";
            return;
        }
    } while (user.alive);
}

/*********************************************************************  
** Functions: randomize()
** Description: randomizes the map, puts the player in a new spot.
**  basically just restarts the game in a random configuration
** Parameters: const int &size
** Pre-Conditions: size of map
** Post-Conditions: restarts the game randomly
*********************************************************************/
void Game::randomize(const int &size)
{
    my_map = Map(size);
    my_map.fill_rooms(debug);
    my_map.shuffle(w_x, w_y, g_x, g_y);
    my_map.player_drop(p_x, p_y, true, false);
    
    user = Player(p_x, p_y);
    user.trigger_adjacent_rooms(my_map);
    arrows = 3;
}

/*********************************************************************  
** Functions: reset()
** Description: resets the game to how it initially started
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: sets everything to back how it started
*********************************************************************/
void Game::reset()
{
    //reset the location of the wumpus and gold to original positions   
    my_map.reset_stuff(w_x, w_y, g_x, g_y, user.has_killed_wumpus);  
    //reset player location and other attributes
    my_map(user.get_x(), user.get_y()).set_player(false);
    my_map(p_x, p_y).set_player(true);
    user.set_coordinates(p_x, p_y);
    user.reset_stats();
    user.trigger_adjacent_rooms(my_map);
    arrows = 3;
}