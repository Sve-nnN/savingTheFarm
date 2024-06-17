#pragma once

using namespace System::Drawing;

class Player
{
private:
	int x, y; // ubicacion
	int dx, dy; // movimiento
	int indexX, indexY; // index x e y
	int width, height;
	char direction;
public:
	Player(int width, int height);

public:
	char getDirection();
	int getX();
	int getY();

	void draw(Graphics^ panel, Bitmap^ image);
	void move(Graphics^ panel, char keyPressed);

};

