#include "ofApp.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(toggle.setup("toggle", fullScreen));
    toggle.addListener(this, &ofApp::toggleFullScreen);
    fullScreen.addListener(this, &ofApp::toggleFullScreen);

    camera.setDeviceID(0); // set device
    
    shader.load("shadersGL3/shader");
    
    if( XML.loadFile("mySettings.xml") ){
        message = "mySettings.xml loaded!";
    }else{
        message = "unable to load mySettings.xml check data/ folder";
    }
    
    string sceneName = XML.getValue("DEBUG", "defaultScene");
    
    ofLog(OF_LOG_NOTICE, ofToString("1, " + sceneName));

    camWidth = XML.getValue("VIDEO:CAMERA:WIDTH", 640);
    camHeight = XML.getValue("VIDEO:CAMERA:HEIGHT", 360);
    
    bgWidth = XML.getValue("VIDEO:BACKGROUND:WIDTH", 640);
    bgHeight = XML.getValue("VIDEO:BACKGROUND:HEIGHT", 360);
    
    outputWidth = XML.getValue("VIDEO:OUTPUT:WIDTH", 640);
    outputHeight = XML.getValue("VIDEO:OUTPUT:HEIGHT", 360);
    
    camera.setVerbose(false);
    camera.initGrabber(camWidth, camHeight);

    movie.load("battlestar.mp4");
    testFG.load("greenscreen3.mov");
    testFG.play();

    // say how big you want each FBO to be
    fboCam.allocate(camWidth, camHeight, GL_RGBA);
    fboBG.allocate(bgWidth, bgHeight, GL_RGBA);
    fboMain.allocate(outputWidth, outputHeight, GL_RGBA);
}

//--------------------------------------------------------------
void ofApp::update(){
    camera.update();
    movie.update();
    testFG.update();
}

void ofApp::changeCamera(int num){
   camera.close();
   camera.setDeviceID(num);
   camera.initGrabber(camWidth, camHeight); // change this to your settings
}

void ofApp::toggleFullScreen(const void * sender, bool & pressed){
    ofToggleFullscreen();
    if (pressed) {
        gui.setPosition(-500., -500.);
    }
    else gui.setPosition(0, 0);
}

void ofApp::zoomInput(const void * sender, ofVec2f & zoom){
    
}

void ofApp::draw(){
    gui.draw();
    fboCam.begin();
        ofClear(255, 255, 255, 255);
        ofTexture fgInput = camera.getTexture();
        fgInput.draw(0, 0);
    fboCam.end();
    
    fboBG.begin();
        ofClear(255, 255, 255, 255);
        ofImage bgInput = movie.getPixels();
        bgInput.draw(0, 0);
    fboBG.end();
    
    ofTexture tex1 = fboCam.getTexture();
    ofTexture tex2 = fboBG.getTexture();
        
    fboMain.begin();
        ofClear(255, 255, 255, 255);
        shader.begin();
            shader.setUniformTexture("fgInput", tex1, 1);
            shader.setUniformTexture("bgInput", tex2, 2);
            fgInput.draw(0,0);
        shader.end();
    fboMain.end();
    
    float disWidth = 320;
    float disHeight= 240;
    float spacer = 15;

    ofSetColor(255);
    fgInput.draw(gui.getWidth() + spacer, 5, disWidth, disHeight);
    ofSetColor(ofColor::red);
    ofDrawBitmapString("TESTING FG", gui.getWidth() + spacer * 2, 5+30);

    ofSetColor(255);
    movie.draw(spacer * 2 + gui.getWidth() + disWidth, 5, disWidth, disHeight);
    ofSetColor(ofColor::blue);
    ofDrawBitmapString("BACKGROUND", spacer * 3 + gui.getWidth() + disWidth, 5+30);

    ofSetColor(255);
    fboMain.draw(gui.getWidth() + spacer, 5 + disHeight + spacer, outputWidth, outputHeight);
    ofDrawBitmapString("Final FBO", gui.getWidth() + spacer * 2, 5 + 30 + disHeight + spacer);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'f':
            fullScreen.set(!fullScreen);
            break;
        case '0':
            changeCamera(0);
            break;
        case '1':
            changeCamera(1);
            break;
        case '2':
            changeCamera(2);
            break;
        case '3':
            changeCamera(3);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
