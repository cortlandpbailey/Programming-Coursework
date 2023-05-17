#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include <string>
#include "TextureManager.h"
class Tile
{
public:
	Tile();
	~Tile();
	Tile(std::string s);
	Tile(std::string s, int a);
	void Draw(sf::RenderWindow& window);
	void setSpritePosition(float x, float y);
	void ClickTile(int& revealedcount);
	sf::FloatRect getBounds();
	bool getType();
	void giveNeighbors(Tile* t);
	void setMine();
	void PlaceFlag();
	bool isClicked();
	void Debug(std::vector<std::vector<Tile*>>& tiles);
	void Lose();
	void newgame();
	void win();
	void SetTexture(int flagcounter);
	bool getFlag();

private:
	int neighboring_mines = 0;
	std::vector<Tile*> neighbors;
	sf::Sprite bottom_sprite;
	sf::Sprite top_sprite;
	bool flagged = false;
	bool clicked = false;
	bool debugmode = false;
	bool mine = false;
};

