#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetVerticalSync(false);
	ofSetLogLevel(OF_LOG_VERBOSE);			
	consoleListener.setup(this);
    omxCameraSettings.width = 640;
    omxCameraSettings.height = 480;
    omxCameraSettings.framerate = 30;
    omxCameraSettings.enableTexture = true;
    omxCameraSettings.enablePixels = true;
    videoGrabber.setup(omxCameraSettings);
    
    objectFinder.setup("haarcascade_frontalface_alt2.xml");
    objectFinder.setPreset(ofxCv::ObjectFinder::Fast);
    
    cameraMat = cv::Mat(cvSize(omxCameraSettings.width,
                               omxCameraSettings.height),
                        CV_8UC4,
                        videoGrabber.getPixels(),
                        cv::Mat::AUTO_STEP);
    
}	

//--------------------------------------------------------------
void ofApp::update()
{
    if(videoGrabber.isFrameNew())
    {
        objectFinder.update(cameraMat);
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
	
	videoGrabber.draw();
    objectFinder.draw();
    
	stringstream info;
	info << "APP FPS: " << ofGetFrameRate() << endl;
	info << "Camera Resolution: " << videoGrabber.getWidth() << "x" << videoGrabber.getHeight()	<< " @ "<< videoGrabber.getFrameRate() <<"FPS"<< endl;
    
	info << endl;
    //info << "PRESS r TO RESET: " << endl;

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

