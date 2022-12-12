#include "particleEffect.h"

void ParticleEffect::setup(ofParameter<int>& numOfParticles, Emitter& emitter)
{
	for(unsigned int i = 0; i < numOfParticles; i++)
	{
		Particle newParticle;
		newParticle.position = glm::vec3((int)ofRandom(-emitter.box.getSize().x /
			2, emitter.box.getSize().x / 2),
			emitter.box.getSize().y / 2, (int)ofRandom(-emitter.box.getSize().x /
				2, emitter.box.getSize().x / 2));;

		newParticle.velocity = glm::vec3(0, ofRandom(0, 1), 0);
		newParticle.friction = glm::vec3(0, 0, 0);
		newParticle.color = ofColor::white;
		newParticle.drag = ofRandom(0.97, 0.99);
		newParticle.uniqueVal = ofRandom(-10000, 10000);
		newParticle.age = 0;
		newParticle.lifetime = ofRandom(5, 10);
		particles.push_back(newParticle);
	}
}

void Snow::draw(std::vector<Particle>& particles, bool& ifBox)
{
	for(unsigned int i = 0; i < particles.size(); i++)
	{
		if(ifBox)
			ofDrawBox(particles[i].position, ofRandom(0.3, 0.5));
		else
			ofDrawSphere(particles[i].position, ofRandom(0.3, 0.5));
	}
}

void Snow::update(std::vector<Particle>& particles, Emitter& emitter, float& dt)
{
	for(unsigned int i = 0; i < particles.size(); i++)
	{

		// ------- SNOW -------
		float fakeWindX = ofSignedNoise(particles[i].position.x * 0.003, particles[i].position.y * 0.006, ofGetElapsedTimef() * 0.6);
		particles[i].friction.x = fakeWindX * 0.25 + ofSignedNoise(particles[i].uniqueVal, particles[i].position.y * 0.04) * 0.6;
		particles[i].friction.y = ofSignedNoise(particles[i].uniqueVal, particles[i].position.x * 0.006, ofGetElapsedTimef() * 0.2) * 0.09 + 0.18;

		particles[i].velocity *= particles[i].drag;
		particles[i].velocity += particles[i].friction * 0.04;


		//we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
		if(particles[i].position.y + particles[i].velocity.y < -emitter.box.getSize().y / 2)
			particles[i].position.y += emitter.box.getSize().y;

		// particle physics
		particles[i].position -= particles[i].velocity;
		particles[i].velocity += -0.1f * particles[i].position * dt;

		if(particles[i].position.x > (emitter.box.getSize().x / 2))
		{
			particles[i].position.x = (emitter.box.getSize().x / 2);
			particles[i].velocity.x *= -1.0;
		}
		else if(particles[i].position.x < -(emitter.box.getSize().x / 2))
		{
			particles[i].position.x = -(emitter.box.getSize().x / 2);
			particles[i].velocity.x *= -1.0;
		}

		if(particles[i].position.z > (emitter.box.getSize().z / 2))
		{
			particles[i].position.z = (emitter.box.getSize().z / 2);
			particles[i].velocity.z *= -1.0;
		}
		else if(particles[i].position.z < -(emitter.box.getSize().z / 2))
		{
			particles[i].position.z = -(emitter.box.getSize().z / 2);
			particles[i].velocity.z *= -1.0;
		}
	}
}

void Matrix::draw(std::vector<Particle>& particles)
{
	for(unsigned int i = 0; i < particles.size(); i++)
	{
		ofSetColor(0, 255, 0);
		if (i % 2 == 0)
			ofDrawBitmapString("1", particles[i].position);
		else
			ofDrawBitmapString("0", particles[i].position);
	}
}

void Matrix::update(std::vector<Particle>& particles, Emitter& emitter, float& dt)
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		if(particles[i].position.y + particles[i].velocity.y < -emitter.box.getSize().y / 2)
			particles[i].position.y += emitter.box.getSize().y;

		particles[i].position -= particles[i].velocity;

		if(particles[i].position.x > (emitter.box.getSize().x / 2)) 
		{
			particles[i].position.x = (emitter.box.getSize().x / 2);
			particles[i].velocity.x *= -1.0;
		}
		else if(particles[i].position.x < -(emitter.box.getSize().x / 2))
		{
			particles[i].position.x = -(emitter.box.getSize().x / 2);
			particles[i].velocity.x *= -1.0;
		}

		if(particles[i].position.z > (emitter.box.getSize().z / 2))
		{
			particles[i].position.z = (emitter.box.getSize().z / 2);
			particles[i].velocity.z *= -1.0;
		}
		else if(particles[i].position.z < -(emitter.box.getSize().z / 2))
		{
			particles[i].position.z = -(emitter.box.getSize().z / 2);
			particles[i].velocity.z *= -1.0;
		}
	}
}

void Boom::setup(std::vector<Particle>& particles, Emitter& emitter)
{
	for(unsigned int i = 0; i < particles.size(); i++)
	{
		particles[i].velocity = glm::vec3(ofRandom(-1, 1), 
								ofRandom(-1, 1), ofRandom(-1, 1));
		particles[i].position = glm::vec3(0, 0, 0);
	}
}

void Boom::draw(std::vector<Particle>& particles, bool& ifBox)
{
	if(particles.size() != 0)
	{
		for(unsigned int i = 0; i < particles.size(); i++)
		{
			if(ifBox)
				ofDrawBox(particles[i].position, 1 / particles[i].age);
			else
				ofDrawSphere(particles[i].position, 1 / particles[i].age);
		}
	}
}

void Boom::update(std::vector<Particle>& particles, Emitter& emitter, float& dt)
{
	for(unsigned int i = 0; i < particles.size(); i++)
	{
		particles[i].age += ofGetLastFrameTime();
		particles[i].position -= particles[i].velocity;

		if(particles[i].position.x > (emitter.box.getSize().x / 2))
		{
			particles[i].position.x = (emitter.box.getSize().x / 2);
			particles[i].velocity.x *= -1.0;
		}
		else if(particles[i].position.x < -(emitter.box.getSize().x / 2))
		{
			particles[i].position.x = -(emitter.box.getSize().x / 2);
			particles[i].velocity.x *= -1.0;
		}

		if(particles[i].position.y > (emitter.box.getSize().y / 2))
		{
			particles[i].position.y = (emitter.box.getSize().y / 2);
			particles[i].velocity.y *= -1.0;
		}
		else if(particles[i].position.y < -(emitter.box.getSize().y / 2))
		{
			particles[i].position.y = -(emitter.box.getSize().y / 2);
			particles[i].velocity.y *= -1.0;
		}

		if(particles[i].position.z > (emitter.box.getSize().z / 2))
		{
			particles[i].position.z = (emitter.box.getSize().z / 2);
			particles[i].velocity.z *= -1.0;
		}
		else if(particles[i].position.z < -(emitter.box.getSize().z / 2))
		{
			particles[i].position.z = -(emitter.box.getSize().z / 2);
			particles[i].velocity.z *= -1.0;
		}

		if(particles[i].age > particles[i].lifetime)
			particles.erase(particles.begin() + i);
	}
}

void CustomEffect::draw(std::vector<Particle>& particles, const ofColor& color, bool& ifBox)
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		ofSetColor(color);
		ofDrawSphere(particles[i].position, ofRandom(0.3, 0.5));
		if(i < particles.size() - 1)
			ofDrawLine(particles[i].position, particles[i + 1].position);
	}
}

void CustomEffect::update(std::vector<Particle>& particles, Emitter& emitter, float& dt)
{
	for (unsigned int i = 0; i < particles.size(); i++) {

		// ------- SNOW -------
		float fakeWindX = ofSignedNoise(particles[i].position.x * 0.003, particles[i].position.y * 0.006, ofGetElapsedTimef() * 0.6);
		particles[i].friction.x = fakeWindX * 0.25 + ofSignedNoise(particles[i].uniqueVal, particles[i].position.y * 0.04) * 0.6;
		particles[i].friction.y = ofSignedNoise(particles[i].uniqueVal, particles[i].position.x * 0.006, ofGetElapsedTimef() * 0.2) * 0.09 + 0.18;

		particles[i].velocity *= particles[i].drag;
		particles[i].velocity += particles[i].friction * 0.04;


		//we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
		if(particles[i].position.y + particles[i].velocity.y < -emitter.box.getSize().y / 2)
			particles[i].position.y += emitter.box.getSize().y;

		// particle physics
		particles[i].position -= particles[i].velocity;
		particles[i].velocity += -0.1f * particles[i].position * dt;

		if(particles[i].position.x > (emitter.box.getSize().x / 2))
		{
			particles[i].position.x = (emitter.box.getSize().x / 2);
			particles[i].velocity.x *= -1.0;
		}
		else if(particles[i].position.x < -(emitter.box.getSize().x / 2))
		{
			particles[i].position.x = -(emitter.box.getSize().x / 2);
			particles[i].velocity.x *= -1.0;
		}

		if(particles[i].position.z > (emitter.box.getSize().z / 2))
		{
			particles[i].position.z = (emitter.box.getSize().z / 2);
			particles[i].velocity.z *= -1.0;
		}
		else if(particles[i].position.z < -(emitter.box.getSize().z / 2))
		{
			particles[i].position.z = -(emitter.box.getSize().z / 2);
			particles[i].velocity.z *= -1.0;
		}
	}
}

void Firework::setup(std::vector<Particle>& particles, Emitter& emitter)
{
	for(unsigned int i = 0; i < particles.size(); i++)
	{
		particles[i].velocity = glm::vec3(ofRandom(-1, 1), 
			ofRandom(-1, 1), ofRandom(-1, 1));
		particles[i].position = glm::vec3(ofRandom(-49, 49),
			ofRandom(-49, 49), ofRandom(-49, 49));
	}
}

void Firework::draw(std::vector<Particle>& particles, bool& ifBox) {
	for(unsigned int i = 0; i < particles.size(); i++)
	{
		ofDrawSphere(particles[i].position, ofRandom(0.3, 0.5));
		for(int j = i + 1; j < particles.size(); j++)
		{
			if(distance <= 20)
				ofDrawLine(particles[i].position, particles[j].position);
		}
	}
}

void Firework::update(std::vector<Particle>& particles, Emitter& emitter, float& dt)
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		particles[i].position += particles[i].velocity;

		if(particles[i].position.x > (emitter.box.getSize().x / 2))
		{
			particles[i].position.x = (emitter.box.getSize().x / 2);
			particles[i].velocity.x *= -1.0;
		}
		else if(particles[i].position.x < -(emitter.box.getSize().x / 2))
		{
			particles[i].position.x = -(emitter.box.getSize().x / 2);
			particles[i].velocity.x *= -1.0;
		}

		if(particles[i].position.y > (emitter.box.getSize().y / 2))
		{
			particles[i].position.y = (emitter.box.getSize().y / 2);
			particles[i].velocity.y *= -1.0;
		}
		else if(particles[i].position.y < -(emitter.box.getSize().y / 2))
		{
			particles[i].position.y = -(emitter.box.getSize().y / 2);
			particles[i].velocity.y *= -1.0;
		}

		if(particles[i].position.z > (emitter.box.getSize().z / 2))
		{
			particles[i].position.z = (emitter.box.getSize().z / 2);
			particles[i].velocity.z *= -1.0;
		}
		else if(particles[i].position.z < -(emitter.box.getSize().z / 2))
		{
			particles[i].position.z = -(emitter.box.getSize().z / 2);
			particles[i].velocity.z *= -1.0;
		}


		for(int j = i + 1; j < particles.size(); j++){
			distance = ofDist(
				particles[i].position.x,
				particles[i].position.y,
				particles[i].position.z,
				particles[j].position.x,
				particles[j].position.y,
				particles[j].position.z);

			if(distance <= 20)
			{
				particles[i].acceleration = glm::vec3(distance / 2000);
				particles[i].velocity -= particles[i].acceleration;
				particles[j].velocity += particles[i].acceleration;
			}
		}
	}
}