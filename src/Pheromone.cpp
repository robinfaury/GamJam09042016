#include "Pheromone.h"

Pheromone::Pheromone() : active(false), foodLvl(0.0f), dangerLvl(0.0f), colonyLvl(0.0f)
{
}

void Pheromone::decay()
{
	if (!active)
		return;
	//TODO : pheromone decay formula
}

void Pheromone::raiseFood(float foodLvl)
{
	this->foodLvl += foodLvl;
	active = true;
}
