#include <iostream>
#include "Player.hpp"
#include <string>
#include <vector>

namespace coup
{
    class Ambassador : public Player
    {
    public:
        Ambassador(Game &game, const std::string &name) : Player(&game, name, "Ambassador") {}
        ~Ambassador() {}
        void transfer(Player &from, Player &to); /* transter one coin from one player to another */
        void block(Player &player);              /* block the steal option from the captain */
    };
}