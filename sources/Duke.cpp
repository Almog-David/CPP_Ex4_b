#include <iostream>
#include "Duke.hpp"
#include "Player.hpp"
#include <string>
#include <vector>
constexpr auto MAX_COINS = 10;
constexpr auto COUP_COST = 7;

namespace coup
{
    void Duke::tax()
    {
        if (!this->get_game()->game_mode())
        {
            this->get_game()->activate_game();
        }
        if (this->get_game()->turn() != this->get_name())
        {
            throw std::invalid_argument("its not your turn!");
        }
        if (this->get_status() == 1)
        {
            this->change_status(2);
            throw std::invalid_argument("you'r out of the game");
            this->get_game()->next_turn();
        }
        if (this->coins() >= MAX_COINS)
        {
            throw std::invalid_argument("you have 10 coins - you must do coup");
        }
        this->set_coins(this->coins() + 3);
        this->last_action.clear();
        this->last_action.push_back("tax");
        this->get_game()->next_turn();
    }
    void Duke::block(Player &player)
    {
        if (this->get_game() != player.get_game() || player.get_status() == 2)
        {
            throw std::invalid_argument("this player is out of the game");
        }
        if (player.player_action()[0] == "foreign_aid")
        {
            player.set_coins(player.coins() - 2);
        }
        else
        {
            throw std::invalid_argument("you can't block if he didn't do this action");
        }
    }
}