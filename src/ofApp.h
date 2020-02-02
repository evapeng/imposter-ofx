#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void toggleFullScreen(const void * sender, bool & newValue);
        void zoomInput(const void * sender, ofVec2f & newValue);
        void changeCamera(int num);
		
        ofVideoPlayer video;
        ofVideoGrabber cam;
        ofPlanePrimitive plane;
        ofShader shader;
        
        ofVideoPlayer movie;
        ofVideoPlayer testFG;
        ofVideoGrabber camera;

        ofxPanel gui;
        ofxFloatSlider floatSlider;
        ofxIntSlider intSlider;
        ofxToggle toggle;
        ofParameter<bool> fullScreen;

        ofFbo fboCam;
        ofFbo fboBG;
        ofFbo fboMain;

        ofxXmlSettings XML;
        string message;
        int camWidth;
        int camHeight;
        int bgWidth;
        int bgHeight;
        
        int outputWidth;
        int outputHeight;
};
