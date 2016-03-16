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


void ofxDynamicBackgroundCV::draw(int x, int y) //default:0,0
{
    if (!backgroundOutputMat.empty()) 
    {
         ofxCv::drawMat(backgroundOutputMat, x, y);
    }
   
}

void ofxDynamicBackgroundCV::threadedFunction()
{
    while (isThreadRunning()) 
    {
        if (!videoGrabber) 
        {
            return;
        }
        if(videoGrabber->isFrameNew())
        {
            
            cameraMat = cv::Mat(videoGrabber->getHeight(),
                                videoGrabber->getWidth(),
                                CV_8UC4,
                                videoGrabber->getPixels(),
                                0);
            if(accumulatorMat.empty())
            {
                cameraMat.convertTo(accumulatorMat, CV_32F);
            }
            
            cv::accumulateWeighted(cameraMat, accumulatorMat, alpha);
            cv::convertScaleAbs(accumulatorMat, backgroundOutputMat);
        }
        if (!cameraMat.empty()) 
        {
            cv::subtract(backgroundOutputMat, cameraMat, differenceMat);

        }
        if(!differenceMat.empty())
        {
            ofxCv::blur(differenceMat, 20);
            contourFinder.findContours(differenceMat);

        }
        
    }
}
void ofxDynamicBackgroundCV::drawDebug(float scale) //default:1.0
{
    float scaledWidth = cameraMat.size().width*scale;
    float scaledHeight = cameraMat.size().height*scale;
    ofColor color1 = ofColor::black;
    ofColor color2 = ofColor::yellow;
    
    ofxCv::drawMat(cameraMat, 0, 0, scaledWidth, scaledHeight);
    ofDrawBitmapStringHighlight("cameraMat", 0, 20, color1, color2);
    
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

