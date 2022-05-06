#include <iostream>
#include "Player.hpp"
#include <string>
#include <vector>

namespace coup
{
    class Assassin : public Player
    {
    public:
        Assassin(Game &game, const std::string &name) : Player(&game, name, "Assassin") {}
        ~Assassin() {}
        void coup(Player &player); /* kill a player from the game. cost 3 coins. can be clock by some roles */
    };
}