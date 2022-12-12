#pragma once
#include "ofMain.h"

class Particle
{
public:
	Particle();
	~Particle();
	Particle(Particle& a_particle);
	Particle(glm::vec3 a_emitterPos, glm::vec3 a_direction,
		float a_velocity, float a_size, glm::vec4 a_startColor,
		glm::vec4 a_endColor, float a_lifeSpan);

	glm::vec3 getPosition();
	glm::vec3 getDirection();
	glm::vec3 getVelocity();
	glm::vec4 getColor();
	glm::vec4 getStartColor();
	glm::vec4 getMidColor();
	glm::vec4 getEndColor();
	float getRadius();

private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_velocity;
	glm::vec4 m_color;
	glm::vec4 m_startColor;
	glm::vec4 m_midColor;
	glm::vec4 m_endColor;
	float radius;
};