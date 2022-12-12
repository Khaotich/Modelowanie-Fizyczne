#include "particle.h"

glm::vec3 Particle::getPosition() 
{
	return m_position;
}

glm::vec3 Particle::getDirection() 
{
	return m_direction;
}

glm::vec3 Particle::getVelocity() 
{
	return m_velocity;
}

float Particle::getRadius() 
{
	return radius;
}

glm::vec4 Particle::getColor()
{
	return m_color;
}

glm::vec4 Particle::getStartColor() 
{
	return m_startColor;
}

glm::vec4 Particle::getMidColor()
{
	return m_midColor;
}

glm::vec4 Particle::getEndColor()
{
	return m_endColor;
}