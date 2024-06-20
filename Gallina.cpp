#include "pch.h"
#include "Gallina.h"

Gallina::Gallina(int x, int y) {

}
Gallina::Gallina() : Enemy(x, y) {
	this->dx = 3;
	this->dy = 1;

	this->x = 10;
	this->y = 0;
	this->width = 7;
	this->height = 4;
}
Gallina::~Gallina() {

}

int Gallina::getx() {
	return x;
}
int Gallina::gety() {
	return y;
}
void Gallina::setx() {

}
void Gallina::sety() {

}

