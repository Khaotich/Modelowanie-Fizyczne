#pragma once
#include "ofMain.h"

class Point;

class Link
{
public:
	Point* p1;
	Point* p2;
	float k;
};

class Point
{
public:

	Point();
	void setup(ofColor color, float radius, float mass, 
			   glm::vec2 positionAtStart, bool isLocked);
	void draw();
	void SpringForce(int& lineSegmentLength, int& k);
	void Verlet(bool& isLocked, float& deltaTime);

	bool isLocked;
	float radius;
	float mass;
	float displacement;

	glm::vec2 grid;
	glm::vec2 position;
	glm::vec2 positionOld;
	glm::vec2 force;
	glm::vec2 velocity;

	ofColor color;
	std::vector<Link> links;
};