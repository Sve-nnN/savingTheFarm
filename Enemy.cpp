#include "pch.h"
#include "Enemy.h"


Enemy::Enemy(int width, int height, int direction) {
	this->width = width;
	this->height = height;
	this->direction = direction;
	this->dx = this->dy = 20;
	this->x = rand() % 900;
	this->y = rand() % 200;
	this->indexX = indexY = 0;
	this->visibility = true;
}
Enemy::Enemy() {}
Enemy::Enemy(int width, int height) {
	this->width = width;
	this->height = height;
	this->dx = this->dy = 20;
	this->x = 10;
	this->y = 0;
	this->indexX = this->indexY = 0;
	this->visibility = true;
}

void Enemy::move(Graphics^ panel) {
	if (direction == 1) {
		if (x + width * 1.0 > panel->VisibleClipBounds.Width || x < 0)
			dx *= -1;
		if (dx > 0) {
			indexY = 1;
		}
		else
			indexY = 3;
		x += dx;
	}
	else {
		if (y + height * 1.0 > panel->VisibleClipBounds.Height || y < 0) dy *= -1;

		if (dy > 0) {
			indexY = 0;
		}
		else
			indexY = 2;
		y += dy;

	}
	indexX++;
	if (indexX > 3)
		indexX = 0;
}
void Enemy::draw(Graphics^ panel, Bitmap^ image) {}
Rectangle Enemy::getRectangle() {
	return Rectangle(x, y, width * 1.0, height * 1.0);
}


Enemy::~Enemy() {}
