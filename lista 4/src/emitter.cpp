#include "emitter.h"

void Emitter::draw(ofParameter<int>& boxSize)
{
	ofPushStyle();
	ofSetColor(ofColor::teal);
	ofNoFill();
	ofDrawBox(boxSize);
	ofPopStyle();
	box.set(boxSize);
}

void Emitter::update() {}