#pragma once
#include "defines.h"
#include "ofMain.h"
#include "ofxJSON.h"
#include "NavTransformer.h"
#include "TSNESelect.h"
#include "KNNSelect.h"
#include "DataHandler.h"
#include "GUI.h"
#include "MidiPlayer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);
		void mousePressed(int x, int y, int button);

        void knnSearch();
        void knnSave();

        ofMesh mesh; // mesh to hold the points
        vector<pair<int, float> > neighbors;
        NavTransformer navTransform;
        TSNESelector tsneSelector;
        KNNSelector knnSelector;
        DataHandler dataHand;
        GUI gui;
        MidiPlayer midiPlayer;
};
