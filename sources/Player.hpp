#pragma once
#include <iostream>
#include "Game.hpp"
#include <vector>
#include <string>

namespace coup
{
    class Game;
    class Player
    {
    protected:
        Game *game;                           /* the game which the player is playing */
        std::string name;                     /* the player name */
        int player_coins;                     /* the amount of coins he have right now */
        std::string player_role;              /* the player role in the game */
        std::vector<std::string> last_action; /*tell us the last action the player did. will be save as (action):(on who)*/
        int status;                           /* tell us if the player is alive(0), targed by assasin(1) or dead(2) in the game */

    public:
        Player(Game *game, const std::string &name, const std::string &role);
        ~Player() {}
        void income();                            /* add 1 coin to the amount of coins of the player */
        void foreign_aid();                       /* add 2 coin to the amount of coins of the player  - can be block by some roles*/
        void coup(Player &player);                /* kill a player from the game. cost 7 coins. cant be block if cost 7 coins */
        std::string get_name() const;             /* get the player name */
        Game *get_game() const;                   /* get the player game */
        std::string role() const;                 /* return the role of the player */
        int coins() const;                        /* return the amount of coins of the player */
        void set_coins(int money);                /*set the amount of money of the player */
        int get_status() const;                   /* return the player status */
        std::vector<std::string> player_action(); /* return the player last action - get action */
        void change_status(int status);
    };
}