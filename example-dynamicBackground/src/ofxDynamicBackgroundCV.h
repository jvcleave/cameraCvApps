#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxRPiCameraVideoGrabber.h"

class ofxDynamicBackgroundCV : public ofThread
{
public:

    ofxDynamicBackgroundCV();
    
    void draw(int x=0, int y=0);
    
	cv::Mat accumulatorMat;
    cv::Mat cameraMat;
    cv::Mat backgroundOutputMat;
    cv::Mat differenceMat;

    double alpha;

    void drawDebug(float scale=1.0);
    ofxRPiCameraVideoGrabber* videoGrabber;
    void setup(ofxRPiCameraVideoGrabber* videoGrabber_);
    void threadedFunction();
    ofxCv::ContourFinder contourFinder;
};





