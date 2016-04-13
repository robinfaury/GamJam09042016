#include "Ant.h"
#include "Simulator.h"

void Ant::setPerception()
{
}

Ant::Ant(Simulator* sim, glm::vec2* p, unsigned int index, float size, float perceptionRadius) : simulator(sim), index(index), pos(p), size(size), perceptionRadius(perceptionRadius)
{

}

Worker::Worker(Simulator* sim, glm::vec2* p, unsigned int index) : Ant(sim, p, index, WORKER_SIZE, WORKER_PERCEPTIONRADIUS)
{
}

void Worker::live()
{
	glm::vec2 r;
	r.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	*this->pos += (r*2.f - 1.f) / 300.f;

	this->simulator->dropFood(*pos, 1.0f);
}

Drone::Drone(Simulator* sim, glm::vec2* p, unsigned int index) : Ant(sim, p, index, DRONE_SIZE, DRONE_PERCEPTIONRADIUS)
{
	
}

void Drone::live()
{
	glm::vec2 r;
	r.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	*this->pos += (r*2.f - 1.f) / 300.f;

	this->simulator->dropColony(*pos, 1.0f);
}

Warrior::Warrior(Simulator* sim, glm::vec2* p, unsigned int index) : Ant(sim, p, index, WARRIOR_SIZE, WARRIOR_PERCEPTIONRADIUS)
{
	
}

void Warrior::live()
{
	glm::vec2 r;
	r.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	r.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	*this->pos += (r*2.f - 1.f) / 300.f;

	this->simulator->dropDanger(*pos, 1.0f);
}

Queen::Queen(Simulator* sim, glm::vec2* p, unsigned int index) : Ant(sim, p, index, QUEEN_SIZE, QUEEN_PERCEPTIONRADIUS)
{
}

void Queen::live()
{
	
}
