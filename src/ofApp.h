#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "NavTransformer.h"

struct tSNEPoint {
public:
    string id;
    ofPoint point;
    bool selected;
};

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
        void mouseScrolled(int x, int y, float scrollX, float scrollY);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void drawPolylines();
        void updateSelected();
        void saveSelected();

        int numSelected;
        ofPoint pWindowSize;
        ofMesh mesh; // mesh to hold the points
        vector<tSNEPoint> data;
        vector<ofPolyline> polylines;
        NavTransformer navTransform;
};
