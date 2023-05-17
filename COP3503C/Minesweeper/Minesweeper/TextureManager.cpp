#include "TextureManager.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
using std::string;
using std::unordered_map;

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string textureName) {	
	string path = "images/" + textureName + ".png";
	textures[textureName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
	if (textures.find(textureName) == textures.end()) {
		LoadTexture(textureName);
	}

	return textures[textureName];
}

void TextureManager::Clear() {
	textures.clear();
}

sf::Texture& TextureManager::GetTexture(int number) {
	int n = number * 21;
	if (number == -1) {
		n = 10 * 21;
	}
	if (textures.find(std::to_string(number)) == textures.end()) {
		textures[std::to_string(number)].loadFromFile("images/digits.png", sf::IntRect(n, 0, 21, 32));
	}

	return textures[std::to_string(number)];
}
