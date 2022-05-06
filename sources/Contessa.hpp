#include <iostream>
#include "Player.hpp"
#include <vector>
#include <string>

namespace coup
{
    class Contessa : public Player
    {
    public:
        Contessa(Game &game, const std::string &name) : Player(&game, name, "Contessa") {}
        ~Contessa() {}
        void block(Player &player); /* block the kill option from a player */
    };
}