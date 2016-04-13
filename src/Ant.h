#pragma once

#define WARRIOR_SIZE 1.0f
#define WARRIOR_PERCEPTIONRADIUS 5.0f

#define DRONE_SIZE 1.0f
#define DRONE_PERCEPTIONRADIUS 5.0f

#define WORKER_SIZE 1.0f
#define WORKER_PERCEPTIONRADIUS 5.0f

#define QUEEN_SIZE 1.0f
#define QUEEN_PERCEPTIONRADIUS 1.0f

#include "glm\glm.hpp"
#include "Perception.h"

class Simulator;

enum AntTypes
{
	QUEEN = 0,
	DRONE,
	WARRIOR,
	WORKER,
	COUNT
};

static const glm::vec3& getColorAnt(AntTypes type) {
	static const glm::vec3 colors[COUNT]{
		glm::vec3(1.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0),
		glm::vec3(0.0, 0.0, 1.0),
		glm::vec3(1.0, 1.0, 0.0),
	};
	return colors[type];
}

class Ant
{
public:
	glm::vec2* pos;
	Simulator* simulator;
	unsigned int index;
	const float size;	// size for collision, in number of tiles
	const float perceptionRadius;
	Perception perceptions;

	virtual void live() = 0;
	virtual void setPerception();

	Ant(Simulator* sim, glm::vec2* p, unsigned int index, float size, float perceptionRadius);
};

class Queen : public Ant
{
public:
	Queen(Simulator* sim, glm::vec2* p, unsigned int index);

	virtual void live();
};

class Worker : public Ant
{
public:
	Worker(Simulator* sim, glm::vec2* p, unsigned int index);

	virtual void live();
};

class Drone : public Ant
{
public:
	Drone(Simulator* sim, glm::vec2* p, unsigned int index);
	virtual void live();
};

class Warrior : public Ant
{
public:
	Warrior(Simulator* sim, glm::vec2* p, unsigned int index);
	virtual void live();
};