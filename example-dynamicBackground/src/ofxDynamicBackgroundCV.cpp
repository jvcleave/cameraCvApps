#include "ofxDynamicBackgroundCV.h"


ofxDynamicBackgroundCV::ofxDynamicBackgroundCV()
{
    alpha = 0.01;
    videoGrabber = NULL;
}

void ofxDynamicBackgroundCV::setup(ofxRPiCameraVideoGrabber* videoGrabber_)
{
    videoGrabber = videoGrabber_;
    contourFinder.setMinAreaRadius(50);
    contourFinder.setMaxAreaRadius(600);
    contourFinder.setThreshold(20);
    
    startThread();
}

void ofxDynamicBackgroundCV::update(unsigned char*  pixels, int h, int w)
{
    frameMat = cv::Mat(h, w, CV_8UC4, pixels, 0);
    if(accumulatorMat.empty())
    {
        frameMat.convertTo(accumulatorMat, CV_32F);
    }
    
    cv::accumulateWeighted(frameMat, accumulatorMat, alpha);
    cv::convertScaleAbs(accumulatorMat, backgroundOutputMat);
    
}



void ofxDynamicBackgroundCV::draw(int x, int y) //default:0,0
{
    ofxCv::drawMat(backgroundOutputMat, x, y);
}

void ofxDynamicBackgroundCV::threadedFunction()
{
    while (isThreadRunning()) 
    {
        if(videoGrabber->isFrameNew())
        {
            update(videoGrabber->getPixels(),
                   videoGrabber->getHeight(),
                   videoGrabber->getWidth());
        }
        cv::subtract(backgroundOutputMat, frameMat, differenceMat);
        if(!differenceMat.empty())
        {
            ofxCv::blur(differenceMat, 20);
            contourFinder.findContours(differenceMat);

        }
        
    }
}
void ofxDynamicBackgroundCV::drawDebug(float scale) //default:1.0
{
    float scaledWidth = frameMat.size().width*scale;
    float scaledHeight = frameMat.size().height*scale;
    ofColor color1 = ofColor::black;
    ofColor color2 = ofColor::yellow;
    
    ofxCv::drawMat(frameMat, 0, 0, scaledWidth, scaledHeight);
    ofDrawBitmapStringHighlight("frameMat", 0, 20, color1, color2);
    
    ofPushMatrix();
        ofTranslate(0, scaledHeight);
            ofxCv::drawMat(backgroundOutputMat, 0, 0, scaledWidth, scaledHeight);
            ofDrawBitmapStringHighlight("backgroundOutputMat", 0, 20, color1, color2);
    ofPopMatrix();

    ofPushMatrix();
        ofTranslate(scaledWidth, 0);
            ofxCv::drawMat(accumulatorMat, 0, 0, scaledWidth, scaledHeight);
            ofDrawBitmapStringHighlight("accumulatorMat", 0, 20, color1, color2);
    ofPopMatrix();
}