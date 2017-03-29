#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    numSelected = 0;

    string file = "points.json";
    ofxJSONElement result;
    bool parsingSuccessful = result.open(file);
    for (int i=0; i<result.size(); i++) {
        DataPoint d;
        d.id = result[i]["id"].asString();
        d.point.set(result[i]["point"][0].asFloat(),
                    result[i]["point"][1].asFloat());
        data.push_back(d);
        mesh.addVertex(ofPoint(ofGetWidth(), ofGetHeight()) * d.point);
    }

    mesh.setMode(OF_PRIMITIVE_POINTS);

    cout << "Loaded " << data.size() << " data points" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(100), ofColor(20));
//    for (int i=0; i<data.size(); i++) {
//        if (data[i].selected) {
//            ofSetColor(0, 255, 0, 180);
//        }
//        else {
//            ofSetColor(255, 180);
//        }
//        ofDrawCircle(ofGetWidth() * data[i].point.x, ofGetHeight() * data[i].point.y, 4);
//    }
    ofSetColor(255);
    drawPolylines();
    mesh.draw();
    string str = "selected: " + ofToString(numSelected);
    ofDrawBitmapStringHighlight(str, 15, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    cout << "key pressed: " << key << endl;
    // delete key
    if (key == 8)
    {
        polylines.clear();
        updateSelected();
    }
    // enter key
    else if (key == 13)
    {
        saveSelected();
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::drawPolylines() {
    for (int i = 0; i < polylines.size(); i++)
    {
        polylines[i].draw();
    }
}

void ofApp::updateSelected() {
    numSelected = 0;
    for (int i = 0; i < data.size(); i++)
    {
        DataPoint& d = data[i];
        d.selected = false;
        for (int j = 0; j < polylines.size(); j++)
        {
            ofPolyline& poly = polylines[j];
            cout << poly.isClosed() << endl;
            if (poly.inside(d.point * ofPoint(ofGetWidth(), ofGetHeight())))
            {
                d.selected = true;
                numSelected++;
                cout << "selected" << endl;
            }
        }
    }
}

void ofApp::saveSelected() {
    ofxJSONElement json;
    for(int i = 0; i < data.size(); i++)
    {
        DataPoint& d = data[i];
        if (d.selected)
        {
            ofxJSONElement j;
            j["id"] = d.id;
            j["point"]["x"] = d.point.x;
            j["point"]["y"] = d.point.y;
            json.append(j);
        }
    }

    string filename = "selection_" + ofGetTimestampString() + ".json";
    if(json.save(filename))
    {
        cout << ("saved " + ofToString(numSelected)) << " point to " << filename << endl;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // left mouse button
    if (button == 0) {
        if (polylines.size() == 0) {
            ofPolyline poly;
            poly.addVertex(x, y);
            polylines.push_back(poly);
            cout << "line added at " << ofPoint(x, y) << endl;
        }
        // append to existing polyline
        else if (!ofGetKeyPressed(OF_KEY_SHIFT))
        {
            ofPolyline& poly = polylines[polylines.size() - 1];
            if (poly.isClosed()) {
                ofPolyline p;
                p.addVertex(x, y);
                polylines.push_back(p);
            } else {
                poly.addVertex(x, y);
                cout << "adding vertex at " << ofPoint(x, y) << endl;
            }
        }
        // shift pressed, create a new polyline
//        else
//        {
//            // close the existing polyine
//            if (polylines.size() > 0)
//            {
//                polylines[polylines.size() - 1].close();
//                updateSelected();
//            }

//            ofPolyline poly;
//            poly.addVertex(x, y);
//            polylines.push_back(poly);
//        }
    }
    // right mouse button, close shape
    else if (button == 2)
    {
        if (polylines.size() > 0)
        {
            ofPolyline& poly = polylines[polylines.size() - 1];
            poly.close();
            updateSelected();
            cout << "closing polyline" << endl;
        }
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

    for (int i = 0; i < polylines.size(); i++) {
        ofPolyline& poly = polylines[i];
        for (int j = 0; j < poly.getVertices().size(); j++)

            poly.getVertices()[j] *= ofPoint(ofGetWidth(), ofGetHeight());
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
