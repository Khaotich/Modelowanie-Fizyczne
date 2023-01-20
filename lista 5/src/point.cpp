#include "point.h"

Point::Point() {}

void Point::setup(ofColor color, float radius, float mass, 
				  glm::vec2 positionAtStart, bool isLocked)
{
	this->color = color;
	this->radius = radius;
	this->mass = mass;
	this->position = positionAtStart;
	this->positionOld = positionAtStart;
	this->isLocked = isLocked;

	velocity = {0, 0};
	force = {0, 0};
	grid = {0, 0};
}

void Point::draw()
{
	ofSetColor(color);
	ofDrawCircle(position, radius);
}

void Point::SpringForce(int& lineSegmentLength, int& k)
{
	for(int i = 0; i < links.size(); i++)
	{
		glm::vec2 directionalVector = links[i].p1->position - links[i].p2->position;
		links[i].p1->displacement = glm::distance(links[i].p1->
			position, links[i].p2->position) - lineSegmentLength;
		directionalVector = glm::normalize(directionalVector);
		glm::vec2 springForce = k * links[i].p1->displacement * directionalVector;

		links[i].p1->force -= springForce;
		links[i].p2->force += springForce;
	}
}

void Point::Verlet(bool& isLocked, float& deltaTime) 
{
	if (!isLocked)
	{
		glm::vec2 tempPositionOld = position;
		position = position + (position - positionOld) + 
				   deltaTime * deltaTime * (force / mass);
		positionOld = tempPositionOld;
	}
}