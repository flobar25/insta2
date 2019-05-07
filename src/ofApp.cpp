#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    recorder.setPrefix(ofToDataPath("recording/frame_"));
    recorder.setFormat("bmp");
    recorder.startThread();
    ofSetFrameRate(30);
    midiIn.openPort(0);
    midiIn.addListener(this);
    backgroundColor = ofColor::black;
    lineColor = ofColor::ghostWhite;
    lineWidth = 2;
    squareDimension = 40;
    
    ofSetBackgroundColor(backgroundColor);
    ofSetColor(lineColor);
    ofSetLineWidth(lineWidth);
    
    // init states
    for (int i = 0; i < ARRAY_SIZE; i++){
        for (int j = 0; j < ARRAY_SIZE; j++){
            rectanglesStates[i][j] = 0;
        }
    }
    
}

void ofApp::exit(){
    recorder.waitForThread();
    recorder.stopThread();
}

//--------------------------------------------------------------
void ofApp::update(){
    // show the framerate on window title
    std::stringstream strm;
    strm << "fps: " << ofGetFrameRate();
    ofSetWindowTitle(strm.str());
    
    if (recording){
        //Boolean shouldMoveASquare = true;
        for (int i = 0; i < ARRAY_SIZE; i++){
            for (int j = 0; j < ARRAY_SIZE; j++){
                //shouldMoveASquare &= rectanglesStates[i][j] == 0;
                if (rectanglesStates[i][j] > 0){
                    rectanglesStates[i][j]--;
                } else {
                    rectanglesStates[i][j] = ofRandom(1000);
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    for (int i = 0; i < ARRAY_SIZE; i++){
        for (int j = 0; j < ARRAY_SIZE; j++){
            int x =  (i - (ARRAY_SIZE/2)) * squareDimension;
            int y =  (j - (ARRAY_SIZE/2)) * squareDimension;
            int z =  sin(rectanglesStates[i][j] / 100.0) * 100;
            drawRectangle(glm::vec3(x, y, z), squareDimension, squareDimension, backgroundColor, lineColor, lineWidth);
        }
    }
    cam.end();
    
    // capture the image if recording is started
    // this can slow down the rendering by a lot, so be aware of the framerate...
    // if frames are skipped this is going to mess up the rendering when imported as a video
    if (recording){
        screenCapture.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        recorder.addFrame(screenCapture);
    }
}

void ofApp::drawRectangle(glm::vec3 location, int height, int width, ofColor fillColor, ofColor lineColor, int lineWidth) {
    ofFill();
    ofSetColor(fillColor);
    ofDrawRectangle(location, height - lineWidth, width - lineWidth);
    
    ofNoFill();
    ofSetColor(lineColor);
    ofDrawRectangle(location, height, width);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
        case 'r':
            toggleRecording();
            break;
        case 'p':
            captureScreen();
            break;
        default:
            break;
    }
}

void ofApp::newMidiMessage(ofxMidiMessage& eventArgs){
    
}

void ofApp::captureScreen(){
    screenCapture.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    screenCapture.save("captures/capture.bmp");
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

void ofApp::toggleRecording(){
    recording = !recording;
}

