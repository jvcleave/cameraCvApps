#pragma once

#include "ofMain.h"
#include "TerminalListener.h"
#include "ofxRPiCameraVideoGrabber.h"
#include "ofxCv.h"


class ofApp : public ofBaseApp, public KeyListener{

	public:

		void setup();
		void update();
		void draw();
		void keyPressed(int key);

	void onCharacterReceived(KeyListenerEventData& e)
    {
        keyPressed((int)e.character);
    };

	TerminalListener consoleListener;
    
    OMXCameraSettings omxCameraSettings;
    ofxRPiCameraVideoGrabber videoGrabber;
};

