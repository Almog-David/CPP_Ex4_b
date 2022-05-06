#include <iostream>
#include "Contessa.hpp"
#include "Player.hpp"
#include <string>
#include <vector>
constexpr auto MAX_COINS = 10;
constexpr auto COUP_COST = 7;

namespace coup
{
    void Contessa::block(Player &player)
    {
        if (this->get_status() == 1)
        {
            this->change_status(2);
            throw std::invalid_argument("you'r out of the game");
            this->get_game()->next_turn();
        }
        if (this->get_game() != player.get_game() || player.get_status() == 2)
        {
            throw std::invalid_argument("this player is not in the game!");
        }
        if (player.role() == "Assassin" && player.player_action()[0] == "low_coup")
        {
            Player *revive = this->get_game()->find_player(player.player_action()[1]);
            revive->change_status(0);
        }
        else
        {
            throw std::invalid_argument("you can't do this action");
        }
    }
}