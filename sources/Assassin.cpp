#include <iostream>
#include "Assassin.hpp"
#include "Player.hpp"
#include <vector>
#include <string>
constexpr auto MAX_COINS = 10;
constexpr auto COUP_COST = 7;

namespace coup
{
    void Assassin::coup(Player &player)
    {
        if (this->get_game()->turn() != this->get_name())
        {
            throw std::invalid_argument("its not your turn!");
        }
        if (this->status == 1)
        {
            this->change_status(2);
            throw std::invalid_argument("you'r out of the game");
            this->get_game()->next_turn();
        }
        if (this->get_game() != player.get_game() || player.get_status() == 2)
        {
            throw std::invalid_argument("this palyer is not in the game");
        }
        if (this->coins() < 3)
        {
            throw std::invalid_argument("you don't have enough coins for this action");
        }
        if (this->coins() >= COUP_COST)
        {
            Player::coup(player);
        }
        else
        {
            this->set_coins(this->coins() - 3);
            player.change_status(1);
            this->last_action.clear();
            this->last_action.push_back("low_coup");
            this->last_action.push_back(player.get_name());
            this->get_game()->next_turn();
        }
    }
}