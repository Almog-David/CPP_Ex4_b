#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Player.hpp"

namespace coup
{
    class Player;
    class Game
    {
    protected:
        std::vector<coup::Player *> players_list; /* list of players */
        size_t player_turn;                       /* run index that show us which player need to play now - every turn it will move */
        bool active;                              /* tell us if the game is over or not in order to be able to return thr name of the winner */
    public:
        Game();
        ~Game() {}
        std::string turn();                           /* return the name of the player which is his turn to play. */
        void next_turn();                             /* at the end of every turn we will move the index to the currect position */
        void add_player(Player *p);                   /* add a player to the game */
        std::vector<std::string> players();           /* return the names of the active players in the game */
        Player *find_player(std::string &name) const; /* return the pointer to the player */
        std::string winner();                         /* return the name of the winner in the game */
        bool game_mode() const;                       /* return the game mode - false: deactivated or true: activated */
        void activate_game();                         /* tell us the game has start - turn to true */
    };

}