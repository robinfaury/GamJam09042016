#pragma once

class Pheromone
{
public :
	Pheromone();
	void decay();
	void raiseFood(float foodLvl);

private:
	float foodLvl;
	float dangerLvl;
	float colonyLvl;
	bool active;
};