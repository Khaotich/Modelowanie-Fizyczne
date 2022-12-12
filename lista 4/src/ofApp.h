#pragma once
#include "ofMain.h"
#include "emitter.h"
#include "grid.h"
#include "ofxGui.h"
#include "particleEffect.h"

class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	bool drawingGrid;
	bool debugText;
	bool ifBox;

	ofEasyCam cam;
	ofLight light;
	ofMaterial material;
	Grid grid;
	ofBoxPrimitive box;

	ofxPanel gui;
	ofxGuiGroup mixerGroup;
	ofxIntSlider show2d;
	ofParameter<int> sliderSize;
	ofParameter<int> sliderNumOfPart;
	ofxToggle toggler;
	ofFbo fbo3d;
	ofParameter<int> temp_size;
	ofParameter<int> temp_numOfPart;
	ofParameter<ofColor> color;

	Emitter emitter;
	ParticleEffect particle_effect;
	Snow snow;
	Matrix matrix;
	Boom boom;
	CustomEffect custom;
	Firework firework;

	int numOfParticles = 3000;
	float deltaTime = ofGetLastFrameTime();
	int keyEffect;
};