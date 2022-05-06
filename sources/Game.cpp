#include <iostream>
#include "Game.hpp"
#include <vector>
constexpr auto MAX_PLAYERS = 6;

namespace coup
{
    Game::Game()
    {
        std::vector<coup::Player *> players_list;
        this->player_turn = 0;
        this->active = false;
    }
    std::string Game::turn()
    {
        return this->players_list[(this->player_turn % this->players_list.size())]->get_name();
    }

    void Game::add_player(Player *p)
    {
        if (this->active)
        {
            throw std::invalid_argument("you can't add player while the game is on ");
        }
        if (this->players_list.size() == MAX_PLAYERS)
        {
            throw std::invalid_argument("this game can have up to 6 players!");
        }
        this->players_list.push_back(p);
    }

    std::vector<std::string> Game::players()
    {
        std::vector<std::string> active_players;
        for (Player *p : this->players_list)
        {
            if (p->get_status() == 0)
            {
                active_players.push_back(p->get_name());
            }
        }
        return active_players;
    }

    Player *Game::find_player(std::string &name) const
    {
        Player *found = nullptr;
        for (Player *p : this->players_list)
        {
            if (p->get_name() == name)
            {
                found = p;
            }
        }
        return found;
    }

    void Game::next_turn()
    {
        this->player_turn++;
        std::string next = this->turn();
        Player *next_player = this->find_player(next);
        if (next_player->get_status() == 1)
        {
            next_player->change_status(2);
        }
        while (this->players_list[this->player_turn % this->players_list.size()]->get_status() == 2)
        {
            this->player_turn++;
        }
    }

    std::string Game::winner()
    {
        if (!this->active)
        {
            throw std::invalid_argument("the game isn't start yet");
        }
        std::string winner;
        for (Player *p : this->players_list)
        {
            if (p->get_status() == 0)
            {
                if (winner.empty())
                {
                    winner = p->get_name();
                }
                else
                {
                    throw std::invalid_argument("the game is not over yet");
                }
            }
        }
        return winner;
    }
    bool Game::game_mode() const
    {
        return this->active;
    }
    void Game::activate_game()
    {
        this->active = true;
    }
}