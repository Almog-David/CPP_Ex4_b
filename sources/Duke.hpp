#include <iostream>
#include "Player.hpp"
#include <vector>
#include <string>

namespace coup
{
    class Duke : public Player
    {
    public:
        Duke(Game &game, const std::string &name) : Player(&game, name, "Duke") {}
        ~Duke() {}
        void tax();                 /* take 3 coins without being block */
        void block(Player &player); /* can block the foreign_aid from a player */
    };
}
