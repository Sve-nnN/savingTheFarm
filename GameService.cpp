#include "pch.h"
#include "GameService.h"

GameService::GameService() {
	numberOfEnemies = rand() % 8 + 2;
	isFinish = false;
}

GameService::~GameService() {

}


int  GameService::getCountEnemiesDelete() {
	return this->countEnemiesDelete;
}

bool GameService::getIsFinish() {
	return this->isFinish;
}

void  GameService::setIsFinish(bool isFinish) {
	this->isFinish = isFinish;
}



void GameService::createEnemies(int width, int height) {

	for (int i = 0; i < numberOfEnemies; i++)
	{
		Enemy* e = new Enemy(width, height, rand() % 2);
		enemies.push_back(e);
	}
}

void GameService::drawEveryThing(Graphics^ panel, Bitmap^ imagenEnemy) {
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw(panel, imagenEnemy);
	}
}

void GameService::moveEveryThing(Graphics^ panel) {
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->move(panel);
	}
}
/*void GameService::collision(Graphics^ panel) {
//TODO

}*/

