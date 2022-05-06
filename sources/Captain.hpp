#include <iostream>
#include "Player.hpp"
#include <string>
#include <vector>

namespace coup
{
    class Captain : public Player
    {
    public:
        Captain(Game &game, const std::string &name) : Player(&game, name, "Captain") {}
        ~Captain() {}
        void block(Player &player); /* can block the steal option from a player */
        void steal(Player &player); /* steal 2 coins from a player. can be block by another captain or an ambassador */
    };
}