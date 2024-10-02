//
// Created by Giuliana Silva on 4/23/24.
//

#ifndef MINESWEEPER1_TILE_FUNCTIONS_H
#define MINESWEEPER1_TILE_FUNCTIONS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Tiles.h"
//#include "Tiles.cpp"

using namespace std;


int assignNumbers(vector<vector<Tiles>>& board, int x, int y) {
    int mineCount = 0;
    Tiles& currentTile = board[y][x];
    //Top left tile
    if (x > 0 && y > 0){
        currentTile.neighbors.push_back(&board[y - 1][x - 1]);
        if(board[y - 1][x - 1].hasMine) {
            mineCount += 1;
        }
    }

    //Top tile
    if (y > 0) {
        currentTile.neighbors.push_back(&board[y - 1][x]);
        if (board[y - 1][x].hasMine) {
            mineCount += 1;
        }
    }

    //Top right tile
    if (x < board[0].size() - 1 && y > 0) {
        currentTile.neighbors.push_back(&board[y - 1][x + 1]);
        if (board[y - 1][x + 1].hasMine) {
            mineCount += 1;
        }
    }

    //Left tile
    if (x > 0) {
        currentTile.neighbors.push_back(&board[y][x - 1]);
        if (board[y][x - 1].hasMine) {
            mineCount += 1;
        }
    }
    //Right tile
    if (x < board[0].size() - 1) {
        currentTile.neighbors.push_back(&board[y][x + 1]);
        if (board[y][x + 1].hasMine) {
            mineCount += 1;
        }
    }

    //Bottom left tile
    if (x > 0 && y < board.size() - 1){
        currentTile.neighbors.push_back(&board[y + 1][x - 1]);
        if(board[y + 1][x - 1].hasMine) {
            mineCount += 1;
        }
    }
    //Bottom tile
    if (y < board.size() - 1) {
        currentTile.neighbors.push_back(&board[y + 1][x]);
        if (board[y + 1][x].hasMine) {
            mineCount += 1;
        }
    }
    //Bottom right tile
    if (x < board[0].size() - 1 && y < board.size() - 1) {
        if (board[y + 1][x + 1].hasMine) {
            currentTile.neighbors.push_back(&board[y + 1][x + 1]);
            mineCount += 1;
        }
    }
    return mineCount;
}




void ShowTile(vector<vector<Tiles>>& board, int col, int row, sf::Texture& BTexture, sf::Sprite& BSprite, sf::RenderWindow& GameWindow, vector<pair<sf::Vector2f, sf::Texture>>& drawnSprites){
    if (row < board.size() && col < board[0].size()) {
        // Update the tile's revealed status
        board[row][col].revealed = true;

        int tileNum = assignNumbers(board, col, row);
        if (!board[row][col].hasMine) {
            drawnSprites.push_back({sf::Vector2f(col * 32, row * 32), BTexture});

            if (tileNum >= 1 && tileNum <= 8) {
                sf::Texture BaseTexture;
                if (!BaseTexture.loadFromFile(
                        "files/images/number_" + to_string(tileNum) +
                        ".png")) {
                    cout << "Failed to load texture" << endl;
                } else {

                    drawnSprites.push_back({sf::Vector2f(col * 32, row * 32), BaseTexture});
                }
            }
        }
    }
}



void showAdjacentTiles(vector<vector<Tiles>>& board, int i, int j, sf::Texture& BTexture, sf::Sprite& BSprite, sf::RenderWindow& GameWindow, vector<pair<sf::Vector2f, sf::Texture>>& drawnSprites) {
    Tiles &currentTile = board[j][i];
    // Checks to make sure current tile has not been flagged or revealed
    if (!currentTile.revealed && !currentTile.flagged) {
        currentTile.revealed = true;

        // Call revealTile to handle revealing the current tile
        ShowTile(board, i, j, BTexture, BSprite, GameWindow, drawnSprites);



        if (assignNumbers(board, i, j) == 0) {
            BSprite.setTexture(BTexture);
            BSprite.setPosition(i, j);
            GameWindow.draw(BSprite);

            for (Tiles *adjacentTile: currentTile.neighbors) {
                // Recursive call to reveal all valid tiles
                showAdjacentTiles(board, adjacentTile->location.x, adjacentTile->location.y, BTexture, BSprite,
                                  GameWindow, drawnSprites);


            }
        }
    }
}


//When tile is clicked on assign the tile a number based on how many mines are on the 8 surrounding tiles
vector<pair<sf::Vector2f, sf::Texture>> leftClick(vector<vector<Tiles>>& board, sf::RenderWindow& GameWindow, vector<pair<sf::Vector2f, sf::Texture>>& drawnSprites, int columns, int rows, int mines, vector<sf::Vector2f> mineCoordinates ) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(GameWindow);
    sf::Vector2f viewPos = GameWindow.mapPixelToCoords(mousePos);
    int col = viewPos.x / 32;
    int row = viewPos.y / 32;


    // Check if the clicked tile is within the bounds of the board
    if (col >= 0 && col < columns && row >= 0 && row < rows) {
        cout << "Clicked within bounds" << endl;
        if (!board[row][col].hasMine) {
            sf::Texture BTexture;
            if (!BTexture.loadFromFile("files/images/tile_revealed.png")) {
                cout << "Failed to load texture" << endl;
            } else {
                // Draw the revealed base tile
                sf::Sprite BSprite;
                BSprite.setTexture(BTexture);
                BSprite.setPosition(col * 32, row * 32);
                GameWindow.draw(BSprite);
                showAdjacentTiles(board, col, row, BTexture, BSprite, GameWindow, drawnSprites);
            }
        }


    }
    return drawnSprites;
}


//If the mouse is right clicked place a flag on the location of the click
vector<pair<sf::Vector2f, sf::Texture>> rightClick(vector<vector<Tiles>>& board, sf::RenderWindow& GameWindow, vector<pair<sf::Vector2f, sf::Texture>> drawnSprites, int columns, int rows) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(GameWindow);
    sf::Vector2f viewPos = GameWindow.mapPixelToCoords(mousePos);
    int col = viewPos.x / 32;
    int row = viewPos.y / 32;
    // Check if the clicked tile is within the bounds of the board
    if (col >= 0 && col < columns && row >= 0 && row < rows) {
        // Check if the tile is already flagged
        if (board[row][col].flagged) {
            board[row][col].flagged = false;
            size_t indexRemove = 0;
            bool found = false;
            for (size_t i = 0; i < drawnSprites.size(); ++i) {
                if (drawnSprites[i].first == sf::Vector2f(col * 32, row * 32)) {
                    found = true;
                    indexRemove = i;
                    break;
                }
            }
            if (found) {
                drawnSprites.erase(drawnSprites.begin() + indexRemove);

            }
        } else {
            // If the tile is not already flagged, flag it
            board[row][col].flagged = true;
            sf::Texture flagTexture;
            if (!flagTexture.loadFromFile("files/images/flag.png")) {
                cout << "Failed to load texture" << endl;
            } else {
                sf::Sprite flagSprite(flagTexture);
                flagSprite.setPosition(col * 32, row * 32);
                drawnSprites.push_back({sf::Vector2f(col * 32, row * 32), flagTexture});
            }
        }
    }
    return drawnSprites;
}

#endif //MINESWEEPER1_TILE_FUNCTIONS_H
