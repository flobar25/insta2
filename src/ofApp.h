#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxImageSequenceRecorder.h"

#define ROWS_SIZE 16
#define COLUMNS_SIZE 100
#define Z_MAX 1000

class ofApp : public ofBaseApp, public ofxMidiListener {
    
public:
    void setup();
    void exit();
    void update();
    void draw();
    
    // recording
    void toggleRecording();
    void toggleStarted();
    void captureScreen();
    
    // MIDI
    void newMidiMessage(ofxMidiMessage& eventArgs);
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
    
    void drawRectangle(glm::vec3 location, int height, int width, ofColor fillColor, ofColor lineColor, int lineWidth);
    

    
private:
    // midi
    ofxMidiIn midiIn;
    
    // camera
    ofEasyCam cam;
    
    // recording
    ofxImageSequenceRecorder recorder;
    Boolean recording;
    Boolean started;
    ofImage screenCapture;
    
    // colors
    ofColor backgroundColor;
    ofColor lineColor;
    int lineWidth;
    int squareDimension;
    
    // rectangles
    int rectanglesStates[COLUMNS_SIZE][ROWS_SIZE];
};
