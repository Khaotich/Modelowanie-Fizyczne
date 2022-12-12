#include "ofMain.h"
#include "ofApp.h"

int main() 
{
	ofGLWindowSettings settings;
	settings.setGLVersion(4, 6);
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW;
	ofCreateWindow(settings);
	ofSetWindowTitle("Particle System");

	ofRunApp(new ofApp());
}