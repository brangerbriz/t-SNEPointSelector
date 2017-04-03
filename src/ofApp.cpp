#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    dataHand.loadTSNEPoints();
    dataHand.loadTSNESelections();
    selector.getSelections() = dataHand.getTSNESelections();
    auto points = dataHand.getTSNEPoints();
    for (int i = 0; i < points.size(); i++)
    {
        mesh.addVertex(points[i].point);
    }

    mesh.setMode(OF_PRIMITIVE_POINTS);
    glPointSize(2.0);

    cout << "Loaded " << points.size() << " data points" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(ofColor(100), ofColor(20));

    navTransform.begin();
        mesh.draw();
        selector.draw();
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
        dataHand.saveTSNESelections(selector.getSelections());
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
        if (selector.selectionPending())
        {
            selector.addPoint(navTransform.toDataSpace(ofPoint(x, y)));
        }
        else
        {
            selector.beginSelection(navTransform.toDataSpace(ofPoint(x, y)));
        }
    }
    // right mouse button, close shape
    else if (button == 2)
    {
        selector.endSelection();
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
