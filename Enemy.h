//
//      Created by Goodecheeseburgers on 20/04/2020.
//      SomeRPG. A C++ console role playing game.
//      Copyright (C) 2020 - goodecheeseburgers@gmail.com
//
//      https://github.com/Cheeseborgers/SomeRPG
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

#ifndef UNTITLED_ENEMY_H
#define UNTITLED_ENEMY_H

#include <iostream>
#include <memory>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Enemy {

private:
    sf::RectangleShape shape;

    int type;
    float velocityY;
    sf::Color color;
    sf::Vector2f size;
    float posY{};

public:

    // Constructor
    Enemy(sf::RenderTarget &target, int type);

    virtual ~Enemy();

    // Accessors
    inline int getPointsGained() const { return (this->type * 2) + 2; };

    inline sf::RectangleShape getShape() const { return this->shape; };


    // Methods
    void initAttributes();

    void update();

    void render(sf::RenderTarget &target) const;
};


#endif //UNTITLED_ENEMY_H
