#include "grid.h"

void Grid::customDraw()
{
	ofPushStyle();
	ofSetColor(255, 100, 100);
	ofDrawGrid(100.0f);
	ofPopStyle();
}