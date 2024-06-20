#pragma once
#include "Player.h"
#include <iostream>
//Mapa que sigue al jugador
class Map
{
private:
	int playerX, playerY; //Posicion del jugador
	int dx, dy; //Desplazamiento del jugador
	int indexX, indexY; //Indice del mapa
	int width, height ; //Dimensiones del mapa
	bool visibility; //Visibilidad del mapa
public:
	Map(int width, int height, Player player);
	~Map();

	void draw(Graphics^ panel, Bitmap^ image, Player player);
	void move(Graphics^ panel, Player player);
	Rectangle getRectangle();
};