#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "point.h"

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
	void clearForce();
	void applyDrag();
	void applyGravity();
	void verlet();
	void setupCloth(int& points_X, int& points_Y, int& lineSegmentLength, int& lastMass);

	int pointsX;
	int pointsY;
	float gravityX;
	float gravityY;
	float deltaTime;
	int length;
	int current;
	int tempMass;
	int stiffness;

	std::vector<Point*> points;
	glm::vec2 startingPoint;
	glm::vec2 gravity;
	glm::vec2 size;
	ofxPanel gui;
	ofxLabel guiLabel;
	ofxIntSlider slider_restlength;
	ofxIntSlider slider_points_x;
	ofxIntSlider slider_points_y;
	ofxFloatSlider slider_gravity_x;
	ofxFloatSlider slider_gravity_y;
	ofxIntSlider slider_mass;
	ofxIntSlider slider_stiffness;
	std::string guiName;
};