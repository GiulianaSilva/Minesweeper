//
// Created by Giuliana Silva on 4/17/24.
//

#ifndef MINESWEEPER1_TILES_H
#define MINESWEEPER1_TILES_H

#include <SFML/Graphics.hpp>

//template <typename T>

class Tiles{
public:
    sf::Vector2i location;
    bool hasMine = false;
    bool revealed = false;
    bool flagged = false;
    std::vector<Tiles*> neighbors;


    Tiles(int x, int y);
    void setLocation(int x, int y);
    bool isRevealed();
    bool isFlagged();





};


// Constructor definition
Tiles::Tiles(int x, int y) : location(x, y) {}

// Member function to set the position of the tile
void Tiles::setLocation(int x, int y) {
    location.x = x;
    location.y = y;
}

// Member function definitions
bool Tiles::isRevealed() {
    revealed = true;
    return revealed;
}

bool Tiles::isFlagged() {
    flagged = !flagged;
    return flagged;
}





#endif //MINESWEEPER1_TILES_H
