#include "Simulator.h"
#include "Ant.h"

Simulator::Simulator(int mapSize, int collisionGridSize, int startingAnts)
{
	init(mapSize, collisionGridSize, startingAnts);
}

void Simulator::init(int mapSize, int collisionGridSize, int startingAnts)
{
	// Creating positions
	attributes_.resize(MAX_ANT_NUMBER);

	// Creating ants
	ants_.reserve(startingAnts * 100);
	ants_.push_back(new Queen(this, &attributes_[0].pos, 0));
	attributes_[0].id = getColorAnt(QUEEN);
	for (int i = 1; i < startingAnts;)
	{
		ants_.push_back(new Drone(this, &attributes_[i].pos, i));
		attributes_[i++].id = getColorAnt(DRONE);
		ants_.push_back(new Warrior(this, &attributes_[i].pos, i));
		attributes_[i++].id = getColorAnt(WARRIOR);
		ants_.push_back(new Worker(this, &attributes_[i].pos, i));
		attributes_[i++].id = getColorAnt(WORKER);
	}

	nbAnts_ = startingAnts;

	// Creating pheromones
	mapSize_ = mapSize;
	pheromones_.resize(mapSize_ * mapSize_);
}

void Simulator::step()
{
	// decaying pheromones
	for (Pheromone p : pheromones_)
		p.decay();

	// Setting ant perceptions
	//TODO: do that

	// Ant actions
	for (int i = 0; i < nbAnts_; ++i)
		ants_[i]->live();

	// Solving ant collisions
}

void Simulator::clear()
{
	for (Ant* a : ants_)
		delete(a);
	ants_.clear();

	pheromones_.clear();
	attributes_.clear();
}

void Simulator::solveCollisions()
{
	// TODO : solve collisions
}

Pheromone& Simulator::getPheromoneAt(int x, int y)
{
	if (x >= 0 && y >= 0 && x < mapSize_ && y < mapSize_)
		return pheromones_[y * mapSize_ + x];
	else
		abort();
}

vector<Ant*>& Simulator::getAnts()
{
	return ants_;
}

unsigned int Simulator::getNbAnts() {
	return nbAnts_;
}

vector<Pheromone>& Simulator::getPheromones()
{
	return pheromones_;
}

vector<AntAttribute>& Simulator::getAntAttributes()
{
	return attributes_;
}

void Simulator::die(int index)
{
}

void Simulator::dropFood(glm::vec2 & pos, float amount)
{
}

void Simulator::dropDanger(glm::vec2 & pos, float amount)
{
}

void Simulator::dropColony(glm::vec2 & pos, float amount)
{
}