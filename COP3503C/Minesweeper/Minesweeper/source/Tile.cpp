#include "Tile.h"
#include "SFML/Graphics.hpp"
#include <string>
#include "TextureManager.h"

Tile::Tile()
{
	top_sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
	bottom_sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
}

Tile::Tile(std::string s) {
	top_sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
	bottom_sprite.setTexture(TextureManager::GetTexture("tile_revealed"));

}

Tile::Tile(std::string s, int a) {
	top_sprite.setTexture(TextureManager::GetTexture(s));
}

Tile::~Tile()
{
}

bool Tile::isClicked() {
	return clicked;
}

bool Tile::getType() {
	return mine;
}

void Tile::setSpritePosition(float x, float y) {
	top_sprite.setPosition(x, y);
	bottom_sprite.setPosition(x, y);
}

void Tile::Draw(sf::RenderWindow &window) {
	
		window.draw(bottom_sprite);
		window.draw(top_sprite);
	
}

void Tile::ClickTile(int& revealedcount) {
	//If there isnt a flag on the tile do this: 
	if (flagged == false && clicked == false) {
		clicked = true;
		revealedcount++;
		if (mine == true) {
			top_sprite.setTexture(TextureManager::GetTexture("mine"));
			bottom_sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
			// Game Loss conditions:

		}
		else if (neighboring_mines != 0 && mine == false) {
			top_sprite.setTexture(TextureManager::GetTexture("number_" + std::to_string(neighboring_mines)));
			bottom_sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
		}
		else if (mine == true) {
			top_sprite.setTexture(TextureManager::GetTexture("mine"));
			bottom_sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
			// Game Loss conditions:

		}
		else if (mine == false && neighboring_mines == 0){
			// if there are no neighboring mines, draw a blank tile
			top_sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
			//Do recursion if neighbors are zero and its not a mine
			for (unsigned int i = 0; i < neighbors.size(); i++)
				neighbors.at(i)->ClickTile(revealedcount);
		}
	}
}
void Tile::Lose() {
	top_sprite.setTexture(TextureManager::GetTexture("face_lose"));
}

void Tile::newgame() {
	top_sprite.setTexture(TextureManager::GetTexture("face_happy"));
}

void Tile::win() {
	top_sprite.setTexture(TextureManager::GetTexture("face_win"));
}

sf::FloatRect Tile::getBounds() {
	return top_sprite.getGlobalBounds();
}

void Tile::giveNeighbors(Tile* t) {
	neighbors.push_back(t);	
	if(t->getType() == true) neighboring_mines += 1;	
}


void Tile::setMine() {
	mine = true;
	bottom_sprite.setTexture(TextureManager::GetTexture("mine"));
}

void Tile::PlaceFlag() {
	if (flagged == false) {
		top_sprite.setTexture(TextureManager::GetTexture("flag"));
		bottom_sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
		flagged = true;
	}
	else {
		top_sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
		flagged = false;
	}


}

void Tile::Debug(std::vector<std::vector<Tile*>>& tiles) {
	if (debugmode == false) {
		for (unsigned int i = 0; i < tiles.size(); i++)
			for (unsigned int j = 0; j < tiles.at(i).size(); j++) {
				if (tiles.at(i).at(j)->mine == true) {
					tiles.at(i).at(j)->bottom_sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
					tiles.at(i).at(j)->top_sprite.setTexture(TextureManager::GetTexture("mine"));
				}
	
			}
		debugmode = true;
	}

	else {
		for (unsigned int i = 0; i < tiles.size(); i++)
			for (unsigned int j = 0; j < tiles.at(i).size(); j++) {
				if (tiles.at(i).at(j)->flagged == true)
				{
					tiles.at(i).at(j)->bottom_sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
					tiles.at(i).at(j)->top_sprite.setTexture(TextureManager::GetTexture("flag"));
				}
				else if (tiles.at(i).at(j)->clicked == true) {
					tiles.at(i).at(j)->bottom_sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
				}
				else 
					tiles.at(i).at(j)->top_sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
				}
		debugmode = false;
	}
}

void Tile::SetTexture(int flagcounter) {
	top_sprite.setTexture(TextureManager::GetTexture(flagcounter));
}


bool Tile::getFlag() {
	return flagged;
}