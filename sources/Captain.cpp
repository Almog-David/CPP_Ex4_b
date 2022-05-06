#include <iostream>
#include "Captain.hpp"
#include "Player.hpp"
#include <vector>
#include <string>
constexpr auto MAX_COINS = 10;
constexpr auto COUP_COST = 7;

namespace coup
{
    void Captain::block(Player &player)
    {
        if (this->get_game() != player.get_game() || player.get_status() == 2)
        {
            throw std::invalid_argument("this player is not in the game!");
        }
        if (player.role() == "Captain" && player.player_action()[0] == "steal")
        {
            player.set_coins(player.coins() - 2);                                         /* take from this player his 2 coin */
            Player *return_to = this->get_game()->find_player(player.player_action()[1]); /* find the player in the game*/
            return_to->set_coins(return_to->coins() + 2);                                 /* return to him his 2 coins */
        }
        else
        {
            throw std::invalid_argument("you can't do this action");
        }
    }
    void Captain::steal(Player &player)
    {
        int amount = 0;
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
        if (this->get_game() != player.get_game() || player.get_status() == 2)
        {
            throw std::invalid_argument("this player is not in the game!");
        }
        if (this->coins() >= MAX_COINS)
        {
            throw std::invalid_argument("you have 10 coins - you must do coup");
        }

        if (player.coins() == 1)
        {
            this->set_coins(this->coins() + 1);
            player.set_coins(player.coins() - 1);
            amount = 1;
        }
        else if (player.coins() >= 2)
        {
            this->set_coins(this->coins() + 2);
            player.set_coins(player.coins() - 2);
            amount = 2;
        }
        this->last_action.clear();
        this->last_action.push_back("steal");
        this->last_action.push_back(std::to_string(amount));
        this->last_action.push_back(player.get_name());
        this->get_game()->next_turn();
    }
}