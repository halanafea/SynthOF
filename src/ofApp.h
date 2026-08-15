#pragma once
#include "Synthesizer.h"
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void audioOut(ofSoundBuffer & buffer);

private:
	Synthesizer synth;
	ofSoundStream soundStream;
};
