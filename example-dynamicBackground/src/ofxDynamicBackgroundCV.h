#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxRPiCameraVideoGrabber.h"

class ofxDynamicBackgroundCV : public ofThread
{
public:

    ofxDynamicBackgroundCV();
    
    void update(unsigned char*  pixels, int h, int w);
    void draw(int x=0, int y=0);
    
	cv::Mat accumulatorMat;
    cv::Mat frameMat;
    cv::Mat backgroundOutputMat;
    cv::Mat differenceMat;

    
    ofImage& getImageRef();
    double alpha;

    void drawDebug(float scale=1.0);
    ofxRPiCameraVideoGrabber* videoGrabber;
    void setup(ofxRPiCameraVideoGrabber* videoGrabber_);
    void threadedFunction();
    ofxCv::ContourFinder contourFinder;

};





