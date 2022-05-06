#include <iostream>
#include "Player.hpp"
#include <string>
#include <vector>
#include "Game.hpp"
constexpr auto MAX_COINS = 10;
constexpr auto COUP_COST = 7;

namespace coup
{
    Player::Player(Game *game, const std::string &name, const std::string &role)
    {
        this->game = game;
        this->name = name;
        this->player_coins = 0;
        this->player_role = role;
        this->last_action = {};
        this->status = 0;
        this->game->add_player(this);
    }

    void Player::income()
    {
        if (this->get_game()->players().size() == 1)
        {
            throw std::invalid_argument("the game must have at least 2 players!");
        }
        if (!this->get_game()->game_mode())
        {
            this->get_game()->activate_game();
        }
        if (this->game->turn() != this->name)
        {
            throw std::invalid_argument("its not your turn!");
        }
        if (this->status == 1)
        {
            this->status = 2;
            throw std::invalid_argument("you'r out of the game");
            this->get_game()->next_turn();
        }
        if (this->coins() >= MAX_COINS)
        {
            throw std::invalid_argument("you have 10 coins - you must do coup");
        }
        this->set_coins(this->coins() + 1);
        this->last_action.clear();
        this->last_action.push_back("income");
        this->get_game()->next_turn();
    }

    void Player::foreign_aid()
    {
        if (this->get_game()->players().size() == 1)
        {
            throw std::invalid_argument("the game must have at least 2 players!");
        }
        if (!this->get_game()->game_mode())
        {
            this->get_game()->activate_game();
        }
        if (this->game->turn() != this->name)
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
        this->set_coins(this->coins() + 2);
        this->last_action.clear();
        this->last_action.push_back("foreign_aid");
        this->get_game()->next_turn();
    }

    void Player::coup(Player &p)
    {
        if (this->game->turn() != this->name)
        {
            throw std::invalid_argument("its not your turn!");
        }
        if (this->get_status() == 1)
        {
            this->change_status(2);
            throw std::invalid_argument("you'r out of the game");
            this->get_game()->next_turn();
        }
        if (this->game != p.game || p.get_status() == 2)
        {
            throw std::invalid_argument("this player is not in the game!");
        }
        if (Player::coins() < COUP_COST)
        {
            throw std::invalid_argument("you don't have enough coins for this action");
        }
        this->set_coins(this->coins() - COUP_COST);
        p.change_status(2);
        this->last_action.clear();
        this->last_action.push_back("coup:");
        this->last_action.push_back(p.get_name());
        this->get_game()->next_turn();
    }

    std::string Player::get_name() const
    {
        return this->name;
    }

    Game *Player::get_game() const
    {
        return this->game;
    }

    std::string Player::role() const
    {
        return this->player_role;
    }

    int Player::coins() const
    {
        return this->player_coins;
    }

    void Player::set_coins(int money)
    {
        this->player_coins = money;
    }

    std::vector<std::string> Player::player_action()
    {
        return this->last_action;
    }

    int Player::get_status() const
    {
        return this->status;
    }

    void Player::change_status(int status)
    {
        this->status = status;
    }
}