#include <iostream>
#include "Ambassador.hpp"
#include "Player.hpp"
#include <string>
#include <vector>
constexpr auto MAX_COINS = 10;
constexpr auto COUP_COST = 7;

namespace coup
{
    void Ambassador::transfer(Player &from, Player &to)
    {
        if (!this->get_game()->game_mode())
        {
            this->get_game()->activate_game();
        }
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
        if (from.get_status() == 2 || to.get_status() == 2 || this->get_game() != from.get_game() || this->game != to.get_game())
        {
            throw std::invalid_argument("you can't transfer if one of them is not in the game");
        }
        if (this->coins() >= MAX_COINS)
        {
            throw std::invalid_argument("you have 10 coins - you must do coup");
        }
        if (from.coins() == 0)
        {
            throw std::invalid_argument("cant transfer if he has 0 coins");
        }
        from.set_coins(from.coins() - 1);
        to.set_coins(to.coins() + 1);
        this->last_action.clear();
        this->last_action.push_back("transfer");
        this->last_action.push_back(from.get_name());
        this->last_action.push_back(to.get_name());
        this->get_game()->next_turn();
    }
    void Ambassador::block(Player &player)
    {
        if (player.role() == "Captain" && player.player_action()[0] == "steal")
        {
            int amount = stoi(player.player_action()[1]);
            player.set_coins(player.coins() - amount);                                    /* take from this player his 2 coin */
            Player *return_to = this->get_game()->find_player(player.player_action()[2]); /* find the player in the game*/
            return_to->set_coins(return_to->coins() + amount);                            /* return to him his 2 coins */
        }
        else
        {
            throw std::invalid_argument("you can't do this action");
        }
    }
}