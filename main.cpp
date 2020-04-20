//
//      Created by Goodecheeseburgers on 19/04/2020.
//      attack-of-the-squares.  A simple C++ / SFML game about squares.
//      Copyright (C) 2020 - goodecheeseburgers@gmail.com
//
//      https://github.com/Cheeseborgers/attack-of-the-squares
//
//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "Game.h"

int main() {
    // Init srand
    std::srand(static_cast<unsigned >(std::time(nullptr)));
    Game game;

    // Game loop
    while (game.isRunning() && !game.getEndGame()) {
        game.update(); // Update
        game.render(); // Render
    }

    // End of application
    return 0;
}