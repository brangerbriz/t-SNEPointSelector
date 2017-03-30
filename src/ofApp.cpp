#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    numSelected = 0;

    // CSV
    ofBuffer buff = ofBufferFromFile("t-SNE_points.csv");

    for (ofBuffer::Line it = buff.getLines().begin(); it != buff.getLines().end(); it++) {
        std::vector<std::string> vals = ofSplitString(*it, ",");
        tSNEPoint d;
        if (vals[0] != "") {
            d.id = std::stoi(vals[0]);
            d.point.set(std::stof(vals[1]), std::stof(vals[2]));
            data.push_back(d);
            mesh.addVertex(d.point);
        }
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

    ofSetColor(255);
    drawPolylines();

    navTransform.begin();
    mesh.draw();
    navTransform.end();

    string str = "selected: " + ofToString(numSelected);
    ofDrawBitmapStringHighlight(str, 15, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {

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
        tSNEPoint& d = data[i];
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
        tSNEPoint& d = data[i];
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
