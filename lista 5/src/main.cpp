#include "ofMain.h"
#include "ofApp.h"

int main()
{
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	ofCreateWindow(settings);
	ofSetWindowTitle("Mass Spring System");

	ofRunApp(new ofApp());
}
