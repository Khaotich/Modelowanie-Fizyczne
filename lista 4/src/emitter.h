#pragma once
#include "ofMain.h"

class Emitter : public ofNode
{
public:
	ofBoxPrimitive box;
	void draw(ofParameter<int>& boxSize);
	void update();
};