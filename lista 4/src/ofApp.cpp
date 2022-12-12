#include "ofApp.h"

void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofEnableSmoothing();

	cam.setTarget(emitter);
	cam.setDistance(200);
	cam.setNearClip(10);
	cam.setFarClip(1000);

	drawingGrid = false;
	debugText = false;
	box.set(20);

	gui.setup();
	mixerGroup.setup("GUI");
	mixerGroup.setHeaderBackgroundColor(ofColor::darkBlue);
	mixerGroup.setBorderColor(ofColor::darkBlue);
	mixerGroup.add(sliderSize.set("box size", 100, 100, 500));
	mixerGroup.add(sliderNumOfPart.set("number of particles", 1000, 1, 2000));
	mixerGroup.add(toggler.setup(ifBox, false));
	toggler.setName("particles in box shape");
	mixerGroup.add(color.set(ofColor::white));
	fbo3d.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	gui.add(&mixerGroup);

	particle_effect.setup(sliderNumOfPart, emitter);
	boom.setup(particle_effect.particles, emitter);
	firework.setup(particle_effect.particles, emitter);

	keyEffect = 0;
}

void ofApp::update()
{
	emitter.update();
	if(keyEffect == 0)
	{
		particle_effect.particles.clear();
		particle_effect.setup(sliderNumOfPart, emitter);
	}

	if(keyEffect == 1)
		snow.update(particle_effect.particles, emitter, deltaTime);

	if(keyEffect == 2)
		matrix.update(particle_effect.particles, emitter, deltaTime);

	if(keyEffect == 3)
		boom.update(particle_effect.particles, emitter, deltaTime);

	if(keyEffect == 4)
		custom.update(particle_effect.particles, emitter, deltaTime);

	if(keyEffect == 5)
		firework.update(particle_effect.particles, emitter, deltaTime);

	if(toggler.getParameter().toString() == "0")
		ifBox = false;
	else
		ifBox = true;

	if(sliderSize != temp_size or sliderNumOfPart != temp_numOfPart)
	{
		particle_effect.particles.clear();
		particle_effect.setup(sliderNumOfPart, emitter);
		
		if(keyEffect == 3)
			boom.setup(particle_effect.particles, emitter);

		temp_size = sliderSize;
		temp_numOfPart = sliderNumOfPart;
	}
}

void ofApp::draw()
{
	ofDisableDepthTest();
	ofDisableSeparateSpecularLight();
	ofDisableLighting();
	gui.draw();
	cam.begin();

	ofEnableDepthTest();
	ofDisableLighting();

	ofPushStyle();
	box.setPosition(0, 0, 0);
	emitter.draw(sliderSize);

	if(keyEffect == 1)
		snow.draw(particle_effect.particles, ifBox);

	if(keyEffect == 2)
		matrix.draw(particle_effect.particles);

	if(keyEffect == 3)
		boom.draw(particle_effect.particles, ifBox);

	if(keyEffect == 4)
		custom.draw(particle_effect.particles, color.get(), ifBox);

	if(keyEffect == 5)
		firework.draw(particle_effect.particles, ifBox);

	ofPushStyle();
	ofPopStyle();

	if(drawingGrid)
		grid.draw();

	if(debugText)
	{
		ofDrawBitmapString(".(x:-50, y:50, z:50) ", glm::vec3(-50, 50, 50));
		ofDrawBitmapString(".(x:50, y:-50, z:50) ", glm::vec3(50, -50, 50));
		ofDrawBitmapString(".(x:50, y:50, z:-50) ", glm::vec3(50, 50, -50));
		ofDrawBitmapString(".(x:-50, y:-50, z:50) ", glm::vec3(-50, -50, 50));
		ofDrawBitmapString(".(x:50, y:-50, z:-50) ", glm::vec3(50, -50, -50));
		ofDrawBitmapString(".(x:-50, y:50, z:-50) ", glm::vec3(-50, 50, -50));
		ofDrawBitmapString(".(x:-50, y:-50, z:-50) ", glm::vec3(-50, -50, -50));
		ofDrawBitmapString(".(x:50, y:50, z:50) ", glm::vec3(50, 50, 50));

		ofDrawBitmapString(".boxCorner", (box.getSize() / 2));
		ofDrawBitmapString(".boxCorner", (-box.getSize() / 2));

		ofDrawBitmapString(".boxCorner", -box.getSize().x / 2,
			box.getSize().y / 2, box.getSize().z / 2);
		ofDrawBitmapString(".boxCorner", box.getSize().x / 2,
			-box.getSize().y / 2, box.getSize().z / 2);
		ofDrawBitmapString(".boxCorner", box.getSize().x / 2,
			box.getSize().y / 2, -box.getSize().z / 2);

		ofDrawBitmapString(".boxCorner", -box.getSize().x / 2,
			-box.getSize().y / 2, box.getSize().z / 2);
		ofDrawBitmapString(".boxCorner", box.getSize().x / 2,
			-box.getSize().y / 2, -box.getSize().z / 2);
		ofDrawBitmapString(".boxCorner", -box.getSize().x / 2
			, box.getSize().y / 2, -box.getSize().z / 2);

		ofDrawBitmapString(".boxCenter", (box.getGlobalPosition()));
	}

	ofPopStyle();
	cam.end();
}

void ofApp::keyPressed(int key)
{
	if(key == 'g')
	{
		if(!drawingGrid)
			drawingGrid = true;
		else
			drawingGrid = false;
	}

	if(key == ' ') 
	{
		particle_effect.particles.clear();
		particle_effect.setup(sliderNumOfPart, emitter);
	}

	if(key == 't')
	{
		if(!debugText)
			debugText = true;
		else
			debugText = false;
	}

	if(key == '0')
	{
		particle_effect.particles.clear();
		particle_effect.setup(sliderNumOfPart, emitter);
		keyEffect = 0;
	}

	if(key == '1')
	{
		particle_effect.particles.clear();
		particle_effect.setup(sliderNumOfPart, emitter);
		keyEffect = 1;
	}

	if(key == '2')
	{
		particle_effect.particles.clear();
		particle_effect.setup(sliderNumOfPart, emitter);
		keyEffect = 2;
	}

	if(key == '3')
	{
		particle_effect.particles.clear();
		particle_effect.setup(sliderNumOfPart, emitter);
		boom.setup(particle_effect.particles, emitter);
		keyEffect = 3;
	}

	if(key == '4')
	{
		particle_effect.particles.clear();
		particle_effect.setup(sliderNumOfPart, emitter);
		keyEffect = 4;
	}

	if(key == '5')
	{
		particle_effect.particles.clear();
		particle_effect.setup(sliderNumOfPart, emitter);
		firework.setup(particle_effect.particles, emitter);
		keyEffect = 5;
	}
}

void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}