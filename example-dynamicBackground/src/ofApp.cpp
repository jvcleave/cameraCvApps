#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);			
	consoleListener.setup(this);
    
    omxCameraSettings.width = 640;
    omxCameraSettings.height = 480;
    omxCameraSettings.framerate = 30;
    omxCameraSettings.enableTexture = true;
    omxCameraSettings.enablePixels = true;
    videoGrabber.setup(omxCameraSettings);
    
    dynamicBackground.setup(&videoGrabber);
}	

//--------------------------------------------------------------
void ofApp::update()
{
    if(videoGrabber.isFrameNew())
    {

    }
}


//--------------------------------------------------------------
void ofApp::draw(){
	
	videoGrabber.draw();
    dynamicBackground.draw(videoGrabber.getWidth(), 0);
	stringstream info;
	info << "APP FPS: " << ofGetFrameRate() << endl;
	info << "Camera Resolution: " << videoGrabber.getWidth() << "x" << videoGrabber.getHeight()	<< " @ "<< videoGrabber.getFrameRate() <<"FPS"<< endl;
    
	info << endl;
    info << "PRESS r TO RESET: " << endl;

    ofDrawBitmapStringHighlight(info.str(), 100, 100, ofColor::black, ofColor::yellow);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key)
{
	ofLog(OF_LOG_VERBOSE, "%c keyPressed", key);
    switch (key) 
    {
        case 'r':
        {
            break;
        } 
        default:
        {
            break;
        }
        
    }
}

