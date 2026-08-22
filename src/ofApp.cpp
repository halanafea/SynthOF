#include "ofApp.h"
#include "SawOscillator.h"
#include "SineOscillator.h"
#include "SquareOscillator.h"
#include <cctype>

void ofApp::setup() {
	ofBackground(15, 15, 25);
	ofSetWindowTitle("Synth - Phase 1");

	synth.addVoice('a', std::make_unique<SineOscillator>(), 440.0f); // A4 - working
	synth.addVoice('s', std::make_unique<SquareOscillator>(), 493.88f); // B4
	synth.addVoice('d', std::make_unique<SawOscillator>(), 523.25f); // C5

	buttons = {
		{ 'a', "A - Sine", ofColor(90, 220, 160), ofRectangle(40, 60, 160, 90) },
		{ 's', "S - Square", ofColor(150, 120, 230), ofRectangle(220, 60, 160, 90) },
		{ 'd', "D - Saw", ofColor(230, 140, 70), ofRectangle(400, 60, 160, 90) },
	};

	ofSoundStreamSettings settings;
	settings.setOutListener(this);
	settings.sampleRate = 44100;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 0;
	settings.bufferSize = 256;
	soundStream.setup(settings);
}

void ofApp::audioOut(ofSoundBuffer & buffer) {
	for (size_t i = 0; i < buffer.getNumFrames(); i++) {
		float sample = synth.getNextSample(static_cast<float>(buffer.getSampleRate()));
		for (size_t ch = 0; ch < buffer.getNumChannels(); ch++) {
			buffer.getSample(i, ch) = sample;
		}
	}
}

void ofApp::update() { }

void ofApp::draw() {
	ofSetColor(255);
	ofDrawBitmapString("Press A, S, or D  |  or click a button below", 40, 30);

	drawButtons();
	drawWaveform();
}

void ofApp::drawButtons() {
	for (const auto & btn : buttons) {
		bool implemented = synth.hasVoice(btn.key);
		bool active = synth.isKeyActive(btn.key);

		ofColor fill = btn.color;
		if (!implemented) {
			fill = ofColor(60, 60, 70); // dimmed - not built yet
		} else if (active) {
			fill.a = 255;
		} else {
			fill.a = 160; // implemented but idle
		}

		ofSetColor(fill);
		ofFill();
		ofDrawRectRounded(btn.bounds, 10);

		ofSetColor(implemented ? ofColor(20, 20, 20) : ofColor(140, 140, 140));
		ofDrawBitmapString(btn.label, btn.bounds.x + 14, btn.bounds.y + btn.bounds.height / 2);

		if (active) {
			ofNoFill();
			ofSetColor(255);
			ofSetLineWidth(2);
			ofDrawRectRounded(btn.bounds, 10);
			ofFill();
		}
	}
}

void ofApp::drawWaveform() {
	float panelX = 40, panelY = 190, panelW = 520, panelH = 200;

	ofSetColor(25, 25, 40);
	ofDrawRectRounded(panelX, panelY, panelW, panelH, 8);

	auto samples = synth.getRecentSamples();
	if (samples.size() > 1) {
		float xStep = panelW / samples.size();
		float midY = panelY + panelH / 2.0f;

		ofColor quietColor(90, 60, 200); // deep purple - low amplitude
		ofColor loudColor(255, 90, 180); // bright pink - high amplitude

		for (size_t i = 0; i < samples.size() - 1; i++) {
			float amplitude = fabs(samples[i]); // 0.0 (silent) to ~1.0 (loud)
			float blend = ofClamp(amplitude * 3.0f, 0.0f, 1.0f); // amplify small values so color shows clearly

			ofColor waveColor = quietColor.getLerped(loudColor, blend);
			ofSetColor(waveColor);
			ofSetLineWidth(2);

			float x1 = panelX + i * xStep;
			float y1 = midY + samples[i] * (panelH / 2.5f);
			float x2 = panelX + (i + 1) * xStep;
			float y2 = midY + samples[i + 1] * (panelH / 2.5f);
			ofDrawLine(x1, y1, x2, y2);
		}
	}
}

void ofApp::handleClick(int x, int y, bool pressed) {
	for (const auto & btn : buttons) {
		if (btn.bounds.inside(x, y)) {
			if (pressed)
				synth.noteOn(btn.key);
			else
				synth.noteOff(btn.key);
		}
	}
}

/** void ofApp::keyPressed(int key) {
	synth.noteOn(static_cast<char>(key));
}

void ofApp::keyReleased(int key) {
	synth.noteOff(static_cast<char>(key));
}*/

/* void ofApp::keyPressed(int key) {

	 std::cout << "Key pressed: " << key << std::endl;

	char k = tolower(static_cast<char>(key));
	if (k == 'a' || k == 's' || k == 'd') {
		synth.noteOn(k);
	}
}

void ofApp::keyReleased(int key) {
	char k = tolower(static_cast<char>(key));
	if (k == 'a' || k == 's' || k == 'd') {
		synth.noteOff(k);
	}
}*/

void ofApp::keyPressed(int key) {
	if (key == 'a' || key == 'A') {
		synth.noteOn('a');
	} else if (key == 's' || key == 'S') {
		synth.noteOn('s');
	} else if (key == 'd' || key == 'D') {
		synth.noteOn('d');
	}
}

void ofApp::keyReleased(int key) {
	if (key == 'a' || key == 'A') {
		synth.noteOff('a');
	} else if (key == 's' || key == 'S') {
		synth.noteOff('s');
	} else if (key == 'd' || key == 'D') {
		synth.noteOff('d');
	}
}
void ofApp::mousePressed(int x, int y, int button) {
	handleClick(x, y, true);
}

void ofApp::mouseReleased(int x, int y, int button) {
	handleClick(x, y, false);
}
