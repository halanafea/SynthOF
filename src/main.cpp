#include "ofMain.h"
#include "ofApp.h"
#include "ofLog.h"

//========================================================================
int main( ){

	//This forces OF's logging system to fully initialize before any other library code gets a chance to log something too early.
	ofSetLoggerChannel(std::shared_ptr<ofBaseLoggerChannel>(new ofConsoleLoggerChannel())); 

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();

}
