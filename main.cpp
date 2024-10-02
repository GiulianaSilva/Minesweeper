#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Game Board.h"
using namespace std;

//Function used to center text based off a given position.
void setText(sf::Text &text, sf::RenderWindow &window, float x, float y) {
    sf::Vector2u windowSize = window.getSize();
    sf::FloatRect textBounds = text.getLocalBounds();

    float windowCenterX = windowSize.x / 2.0f;
    float windowCenterY = windowSize.y / 2.0f;

    float textPositionX =  windowCenterX - (textBounds.width / 2.0f) + x;
    float textPositionY = windowCenterY -  (textBounds.height / 2.0f) + y;

    text.setPosition(abs(textPositionX), abs(textPositionY));
}


int main() {

//Getting values for columns, rows, and mines stored in the config.cfg file.
    string strColumns;
    string strRows;
    string strMines;

    ifstream file("files/config.cfg");
    if(!file.is_open()){
        cout<<"error: file not opened."<<endl;
        return 1;
    }

    if (!(file >> strColumns >> strRows >> strMines)) {
        cout << "error: unable to read file." << endl;
        return 1;
    }


    file.close();
    int columns = stoi(strColumns);
    int rows = stoi(strRows);
    int mines = stoi(strMines);

//declaring a font for welcome message.
    sf::Font welcomeFont;
    if (!welcomeFont.loadFromFile("files/font.ttf")){
        cout << "error: unable to read file containing font." << endl;
        return 1;
    }

//Sets up specifics for welcome message.
    sf::Text welcomeText;
    welcomeText.setFont(welcomeFont);
    welcomeText.setCharacterSize(24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setString("WELCOME TO MINESWEEPER !");

    float WelcX = columns/2;
    float WelcY = (rows/2) - 150;

//Sets up specifics for enter name message.
    sf::Text nameText;
    nameText.setFont(welcomeFont);
    nameText.setCharacterSize(20);
    nameText.setStyle(sf::Text::Bold);
    nameText.setFillColor(sf::Color::White);
    nameText.setString("Enter your name :");

    float NameX = columns/2;
    float NameY = (rows/2) - 75;

//Sets up specifications for curser tracker.
    sf::Text curserText;
    curserText.setFont(welcomeFont);
    curserText.setCharacterSize(18);
    curserText.setStyle(sf::Text::Bold);
    curserText.setFillColor(sf::Color::Yellow);
    curserText.setString("|");

    float TrackX = columns/2;
    float TrackY = (rows/2) - 45;

//Sets up specifications for Username.
    sf::Text userText;
    userText.setFont(welcomeFont);
    userText.setCharacterSize(18);
    userText.setStyle(sf::Text::Bold);
    userText.setFillColor(sf::Color::Yellow);
    string username= "";
    userText.setString(username);

//opening the welcome window
    sf::RenderWindow welcomeWindow(sf::VideoMode((columns*32), (rows * 32)+100 ), "Minesweeper");

 //set center initial positioning of all text
    setText(welcomeText, welcomeWindow,  WelcX, WelcY);
    setText(nameText, welcomeWindow,  NameX, NameY);
    setText(curserText, welcomeWindow,  TrackX, TrackY);
    setText(userText, welcomeWindow,  TrackX , TrackY);

    while (welcomeWindow.isOpen()) {
        sf::Event event;
        while (welcomeWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    welcomeWindow.close();
                    break;


                case sf::Event::TextEntered:
                    //Specifies that only letters will be taken in as valid inputs.
                    if (event.text.unicode >= 97 && event.text.unicode <= 122 && event.text.unicode != '\b' ) {

                        //Capitalizes first letter imputed by the user
                        if (username.size() == 0 ) {
                            setText(curserText, welcomeWindow,  TrackX, TrackY);
                            event.text.unicode -= 32; // Convert lowercase to uppercase
                            username += static_cast<char>(event.text.unicode);

                            userText.setString(username + "|");
                            setText(curserText, welcomeWindow,  TrackX, TrackY);
                            curserText.setString("");
                            setText(userText, welcomeWindow,  TrackX , TrackY);
                        }

                        else if( username.size() < 10) {
                            username += static_cast<char>(event.text.unicode);
                            userText.setString(username + "|");
                            setText(userText, welcomeWindow,  TrackX , TrackY);
                            curserText.setString("");
                        }
                    }
                    //Backspace
                     else if (event.text.unicode == '\b') {
                        if (!username.empty()) {
                            username.pop_back();
                            setText(userText, welcomeWindow,  TrackX , TrackY);
                            userText.setString(username + "|");
                        }
                    }
                    break;
                 //Closes the welcome window when the return button is clicked only if the user has imputed a username.
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Return){
                        if(!username.empty()) {
                            welcomeWindow.close();
                            GameWindow(columns, rows, mines, username);
                        }
                    }
                    break;
            }
        }
//Displays welcome window
        welcomeWindow.clear(sf::Color::Blue);
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(nameText);
        welcomeWindow.draw(curserText);
        welcomeWindow.draw(userText);
        welcomeWindow.display();
    }
    return 0;
}

