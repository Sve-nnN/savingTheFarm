#pragma once
#include "Enemy.h" 
class Pez : public Enemy
{
private:

public:

	Pez(int x, int y);
	Pez();
	~Pez();

	int getx();
	int gety();
	void setx();
	void sety();
};

