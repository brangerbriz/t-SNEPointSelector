#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    dataHand.loadTSNEPoints();
    dataHand.loadTSNESelections();
    tsneSelector.getSelections() = dataHand.getTSNESelections();
    auto points = dataHand.getTSNEPoints();

    vector<ofVec2f> p;
    for (auto point : points)
    {
        p.push_back(point.point);
    }

    knnSelector.get2DPoints() = p;
    knnSelector.index();

    for (int i = 0; i < points.size(); i++)
    {
        mesh.addVertex(points[i].point);
    }

    mesh.setMode(OF_PRIMITIVE_POINTS);

    cout << "Loaded " << points.size() << " data points" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(ofColor(100), ofColor(20));

    navTransform.begin();

        glPointSize(2.0);
        mesh.draw();
        tsneSelector.draw();

        ofPoint mouse(ofGetMouseX(), ofGetMouseY());
        auto results = knnSelector.getKNearest2D(navTransform.toDataSpace(mouse), 1);
        int nearestIndex = results[0].first;
        ofPoint p = mesh.getVertices()[nearestIndex];
        ofSetColor(255, 255, 0);
        ofDrawCircle(p, 0.005);

        ofSetColor(255);

    navTransform.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
//    cout << "key pressed: " << key << endl;
    // delete key
    if (key == 8)
    {
        // delete selections...
    }
    // enter key
    else if (key == 13)
    {
        dataHand.saveTSNESelections(tsneSelector.getSelections());
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // left mouse button
    if (button == 0)
    {
        if (tsneSelector.selectionPending())
        {
            tsneSelector.addPoint(navTransform.toDataSpace(ofPoint(x, y)));
        }
        else
        {
            tsneSelector.beginSelection(navTransform.toDataSpace(ofPoint(x, y)));
        }
    }
    // right mouse button, close shape
    else if (button == 2)
    {
        tsneSelector.endSelection();
    }
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
