//
// Created by Giuliana Silva on 4/23/24.
//

#ifndef MINESWEEPER1_TEXTURE_MANAGER_H
#define MINESWEEPER1_TEXTURE_MANAGER_H

#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class TextureManager {
private:
    std::map<std::string, sf::Texture> textures;

public:
    TextureManager() {
        loadTextures();
    }

    // Load all textures
    void loadTextures() {
        // Load number textures
        for (int i = 1; i <= 8; ++i) {
            sf::Texture texture;
            std::string filename = "files/images/number_" + std::to_string(i) + ".png";
            if (!texture.loadFromFile(filename)) {
                std::cout << "Failed to load texture: " << filename << std::endl;
            }
            textures["number_" + std::to_string(i)] = texture;
        }

        // Load cover texture
        sf::Texture coverTexture;
        std::string coverFilename = "files/images/tile_hidden.png";
        if (!coverTexture.loadFromFile(coverFilename)) {
            std::cout << "Failed to load cover texture: " << coverFilename << std::endl;
        }
        textures["tile_hidden.png"] = coverTexture;

        // Load base texture
        sf::Texture baseTexture;
        std::string baseFilename = "files/images/tile_revealed.png";
        if (!baseTexture.loadFromFile(baseFilename)) {
            std::cout << "Failed to load cover texture: " << baseFilename << std::endl;
        }
        textures["tile_revealed.png"] = baseTexture;

        // Load mine texture
        sf::Texture mineTexture;
        std::string mineFilename = "files/images/mine.png";
        if (!mineTexture.loadFromFile(mineFilename)) {
            std::cout << "Failed to load cover texture: " << mineFilename << std::endl;
        }
        textures["mine.png"] = mineTexture;

        // Load reset happy face texture
        sf::Texture happyTexture;
        std::string happyFilename = "files/images/face_happy.png";
        if (!happyTexture.loadFromFile(happyFilename)) {
            std::cout << "Failed to load cover texture: " << happyFilename << std::endl;
        }
        textures["face_happy.png"] = happyTexture;

        // Load win face texture
        sf::Texture winTexture;
        std::string winFilename = "files/images/face_win.png";
        if (!winTexture.loadFromFile(winFilename)) {
            std::cout << "Failed to load cover texture: " << winFilename << std::endl;
        }
        textures["face_win.png"] = winTexture;

        // Load lose face texture
        sf::Texture lossTexture;
        std::string lossFilename = "files/images/face_lose.png";
        if (!lossTexture.loadFromFile(lossFilename)) {
            std::cout << "Failed to load cover texture: " << lossFilename << std::endl;
        }
        textures["face_lose.png"] = lossTexture;

        // Load debug texture
        sf::Texture debugTexture;
        std::string debugFilename = "files/images/debug.png";
        if (!debugTexture.loadFromFile(debugFilename)) {
            std::cout << "Failed to load cover texture: " << debugFilename << std::endl;
        }
        textures["debug.png"] = debugTexture;

        //load pause texture
        sf::Texture pauseTexture;
        std::string pauseFilename = "files/images/pause.png";
        if (!pauseTexture.loadFromFile(pauseFilename)) {
            std::cout << "Failed to load cover texture: " << pauseFilename << std::endl;
        }
        textures["pause.png"] = pauseTexture;

        //load play texture
        sf::Texture playTexture;
        std::string playFilename = "files/images/play.png";
        if (!playTexture.loadFromFile(playFilename)) {
            std::cout << "Failed to load cover texture: " << playFilename << std::endl;
        }
        textures["play.png"] = playTexture;

        //Leader board texture
        sf::Texture leaderboardTexture;
        std::string leaderboardFilename = "files/images/leaderboard.png";
        if (!leaderboardTexture.loadFromFile(leaderboardFilename)) {
            std::cout << "Failed to load cover texture: " << leaderboardFilename << std::endl;
        }
        textures["leaderboard.png"] = leaderboardTexture;

        //Timer and Mine count digits
        sf::Texture digitsTexture;
        std::string digitsFilename = "files/images/digits.png";
        if (!digitsTexture.loadFromFile(digitsFilename)) {
            std::cout << "Failed to load cover texture: " << digitsFilename << std::endl;
        }
        textures["digits.png"] = digitsTexture;

        //Flag
        sf::Texture FlagTexture;
        std::string FlagFilename = "files/images/flag.png";
        if (!FlagTexture.loadFromFile(FlagFilename)) {
            std::cout << "Failed to load cover texture: " << FlagFilename << std::endl;
        }
        textures["flag.png"] = FlagTexture;







}




    // Method to get a texture by key
    sf::Texture& getTexture(const std::string& key) {
        return textures[key];
    }

    // Method to add a texture
    void addTexture(const std::string& key, const sf::Texture& texture) {
        textures[key] = texture;
    }
};



#endif //MINESWEEPER1_TEXTURE_MANAGER_H
