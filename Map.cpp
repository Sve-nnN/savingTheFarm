#include "pch.h"
#include "Map.h"

Map::Map(int width, int height, Player player) {
	this->width = width;
	this->height = height;
	playerX = player.getX();
	playerY = player.getY();
	dx = 0;
	dy = 0;
	indexX = 0;
	indexY = 0;
	visibility = true;
}

Map::~Map() {
}

void Map::draw(Graphics^ panel, Bitmap^ image, Player player) {
	//Code to draw the map
	//Cortado a cierta parte del mapa
	//Rectangle sectionShow = Rectangle(indexX * width, indexY * height, width, height);
	Rectangle sectionShow = Rectangle(playerX-20, playerY - 40, width, height);

	Rectangle zoom = Rectangle(0,0, image->Width, image->Height);
	panel->DrawImage(image, zoom, sectionShow, GraphicsUnit::Pixel);

}

void Map::move(Graphics^ panel, Player player) {
	// Code to move the map based on player's movement
	dx = player.getX() - playerX;
	dy = player.getY() - playerY;
	indexX += dx;
	indexY += dy;
	playerX = player.getX();
	playerY = player.getY();
}

Rectangle Map::getRectangle() {
	// Code to get the rectangle of the map
	return Rectangle(0, 0, width, height);
}