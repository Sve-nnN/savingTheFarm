#pragma once
#include <iostream>

using namespace System::Drawing;

class Enemy
{
private:
	int x, y;
	int dx, dy;
	int indexX, indexY;
	int width, height;
	bool visibility;
	int direction;
public:
	Enemy(int width, int height, int direction);
	Enemy();
	Enemy(int width, int height);

	~Enemy();

	void setVisibility(bool visiblity);
	bool getVisibility();

	void draw(Graphics^ panel, Bitmap^ image);
	void move(Graphics^ panel);
	Rectangle getRectangle();
	
};