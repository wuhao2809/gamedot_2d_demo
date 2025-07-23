#include "core/Game.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Game game;

    if (!game.initialize())
    {
        std::cerr << "Failed to initialize game!" << std::endl;
        return 1;
    }

    game.run();
    game.shutdown();

    return 0;
}
