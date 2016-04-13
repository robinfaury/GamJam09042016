#pragma once

#include <deque>
#include <vector>

#include "Ant.h"
#include "Pheromone.h"

#define MAX_ANT_NUMBER 100000

using std::vector;
using std::deque;

struct AntAttribute
{
	glm::vec2 pos;
	glm::vec3 id;
	float orientation;
};

class Simulator
{
public:
	Simulator(int mapSize, int collisionGridSize, int startingAnts);

	void init(int mapSize, int collisionGridSize, int startingAnts);
	void step();
	void clear();
	void solveCollisions();

	Pheromone& getPheromoneAt(int x, int y);

	vector<Ant*>& getAnts();
	unsigned int getNbAnts();
	vector<Pheromone>& getPheromones();
	vector<AntAttribute>& getAntAttributes();

	// Ant stuff
	void die(int index);
	void dropFood(glm::vec2& pos, float amount = 0.0f);
	void dropDanger(glm::vec2& pos, float amount = 0.0f);
	void dropColony(glm::vec2& pos, float amount = 0.0f);

private :
	deque<unsigned int> ants_freeIndices_;
	vector<Ant*> ants_;
	unsigned int nbAnts_;
	vector<AntAttribute> attributes_;

	int collisionGridSize_;
	int mapSize_;
	vector<Pheromone> pheromones_;
};