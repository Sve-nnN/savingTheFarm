#include "pch.h"
#include "Player.h"


Player::Player(int width, int height) {
	this->width = width;
	this->height = height;
	this->dx = this->dy = 15;
	this->x = 500;
	this->y = 85;
	this->indexX = this->indexY = 0;
}

void Player::draw(Graphics^ panel, Bitmap^ image) {
	Rectangle sectionShow = Rectangle(indexX * width, indexY * height, width, height);
	Rectangle zoom = Rectangle(x, y, width, height);
	panel->DrawImage(image, zoom, sectionShow, GraphicsUnit::Pixel);

}
void Player::move(Graphics^ panel, char keyPressed) {
	switch (keyPressed) {
	case 'A':
		if (x > 0) {
			indexY = 3;
			x -= dx;
			direction = 'A';
		}
		break;
	case 'D':
		if (x + width * 1.0 < panel->VisibleClipBounds.Width) {
			indexY = 1;
			x += dx;
			direction = 'D';
		}
		break;
	case 'W':
		if (y > 0) {
			indexY = 2;
			y -= dy;
			direction = 'W';
		}
		break;
	case 'S':
		if (y + height * 1.0 < panel->VisibleClipBounds.Height) {
			indexY = 0;
			y += dy;
			direction = 'S';
		}
		break;
	}
	indexX++;
	if (indexX >= 4) indexX = 0;
}
char Player::getDirection() {
	return this->direction;
}

int Player::getX() {
	return this->x;
}

int Player::getY() {
	return this->y;
}