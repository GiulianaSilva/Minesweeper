//
// Created by Giuliana Silva on 4/15/24.
//

#ifndef MINESWEEPER1_LEADER_BOARD_H
#define MINESWEEPER1_LEADER_BOARD_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Game Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

struct Player {
    int minutes;
    int seconds;
    string name;
};

void setTextCentered(sf::Text& text, sf::RenderWindow& window, float x, float y) {
    sf::Vector2u windowSize = window.getSize();
    sf::FloatRect textBounds = text.getLocalBounds();
    float windowCenterX = windowSize.x / 2.0f;
    float windowCenterY = windowSize.y / 2.0f;
    float textPositionX = windowCenterX - (textBounds.width / 2.0f) + x;
    float textPositionY = windowCenterY - (textBounds.height / 2.0f) + y;
    text.setPosition(abs(textPositionX), abs(textPositionY));
}

void readLeaderboard(const string& filename, vector<Player>& leaderboard) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening the file." << endl;
        return;
    }

    leaderboard.clear();
    string line;
    while (getline(file, line)) {
        // Remove commas from the line
        line.erase(remove(line.begin(), line.end(), ','), line.end());


        Player player;
        char colon;
        stringstream ss(line);
        ss >> player.minutes >> colon >> player.seconds >> player.name;

        leaderboard.push_back(player);
    }

    file.close();
}

void writeLeaderboard(const string& filename, const vector<Player>& leaderboard) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening the leaderboard file for writing." << endl;
        return;
    }

    // Write each player's information to the file
    for (const Player& player : leaderboard) {

        string formattedMinutes = (player.minutes < 10 ? "0" : "") + to_string(player.minutes);
        string formattedSeconds = (player.seconds < 10 ? "0" : "") + to_string(player.seconds);
        string formattedTime = formattedMinutes + ":" + formattedSeconds;
        // Write player's name and formatted time to the file
        file << formattedTime << "," << player.name  << endl;
    }

    file.close();
}

void updateLeaderboard(vector<Player>& leaderboard, int newMinutes, int newSeconds, const string& newName, const string& leaderboardFile) {
    // Remove "*" from all entries of the same user
    for (auto& player : leaderboard) {
        if (player.name == newName + "*") {
            player.name = newName;
            break;
        }
    }
    Player newPlayer {newMinutes, newSeconds, newName + "*"};
    // Find the position to insert the new player
    auto it = find_if(leaderboard.begin(), leaderboard.end(), [&](const Player& p) {
        return (p.minutes > newMinutes) || (p.minutes == newMinutes && p.seconds > newSeconds);
    });
    if (it != leaderboard.end()) {
        leaderboard.insert(it, newPlayer);
        if (leaderboard.size() > 5) {
            leaderboard.pop_back();
        }
    }
    writeLeaderboard(leaderboardFile, leaderboard);
}


void leaderBoardWindow(int columns, int rows, string username, int time) {
    sf::RenderWindow LeaderBoardWindow(sf::VideoMode((columns * 16), (rows * 16) + 50), "Minesweeper");
    sf::Font LeaderFont;
    if (!LeaderFont.loadFromFile("files/font.ttf")) {
        cout << "error: unable to read file containing font." << endl;
        return;
    }

    sf::Text titleText;
    titleText.setFont(LeaderFont);
    titleText.setCharacterSize(20);
    titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("LEADERBOARD");

    float TrackX = (columns / 2) - 10;
    float TrackY = (rows / 2) - 120;
    setTextCentered(titleText, LeaderBoardWindow, TrackX, TrackY);

    // Read leaderboard from file
    string leaderboardFile = "files/leaderboard.txt";
    vector<Player> leaderboard;
    readLeaderboard(leaderboardFile, leaderboard);

    // Update leaderboard
    int minutes = time / 60;
    int seconds = time % 60;
    updateLeaderboard(leaderboard, minutes, seconds, username, leaderboardFile);

    // Create leaderboard string
    string leaderboardString;
    for (size_t i = 0; i < leaderboard.size() && i < 5; ++i) {

        string formattedMinutes = (leaderboard[i].minutes < 10 ? "0" : "") + to_string(leaderboard[i].minutes);
        string formattedSeconds = (leaderboard[i].seconds < 10 ? "0" : "") + to_string(leaderboard[i].seconds);

        leaderboardString +=
                to_string(i + 1) + "\t" + formattedMinutes + ":" + formattedSeconds + "\t" + leaderboard[i].name +
                "\n\n";

    }


    // Create a sf::Text instance
    sf::Text leaderboardText;
    leaderboardText.setFont(LeaderFont);
    leaderboardText.setCharacterSize(18);
    leaderboardText.setStyle(sf::Text::Bold);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setString(leaderboardString);
    float OutX = (columns / 2) + 5;
    float OutY = (rows / 2) + 20;
    setTextCentered(leaderboardText, LeaderBoardWindow, OutX, OutY);

    while (LeaderBoardWindow.isOpen()) {
        sf::Event event;
        while (LeaderBoardWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    LeaderBoardWindow.close();
                    break;
            }
        }

        LeaderBoardWindow.clear(sf::Color::Blue);
        LeaderBoardWindow.draw(titleText);
        LeaderBoardWindow.draw(leaderboardText);
        LeaderBoardWindow.display();
    }
}










#endif //MINESWEEPER1_LEADER_BOARD_H
