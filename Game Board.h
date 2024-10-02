//
// Created by Giuliana Silva on 4/16/24.
//
#ifndef MINESWEEPER1_GAME_BOARD_H
#define MINESWEEPER1_GAME_BOARD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Tiles.h"
#include "Tile Functions.h"
#include "Texture Manager.h"
#include "Leader Board.h"

using namespace std;

#include <map>


//Function to display cover Tiles
void displayCoverTile(int columns, int rows,sf::RenderWindow& GameWindow){
    //Making base tile texture based on amount of columns
    TextureManager textureManager;
    sf::Texture CoverTexture = textureManager.getTexture("tile_hidden.png");
    sf::Sprite BaseSprite;
    BaseSprite.setTexture(CoverTexture);

    // Calculate the width and height of each texture
    const float textureWidth = CoverTexture.getSize().x;
    const float textureHeight = CoverTexture.getSize().y;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            float x = col * textureWidth;
            float y = row * textureHeight;
            BaseSprite.setPosition(x, y);
            GameWindow.draw(BaseSprite);
        }
    }
}

void displayBaseTile(int rows, int columns, sf::RenderWindow& window, TextureManager& textureManager) {
    sf::Texture bTexture = textureManager.getTexture("tile_revealed.png");
    sf::Sprite bSprite(bTexture);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            bSprite.setPosition(j * 32, i * 32); // Assuming each tile is 32x32 pixels
            window.draw(bSprite);
        }
    }
}

//Function to generate coordinates for mines
vector<sf::Vector2f> loadMines(vector<vector<Tiles>>& board, int rows, int columns, int mines, sf::RenderWindow& window) {
    srand(static_cast<unsigned int>(time(nullptr)));
    unsigned int seed = rand();

    vector<sf::Vector2f> mineCoordinates;
    vector<int> uniqueCoordinates;

    // Reset all Tiles objects in the board
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j].hasMine = false;
            board[i][j].flagged = false;
            if (board[i][j].revealed) {
                board[i][j].revealed = false;
            }
        }
    }
    // Places mines randomly on tiles
    for (int i = 0; i < mines; i++) {
        int tileX, tileY;
        int coordinate;

        while (true) {
            tileX = rand() % columns;
            tileY = rand() % rows;
            coordinate = tileY * columns + tileX;

            // Check if the coordinate is unique
            if (find(uniqueCoordinates.begin(), uniqueCoordinates.end(), coordinate) == uniqueCoordinates.end()) {
                break;
            }
        }
        int mineX = tileX * 32;
        int mineY = tileY * 32;

        if (tileX >= 0 && tileX < columns && tileY >= 0 && tileY < rows) {
            board[tileY][tileX].hasMine = true;
            mineCoordinates.push_back(sf::Vector2f(mineX, mineY));
            uniqueCoordinates.push_back(coordinate);
        }
    }
    return mineCoordinates;
}


//Function to display Mines
void showMines(vector<sf::Vector2f> mineCoordinates, sf::RenderWindow& window ){
    TextureManager textureManager;
    sf::Texture mineTexture = textureManager.getTexture("mine.png");
    sf::Sprite mineSprite(mineTexture);
    for (const auto &position: mineCoordinates) {
        mineSprite.setPosition(position);
        window.draw(mineSprite);
    }
}

void showFlags(vector<sf::Vector2f> mineCoordinates, sf::RenderWindow& window ){
    TextureManager textureManager;
    sf::Texture flagTexture = textureManager.getTexture("flag.png");
    sf::Sprite flagSprite(flagTexture);
    sf::Texture CcoverTexture = textureManager.getTexture("tile_hidden.png");
    sf::Sprite BbaseSprite(CcoverTexture);

    for (const auto &position: mineCoordinates) {
        BbaseSprite.setPosition(position);
        window.draw(BbaseSprite);
        flagSprite.setPosition(position);
        window.draw(flagSprite);

    }

}

//Update mine count
void updateMineCountSprites(int RemainingMines, sf::Sprite& FirstNumSprite, sf::Sprite& NegNumSprite, sf::Sprite& SecondNumSprite) {

    int RM;
    int RM1;
    int RM2;


    if (RemainingMines >= 100) {
        RM = (RemainingMines / 100) * 21;
        RM1 = ((RemainingMines / 10) % 10) * 21;
        RM2 = (RemainingMines % 10) * 21;

    } else if (RemainingMines >= 0 && RemainingMines < 100) {
        RM = 0;
        RM1 = (RemainingMines / 10) * 21;
        RM2 = (RemainingMines % 10) * 21;


    } else if (RemainingMines < 0 && RemainingMines > -100) {
        RM = 210;
        RM1 = abs(RemainingMines / 10) * 21;
        RM2 = abs(RemainingMines % 10) * 21;

    } else if (RemainingMines <= -100) {
        RM = 210;
        RM1 = ((abs(RemainingMines) / 10) % 10) * 21;
        RM2 = (abs(RemainingMines) % 10) * 21;
    }

    FirstNumSprite.setTextureRect(sf::IntRect(RM1, 0, 21, 32));
    NegNumSprite.setTextureRect(sf::IntRect(RM, 0, 21, 32));
    SecondNumSprite.setTextureRect(sf::IntRect(RM2, 0, 21, 32));
}

void updateClockSprites(int elapsedTime, sf::Sprite& FirstClockSprite, sf::Sprite& SecondClockSprite, sf::Sprite& ThirdClockSprite, sf::Sprite& FourthClockSprite) {
    // Convert elapsed time to int seconds
    int totalSeconds = elapsedTime;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    int M1 = minutes / 10;
    int M2 = minutes % 10;
    int S1 = seconds / 10;
    int S2 = seconds % 10;

    // Update texture rectangles for minutes
    FirstClockSprite.setTextureRect(sf::IntRect((21 * M1), 0, 21, 32));
    SecondClockSprite.setTextureRect(sf::IntRect((21 * M2), 0, 21, 32));

    // Update texture rectangles for seconds
    ThirdClockSprite.setTextureRect(sf::IntRect((21 * S1), 0, 21, 32));
    FourthClockSprite.setTextureRect(sf::IntRect((21 * S2), 0, 21, 32));
}


bool checkForWin(const vector<vector<Tiles>>& board) {
    for (const auto& row : board) {
        for (const auto& tile : row) {
            if (!tile.hasMine && !tile.revealed) {
                return false;
            }
        }
    }
    return true;
}



//Opens the game window
void GameWindow(int columns, int rows, int mines, string username) {

    // Making Game Window
    sf::RenderWindow GameWindow(sf::VideoMode((columns * 32), (rows * 32) + 100), "Minesweeper");

    TextureManager textureManager;
    int RemainingMines = mines;

    // Saves the tile coordinates into the Tiles class.
    vector<vector<Tiles>> board;
    for (int i = 0; i < rows; ++i) {
        std::vector<Tiles> row;
        for (int j = 0; j < columns; ++j) {
            Tiles tile(j, i);
            row.push_back(tile);
        }
        board.push_back(row);
    }

    //vector<sf::Vector2f> mineCoordinates ;
    vector<sf::Vector2f> mineCoordinates = loadMines(board, rows, columns, mines, GameWindow);

   //Textures for bottom buttons
   //Reset Button
   sf::Texture ResetTexture =  textureManager.getTexture("face_happy.png");
    sf::Sprite ResetSprite;
    ResetSprite.setTexture(ResetTexture);
    ResetSprite.setPosition(((columns/2.0)*32)-32, 32*(rows+0.5));

    sf::Sprite ResetSpriteSave;
    ResetSpriteSave.setTexture(ResetTexture);
    ResetSpriteSave.setPosition(((columns/2.0)*32)-32, 32*(rows+0.5));

    //Lin face
    sf::Texture WinTexture =  textureManager.getTexture("face_win.png");
    sf::Sprite WinSprite;
    WinSprite.setTexture(WinTexture);
    WinSprite.setPosition(((columns/2.0)*32)-32, 32*(rows+0.5));

    //Loss face
    sf::Texture LossTexture =  textureManager.getTexture("face_lose.png");
    sf::Sprite LossSprite;
    LossSprite.setTexture(LossTexture);
    LossSprite.setPosition(((columns/2.0)*32)-32, 32*(rows+0.5));



    //Reveal Mines Button
    sf::Texture RevealMinesTexture =  textureManager.getTexture("debug.png");
    sf::Sprite RevealMineSprite;
    RevealMineSprite.setTexture(RevealMinesTexture);
    RevealMineSprite.setPosition((columns*32)-304, 32*(rows+0.5));

    //Pause Button
    sf::Texture PauseTexture = textureManager.getTexture("pause.png");
    sf::Sprite PauseSprite;
    PauseSprite.setTexture(PauseTexture);
    PauseSprite.setPosition((columns*32)-240, 32*(rows+0.5));

    //Play Button
    sf::Texture PlayTexture = textureManager.getTexture("play.png");
    sf::Sprite PlaySprite;
    PlaySprite.setTexture(PlayTexture);
    PlaySprite.setPosition((columns*32)-240, 32*(rows+0.5));

    //Leader board button
    sf::Texture LeaderBTexture = textureManager.getTexture("leaderboard.png");
    sf::Sprite LeaderSprite;
    LeaderSprite.setTexture(LeaderBTexture);
    LeaderSprite.setPosition((columns*32)-176, 32*(rows+0.5));


    //texture for timer and mine count
    sf::Texture& Numbers = textureManager.getTexture("digits.png");

    sf::Sprite FirstNumSprite;
    FirstNumSprite.setTexture(Numbers);
    FirstNumSprite.setPosition(33,32*(rows + 0.5)+16);


    sf::Sprite NegNumSprite;
    NegNumSprite.setTexture(Numbers);
    NegNumSprite.setPosition(12,32*(rows + 0.5)+16);

    sf::Sprite SecondNumSprite;
    SecondNumSprite.setTexture(Numbers);
    SecondNumSprite.setPosition(54,32*(rows + 0.5)+16);

    updateMineCountSprites(RemainingMines, FirstNumSprite, NegNumSprite,  SecondNumSprite);

 //Clock Display
    // Minutes
    sf::Sprite FirstClockSprite;
    FirstClockSprite.setTexture(Numbers);
    FirstClockSprite.setPosition((columns * 32) - 97, 32 * (rows + 0.5) + 16);
    FirstClockSprite.setTextureRect(sf::IntRect(21, 0, 21, 32));

    sf::Sprite SecondClockSprite;
    SecondClockSprite.setTexture(Numbers);
    SecondClockSprite.setPosition(FirstClockSprite.getPosition().x +21, 32 * (rows + 0.5) + 16);
    SecondClockSprite.setTextureRect(sf::IntRect(42, 0, 21, 32));


    // Seconds
    sf::Sprite ThirdClockSprite;
    ThirdClockSprite.setTexture(Numbers);
    ThirdClockSprite.setPosition((columns * 32) - 54, 32 * (rows + 0.5) + 16);
    ThirdClockSprite.setTextureRect(sf::IntRect(63, 0, 21, 32));

    sf::Sprite FourthClockSprite;
    FourthClockSprite.setTexture(Numbers);
    FourthClockSprite.setPosition(ThirdClockSprite.getPosition().x + 21, 32 * (rows + 0.5) + 16);
    FourthClockSprite.setTextureRect(sf::IntRect(0, 0, 21, 32));


    sf:: Clock clock;


    // Vector to store the position and texture of the drawn sprite
    vector<pair<sf::Vector2f, sf::Texture>> drawnSprites;


    bool debugMode = false;
    bool paused = false;
  bool LB = false;
  bool LB2= false;


    //Time
    int savedTime = 0;
    int Rtime = 100000000;

    bool win = false;
    bool gameOver = false;

    while (GameWindow.isOpen()) {
        // Initialize with an invalid value
        // int previousSecond = -1;

        sf::Event event;
        while (GameWindow.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                GameWindow.close();
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(GameWindow);
            sf::Vector2f viewPos = GameWindow.mapPixelToCoords(mousePos);
            int col = viewPos.x / 32;
            int row = viewPos.y / 32;

//if(!gameOver){
            // Handels Left click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (gameOver == false) {

                    if (col >= 0 && col < columns && row >= 0 && row < rows) {
                        if (board[row][col].hasMine) {
                            // End the game
                            cout << "Game Over! You clicked onnnn a mine." << endl;

                            ResetSprite = LossSprite;
                            gameOver = true;
                            if(debugMode == true){
                                debugMode = false;
                            }
                            debugMode = !debugMode;
                            paused = !paused;
                            if (paused) {
                                // Store the current elapsed time
                                savedTime += clock.getElapsedTime().asSeconds();
                            } else {
                                // Restart the clock
                                clock.restart();
                            }
                            cout<<savedTime<<endl;
                            //paused = false;
                            // You can add more game over logic here, such as displaying a message or resetting the game
                        } else {
                            leftClick(board, GameWindow, drawnSprites, columns, rows, mines, mineCoordinates);
                        }
                    }
                    else {

                        if (RevealMineSprite.getGlobalBounds().contains(viewPos)) {
                            //toggles debug mode
                            debugMode = !debugMode;
                        }
                    }
                    //pauses game
                     if (PauseSprite.getGlobalBounds().contains(viewPos)) {
                            //toggles pause
                            paused = !paused;
                            if (paused) {

                                // Draw the clock with the saved time
                                savedTime += clock.getElapsedTime().asSeconds();

                                updateClockSprites(savedTime, FirstClockSprite, SecondClockSprite, ThirdClockSprite, FourthClockSprite);
                            } else {

                                // Draw the clock with the current elapsed time

                                float runningTime = clock.getElapsedTime().asSeconds() + savedTime;
                                updateClockSprites(runningTime, FirstClockSprite, SecondClockSprite, ThirdClockSprite, FourthClockSprite);
                            }

                        }

                } //closes game loop

//checks for win everytime a tile is clicked on
                if (ResetSprite.getGlobalBounds().contains(viewPos)) {
                    Rtime = 100000000;
                    RemainingMines = mines;
                    updateMineCountSprites(RemainingMines, FirstNumSprite, NegNumSprite, SecondNumSprite);
                    win = false;
                    ResetSprite = ResetSpriteSave;
                    paused = false;
                    debugMode = false;
                    gameOver = false;
                    savedTime = clock.getElapsedTime().asSeconds();
                    cout << savedTime << endl;
                    clock.restart();
                    savedTime = 0;
                    drawnSprites.clear();
                    mineCoordinates = loadMines(board, rows, columns, mines, GameWindow);
                    displayCoverTile(columns, rows, GameWindow);


                }
                //leader board pops up
                else if (LeaderSprite.getGlobalBounds().contains(viewPos)) {
                    LB2 = !LB2;
                    LB = !LB;

                    if (LB) {
                        // Store the current elapsed time
                        savedTime += clock.getElapsedTime().asSeconds();
                    } else {
                        // Restart the clock
                        clock.restart();
                    }

// Open the leaderboard window
                }

// Player wins
                if (!gameOver && checkForWin(board)) {
                    float runningTime = clock.getElapsedTime().asSeconds() + savedTime;

                    debugMode = false;

                    Rtime = runningTime;

                    RemainingMines = 0;
                    updateMineCountSprites(RemainingMines, FirstNumSprite, NegNumSprite, SecondNumSprite);
                    GameWindow.draw(FirstNumSprite);
                    GameWindow.draw(NegNumSprite);
                    GameWindow.draw(SecondNumSprite);
                    ResetSprite = WinSprite;
                    GameWindow.draw(ResetSprite);

                    gameOver = true;
                    paused = !paused;
                    if (paused) {
                        // Store the current elapsed time
                        savedTime += clock.getElapsedTime().asSeconds();
                    } else {
                        // Restart the clock
                        clock.restart();
                    }
                    showFlags(mineCoordinates, GameWindow);
                    win = true;
                    GameWindow.display();
                   leaderBoardWindow(columns, rows, username, Rtime);
                }
            }
        //Handels Right click
        if (gameOver == false) {

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(GameWindow);
                sf::Vector2f viewPos = GameWindow.mapPixelToCoords(mousePos);
                int col = viewPos.x / 32;
                int row = viewPos.y / 32;

                drawnSprites = rightClick(board, GameWindow, drawnSprites, columns, rows);

                if (board[row][col].flagged == true) {
                    RemainingMines -= 1;
                    updateMineCountSprites(RemainingMines, FirstNumSprite, NegNumSprite, SecondNumSprite);
                } else {
                    RemainingMines += 1;
                    updateMineCountSprites(RemainingMines, FirstNumSprite, NegNumSprite, SecondNumSprite);
                }
            }
        }
            // Clear the window
            GameWindow.clear(sf::Color::White);
            //Cover Mines
            displayCoverTile(columns, rows, GameWindow);


//draw all
            GameWindow.draw(ResetSprite);
            GameWindow.draw(RevealMineSprite);
            GameWindow.draw(PauseSprite);
            GameWindow.draw(LeaderSprite);
            GameWindow.draw(FirstNumSprite);
            GameWindow.draw(NegNumSprite);
            GameWindow.draw(SecondNumSprite);

           GameWindow.draw( FirstClockSprite);
           GameWindow.draw( SecondClockSprite);
            GameWindow.draw( ThirdClockSprite);
            GameWindow.draw( FourthClockSprite);

            // Draw stored sprites
            for (const auto &spriteData: drawnSprites) {
                sf::Sprite BaseSprite;
                BaseSprite.setTexture(spriteData.second);
                BaseSprite.setPosition(spriteData.first);
                GameWindow.draw(BaseSprite);

            }
//check for debugMode
            if (debugMode) {
                showMines(mineCoordinates, GameWindow);
            }
            if(win){
                displayCoverTile(columns, rows, GameWindow);
                GameWindow.display();

            }

            //checks for pause button
            if (paused) {
                    if(gameOver == false) {
                        displayBaseTile(rows, columns, GameWindow, textureManager);
                    }

                GameWindow.draw(PlaySprite);

                // Draw the clock with the saved time
                updateClockSprites(savedTime, FirstClockSprite, SecondClockSprite, ThirdClockSprite, FourthClockSprite);
                clock.restart();
            } else {

                // Draw the clock with the current elapsed time

                GameWindow.draw(PauseSprite);
                float runningTime = clock.getElapsedTime().asSeconds() + savedTime;
                updateClockSprites(runningTime, FirstClockSprite, SecondClockSprite, ThirdClockSprite, FourthClockSprite);

            }

            if (LB2) {
                if(gameOver == false) { // Check if the game is not over
                    displayBaseTile(rows, columns, GameWindow, textureManager);
                }
                LB2 = !LB2;
            }

            if (LB) {
                GameWindow.display();
                if(gameOver == false) {
                    leaderBoardWindow(columns, rows, username, Rtime);
                }

                // Draw the clock with the saved time
                updateClockSprites(savedTime, FirstClockSprite, SecondClockSprite, ThirdClockSprite, FourthClockSprite);
                clock.restart();
                LB = !LB;
            } else {

                // Draw the clock with the current elapsed time
                float runningTime = clock.getElapsedTime().asSeconds() + savedTime;
                updateClockSprites(runningTime, FirstClockSprite, SecondClockSprite, ThirdClockSprite, FourthClockSprite);
            }

            GameWindow.display();
        }
    }


}




#endif //MINESWEEPER1_GAME_BOARD_H
