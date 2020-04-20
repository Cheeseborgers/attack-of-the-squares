#include "Game.h"

int main()
{
    // Init srand
    std::srand(static_cast<unsigned >(std::time(nullptr)));
    Game game;

    // Game loop
    while (game.isRunning() && !game.getEndGame())
    {
        game.update(); // Update
        game.render(); // Render
    }

    // End of application
    return 0;
}