#include "ofApp.h"
#include "SineOscillator.h"

void ofApp::setup() {
	ofBackground(20);
	ofSetWindowTitle("Synth - Phase 1");

	// Register one key -> one sound for Phase 1
	synth.addVoice('a', std::make_unique<SineOscillator>(), 440.0f); // A4

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
	ofDrawBitmapString("Press and hold A to play a sine tone", 20, 20);

	// Basic waveform visualization
	ofSetColor(120, 220, 160);
	const auto & samples = synth.getRecentSamples();
	if (samples.size() > 1) {
		float xStep = static_cast<float>(ofGetWidth()) / samples.size();
		float midY = ofGetHeight() / 2.0f;
		for (size_t i = 0; i < samples.size() - 1; i++) {
			float x1 = i * xStep;
			float y1 = midY + samples[i] * 150.0f;
			float x2 = (i + 1) * xStep;
			float y2 = midY + samples[i + 1] * 150.0f;
			ofDrawLine(x1, y1, x2, y2);
		}
	}
}

void ofApp::keyPressed(int key) {
	synth.noteOn(static_cast<char>(key));
}

void ofApp::keyReleased(int key) {
	synth.noteOff(static_cast<char>(key));
}
