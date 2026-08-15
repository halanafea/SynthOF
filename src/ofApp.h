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
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void audioOut(ofSoundBuffer & buffer);

private:
	struct SoundButton {
		char key;
		std::string label;
		ofColor color;
		ofRectangle bounds;
	};

	void drawButtons();
	void drawWaveform();
	void handleClick(int x, int y, bool pressed);

	Synthesizer synth;
	ofSoundStream soundStream;
	std::vector<SoundButton> buttons;
};
