#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <map>
#include "random.h"
#include "TextureManager.h"
using std::cout;
using std::endl;

void AssignNeighbors(int c, int r, std::vector<std::vector<Tile*>>& t);
void randomboard(int row, int col, int mines, std::vector<std::vector<Tile*>>& tiles, int& revealedcount);
void loadboard(std::string s, std::vector<std::vector<Tile*>>& tiles, int& revealedcount, int& mines, int& flagcount);
void LOSETHEGAME(sf::Window& window, Tile* happyface);
void SetCounter(int flagcounter, Tile* one, Tile* two, Tile* three);
void WINTHEGAME(sf::Window& window, Tile* happyface);

int main()
{

    //Load config file here:
    std::ifstream config("boards/config.cfg");
    std::string c, r, m;
    getline(config, c);
    int col = stoi(c);
    getline(config, r);
    int row = stoi(r);
    getline(config, m);
    int mines = stoi(m);
    int flagcounter = mines;
    int tilecount = row * col;
    int revealedcount = 0;

    //Create window based on config file variables:
    sf::RenderWindow window(sf::VideoMode(col * 32, row * 32 + 100), "Minesweeper");

    // Generate random board
    std::vector<std::vector<Tile*>> tiles;
    randomboard(row, col, mines, tiles, revealedcount);

    Tile* flags_1 = new Tile();
    Tile* flags_2 = new Tile();
    Tile* flags_3 = new Tile();
    Tile* happyface = new Tile("face_happy",1);
    Tile* Test1 = new Tile("test_1",1);
    Tile* Test2 = new Tile("test_2",1);
    Tile* Test3 = new Tile("test_3",1);
    Tile* debug_button = new Tile("debug",1);
    SetCounter(flagcounter, flags_1, flags_2, flags_3);
    flags_1->setSpritePosition(21, row*32);
    flags_2->setSpritePosition(42, row*32);
    flags_3->setSpritePosition(63, row*32);
    happyface->setSpritePosition(col * 16 - 32, row * 32);
    debug_button->setSpritePosition(col * 16 + (3 * 32), row * 32);
    Test1->setSpritePosition(col * 16 + (5 * 32), row * 32);
    Test2->setSpritePosition(col * 16 + (7 * 32), row * 32);
    Test3->setSpritePosition(col * 16 + (9 * 32), row * 32);


    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        
            if (event.type == sf::Event::MouseButtonPressed) {
                
                //Get the coordinates of the click:
                sf::Vector2i coordinates = sf::Mouse::getPosition(window);
                
                //Check if mouse button was left or right
                if (event.key.code == sf::Mouse::Left)
                {
                    //If left check which tile was clicked:
                    if (debug_button->getBounds().contains(coordinates.x, coordinates.y)) {
                        debug_button->Debug(tiles);
                    }

                    else if (happyface->getBounds().contains(coordinates.x, coordinates.y)) {
                        randomboard(row, col, mines, tiles, revealedcount);
                        flagcounter = mines;
                        SetCounter(flagcounter, flags_1, flags_2, flags_3);
                        happyface->newgame();

                    }
                    else if (Test1->getBounds().contains(coordinates.x, coordinates.y)) {
                        loadboard("boards/testboard1.brd", tiles, revealedcount, mines, flagcounter);
                        flagcounter = 0; 
                        SetCounter(flagcounter, flags_1, flags_2, flags_3);
                        happyface->newgame();
                    }
                    else if (Test2->getBounds().contains(coordinates.x, coordinates.y)) {
                        loadboard("boards/testboard2.brd", tiles, revealedcount, mines, flagcounter);
                        flagcounter = 0; 
                        SetCounter(flagcounter, flags_1, flags_2, flags_3);
                        happyface->newgame();
                    }
                    else if (Test3->getBounds().contains(coordinates.x, coordinates.y)) {
                        loadboard("boards/testboard3.brd", tiles, revealedcount, mines, flagcounter);
                        flagcounter = 0;
                        SetCounter(flagcounter, flags_1, flags_2, flags_3);
                        happyface->newgame();
                    }
                    else {
                        for (unsigned int i = 0; i < tiles.size(); i++)
                            for (unsigned int j = 0; j < tiles.at(i).size(); j++) {
                                if (tiles.at(i).at(j)->getBounds().contains(coordinates.x, coordinates.y)) {
                                    tiles[i][j]->ClickTile(revealedcount);
                                    if (tiles[i][j]->getType() == true) {
                                        // LOSE THE GAME!
                                        happyface->Lose();
                                        happyface->Draw(window);
                                        tiles[i][j]->Draw(window);
                                        window.display();
                                        LOSETHEGAME(window, happyface);
                                        happyface->newgame();
                                        randomboard(row, col, mines, tiles, revealedcount);
                                        
                                    }
                                    else if (flagcounter == 0 && revealedcount == tilecount - mines) {
                                        happyface->win();
                                        happyface->Draw(window);
                                        tiles[i][j]->Draw(window);
                                        window.display();
                                        WINTHEGAME(window, happyface);
                                        happyface->newgame();
                                        randomboard(row, col, mines, tiles, revealedcount);
                                    }
                                }
                            }
                    }
                }
                //If right click:
                else {
                    //Place flag
                    for (unsigned int i = 0; i < tiles.size(); i++)
                        for (unsigned int j = 0; j < tiles.at(i).size(); j++) {
                            if (tiles.at(i).at(j)->getBounds().contains(coordinates.x, coordinates.y)) {
                                if (tiles.at(i).at(j)->isClicked() == false) {
                                    tiles.at(i).at(j)->PlaceFlag();
                                    //deduct from counter
                                    if (tiles.at(i).at(j)->getFlag() == true) {
                                        flagcounter--;
                                        SetCounter(flagcounter, flags_1, flags_2, flags_3);
                                    }
                                    else {
                                        flagcounter++;

                                        SetCounter(flagcounter, flags_1, flags_2, flags_3);
                                    }
                                }

                            }
                        }
                }               
            }
        }
       
 
        window.clear(sf::Color::White);
        

        // Draw  tiles:
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                tiles.at(i).at(j)->setSpritePosition(j * 32, i * 32);
                tiles.at(i).at(j)->Draw(window);

            }
        }

        //Draw control buttons:

        
        happyface->Draw(window);
        debug_button->Draw(window);
        flags_1->Draw(window);
        flags_2->Draw(window);
        flags_3->Draw(window);
        Test1->Draw(window);
        Test2->Draw(window);
        Test3->Draw(window);      
        window.display();
        
    
    }
    TextureManager::Clear();
    return 0;
}

void AssignNeighbors(int c, int r, std::vector<std::vector<Tile*>>& t) {
    //After building the initial board, assign neighbors
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            //If this specific tile is a mine, don't track neighboring mines:
            if (t.at(i).at(j)->getType()) continue;            
            
            // Check Top Row
            if (i == 0) {   
                //Top left Corner
                if (j == 0) {   
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t.at(i).at(j + 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j + 1));
                }
                //Top right corner
                else if (j == c - 1) {  
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j - 1));
                        t.at(i).at(j)->giveNeighbors(t[i].at(j - 1));
                }
                // Anywhere else in the top row
                else {      
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t.at(i).at(j + 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j + 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j - 1));
                        t.at(i).at(j)->giveNeighbors(t[i].at(j - 1));
                }
            }
           
            // Check Botton Row
            else if (i == r - 1) {  
                // Bottom left corner
                if (j == 0) {           
                        t.at(i).at(j)->giveNeighbors(t.at(i).at(j + 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j + 1));
                }
                // Bottom Right Corner
                else if (j == c - 1) { 
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t[i].at(j - 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j - 1));
                }
                // Anywhere else in the bottom row
                else {          
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t[i].at(j - 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j - 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j + 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i).at(j + 1));
                }
            }

            // Check Anywhere not on the top or bottom row
            else if (i < r-1) {      
                //Left edge
                if (j == 0) { 
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t.at(i).at(j + 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j + 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j + 1));
                }
                //right edge
                else if (j == c - 1) {  
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j - 1));
                        t.at(i).at(j)->giveNeighbors(t[i].at(j - 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j - 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j));
                }
                //Main body, no edge
                else {
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t.at(i).at(j + 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j + 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i + 1).at(j - 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j));
                        t.at(i).at(j)->giveNeighbors(t[i].at(j - 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j + 1));
                        t.at(i).at(j)->giveNeighbors(t.at(i - 1).at(j - 1));
                }
            }
        }
}

void randomboard(int row, int col, int mines, std::vector<std::vector<Tile*>>& tiles, int& revealedcount) {
    tiles.clear();
    for (int i = 0; i < row; i++) {
        std::vector<Tile*> t;
        for (int j = 0; j < col; j++) {
            Tile* n = new Tile();
            t.push_back(n);
        }
        tiles.push_back(t);
    }

    for (int i = 0; i < mines; i++) {
        int randomX = Random::Number(0, col-1);
        int randomY = Random::Number(0, row-1);
        //If the random location already has a mine, deduct from the counter so it generates another
        if (tiles.at(randomY).at(randomX)->getType()) 
            i--;
        //If there isnt a mine, set one
        else
            tiles.at(randomY).at(randomX)->setMine();
    }
    AssignNeighbors(col, row, tiles);
    revealedcount = 0;
}

void LOSETHEGAME(sf::Window& window, Tile* happyface) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed && happyface->getBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                return;
        }
    }
}

void WINTHEGAME(sf::Window& window, Tile* happyface) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed && happyface->getBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                return;
        }
    }
}

void SetCounter(int flagcounter, Tile* one, Tile* two, Tile* three) {
    std::string counter = std::to_string(flagcounter);
    if (flagcounter < 0) {
        one->SetTexture(-1);
        two->SetTexture(-flagcounter / 10 % 10);
        three->SetTexture(-(flagcounter % 10));
    }
    else {
        one->SetTexture(0);
        two->SetTexture(flagcounter/10%10);
        three->SetTexture(flagcounter %10);
    }
        

}

void loadboard(std::string s, std::vector<std::vector<Tile*>>& tiles, int& revealedcount, int& mines, int& flagcount) {
    char c;
    int i = tiles.at(0).size();
    int minecount = 0;
    tiles.clear();
    std::ifstream input(s);

 //   int j = tiles.size();
    std::vector<Tile*> line;
  //  for (int k = 0; k < j; k++) {
   //     tiles.at(k).clear();
   // }
    while (input >> c) {
        if (i > 1) {

            if (c == '1') {
                minecount++;
                Tile* t = new Tile();
                t->setMine();
                i--;
                line.push_back(t);
            }
            else if (c == '0') {
                Tile* t = new Tile();
                i--;
                line.push_back(t);
            }

        }
        else {
            tiles.push_back(line);
            line.clear();
            i = tiles.at(0).size();
        }
    }
    mines = minecount;
    flagcount = minecount;
    revealedcount = 0;
}