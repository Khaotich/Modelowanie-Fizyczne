#include "ofApp.h"

void ofApp::setup()
{
	pointsX = 80;
	pointsY = 60;
	gravityX = 0;
	gravityY = 9.81;
	length = 6;
	tempMass = 10;
	stiffness = 500;
	guiName = "settings";
	startingPoint = {ofGetWidth() / 2 - (pointsX * length / 2), 20};

	setupCloth(pointsX, pointsY, length, tempMass);
	gui.setup(guiName);
	gui.add(guiLabel.setup("GUI", ""));
	gui.add(slider_restlength.setup("length", length, 6, 50));
	gui.add(slider_points_x.setup("x", pointsY, 1, 60));
	gui.add(slider_points_y.setup("y", pointsX, 6, 80));
	gui.add(slider_gravity_x.setup("gravity x", gravityX, -6, 6));
	gui.add(slider_gravity_y.setup("gravity y", gravityY, 1, 10));
	gui.add(slider_stiffness.setup("stiffness", stiffness, 10, 600));
}

void ofApp::update()
{
	deltaTime = 0.03;
	clearForce();

	for(int i = 0; i < points.size(); i++)
		points[i]->SpringForce(length, stiffness);

	applyGravity();
	applyDrag();

	for(int i = 0; i < points.size(); i++)
		points[i]->Verlet(points[i]->isLocked, deltaTime);

	int temp_points_x = pointsX;
	int temp_points_y = pointsY;
	float temp_gravity_x = gravityX;
	float temp_gravity_y = gravityY;
	int temp_length = length;
	int temp_stiffness = stiffness;

	if(temp_points_x != slider_points_x || temp_points_y != slider_points_y ||
	   temp_gravity_x != slider_gravity_x || temp_gravity_y != slider_gravity_y ||
	   temp_length != slider_restlength || temp_stiffness != slider_stiffness)
	{
		temp_points_x = slider_points_x;
		pointsX = temp_points_x;
		
		temp_points_y = slider_points_y;
		pointsY = temp_points_y;
		
		temp_gravity_x = slider_gravity_x;
		gravityX = temp_gravity_x;
		
		temp_gravity_y = slider_gravity_y;
		gravityY = temp_gravity_y;

		temp_length = slider_restlength;
		length = slider_restlength;

		temp_stiffness = slider_stiffness;
		stiffness = slider_stiffness;

		points.clear();
		setupCloth(pointsX, pointsY, length, tempMass);
	}
}

void ofApp::draw()
{
	ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));
	gui.draw();

	for(int i = 0; i < points.size(); i++)
	{
		for(int j = 0; j < points[i]->links.size(); j++)
		{
			ofSetColor(ofColor::lightBlue);
			ofDrawLine(points[i]->links[j].p1->position, points[i]->links[j].p2->position);
		}

		points[i]->draw();
	}
}

void ofApp::clearForce()
{
	for(int i = 0; i < points.size(); i++)
		points[i]->force = { 0, 0 };
}

void ofApp::applyDrag()
{
	for(int i = 0; i < points.size(); i++) 
		points[i]->force += -6 * 3.14 * 17.8 * 10e-05 * 
		points[i]->radius * points[i]->velocity;
}

void ofApp::applyGravity()
{
	for(int i = 0; i < points.size(); i++)
	{
		gravity = {gravityX , gravityY};
		gravity *= points[i]->mass;
		points[i]->force += gravity;
	}
}

void ofApp::verlet()
{
	for(int i = 0; i < points.size(); i++)
	{
		if (!points[i]->isLocked)
		{
			glm::vec2 tempPositionOld = points[i]->position;
			points[i]->position = points[i]->position + (points[i]->position - 
			points[i]->positionOld) + deltaTime * deltaTime * (points[i]->force 
				/ points[i]->mass);
			points[i]->positionOld = tempPositionOld;
			points[i]->velocity += (points[i]->force / points[i]->mass) / deltaTime;
		}
	}
}

void ofApp::setupCloth(int& points_X, int& points_Y, int& lineSegmentLength, int& lastMass)
{
	size = {pointsX, pointsY};
	current = 0;

	for(int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			Point* newPoint = new Point();
			newPoint->setup(ofColor::gray, 2, 1, {startingPoint.x + x * lineSegmentLength, 
							startingPoint.y + y * lineSegmentLength }, false);
			newPoint->force = {0, 0};
			newPoint->grid = {x, y};

			if(y == 0)
			{
				newPoint->color = ofColor::red;
				newPoint->radius = 2;
				newPoint->isLocked = true;
			}

			points.push_back(newPoint);
			current++;
		}
	}

	current = 0;
	for(int y = 0; y < size.y; y++)
	{
		for(int x = 0; x < size.x; x++)
		{
			if(y != 0)
			{
				int above = (y - 1) * size.x + x;
				Link l;
				l.p1 = points[current];
				l.p2 = points[above];
				points[current]->links.push_back(l);
			}

			if(x != 0)
			{
				int left = current - 1;
				Link l;
				l.p1 = points[current];
				l.p2 = points[left];
				points[current]->links.push_back(l);
			}

			current++;
		}
	}
}

void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}