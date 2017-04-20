#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    dataHand.loadFeatures();
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
    knnSelector.getNDPoints() = dataHand.getFeatures();
    knnSelector.index();

    for (int i = 0; i < points.size(); i++)
    {
        mesh.addVertex(points[i].point);
    }

    mesh.setMode(OF_PRIMITIVE_POINTS);

    gui.setup(dataHand.getFeatureNames());
    gui.getKnnSearchButton().addListener(this, &ofApp::knnSearch);
    gui.getKnnSaveButton().addListener(this, &ofApp::knnSave);

    cout << "Loaded " << points.size() << " data points" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    gui.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(50);

    navTransform.begin();

        ofSetColor(255);
        glPointSize(2.0);
        mesh.draw();
        tsneSelector.draw();

        glPointSize(15.0);
        // Draw K nearest neighbors
        ofMesh neighborMesh;
        neighborMesh.setMode(OF_PRIMITIVE_POINTS);
        ofSetColor(255);

        ofColor near = ofColor::fromHex(0xFFB101);
        ofColor far = ofColor::fromHex(0x4533A3);

        // draw the nearest n points
        for (auto neighbor : neighbors)
        {
            neighborMesh.addVertex(mesh.getVertices()[neighbor.first]);
            float min = 0.0001;
            float max = 0.0100;
            neighborMesh.addColor(near.getLerped(far, ofMap(ofClamp(neighbor.second, min, max), min, max, 0.0, 1.0)));
        }

        neighborMesh.draw();

        // draw the currently selected point
        string selected = gui.getSelectedFile();
        if (!selected.empty())
        {
            ofMesh pointMesh;
            pointMesh.setMode(OF_PRIMITIVE_POINTS);
            ofVec3f v = knnSelector.get2DPoints()[dataHand.getMidiIndexFromIdentifier(selected)];
            pointMesh.addVertex(v);
            ofSetColor(255, 0, 0);
            pointMesh.draw();
        }

        // draw the nearest point
        ofPoint mouse(ofGetMouseX(), ofGetMouseY());
        auto results = knnSelector.getKNearest2D(navTransform.toDataSpace(mouse), 1);
        int nearestIndex = results[0].first;
        ofPoint p = mesh.getVertices()[nearestIndex];
        ofMesh pointMesh;
        pointMesh.setMode(OF_PRIMITIVE_POINTS);
        pointMesh.addVertex(p);

        ofSetColor(255, 255, 0);
        pointMesh.draw();


    navTransform.end();
    gui.draw();
}

void ofApp::knnSearch()
{

    string id = gui.getSelectedFile();
    if (!id.empty())
    {
        int index = dataHand.getMidiIndexFromIdentifier(id);
        neighbors = knnSelector.getKNearest(index, gui.getNumNeighbors(), gui.getFeatureMask());
        vector<pair<string, float>> labels;
        // weird bug, neighbors[0] always has value 0, 0, so skip it.
        for (int i = 1; i < neighbors.size(); i++)
        {
            labels.push_back(pair<string, float>(dataHand.getMidiIdentifier(neighbors[i].first), neighbors[i].second));
        }

        gui.setSelectedFiles(dataHand.getMidiIdentifier(index), labels);
    }

}

void ofApp::knnSave()
{
    string selected = gui.getSelectedFile();
    if (!selected.empty() && neighbors.size() > 0)
    {
        dataHand.saveKnnSearch(selected, neighbors, gui.getFeatureMask());
    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    cout << "key pressed: " << key << endl;
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
    // 'g' key
    else if (key == 103 || key == 71)
    {
        gui.toggleEnabled();
    }
    // 'p' key
    else if (key == 112 || key == 80)
    {
        string selected = gui.getSelectedFile();
        if (!selected.empty())
        {
            int index = dataHand.getMidiIndexFromIdentifier(selected);
#ifdef MONO_TRACKS
            string filename = "lmd_mono_tracks_seperated/" + dataHand.getMidiIdentifier(index);
#else
       string filename = "lmd_midi/" + dataHand.getMidiIdentifier(index);
#endif
            cout << "Playing " << filename << endl;
            midiPlayer.play(filename);
        }
    }
    // 's' key
    else if (key == 115)
    {
        midiPlayer.stop();
    }
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // left mouse button
    if (button == 0)
    {
        if (!gui.isEnabled())
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
        else
        {
            // draw the nearest point
            vector<pair<string, float>> labels;
            labels.resize(gui.getNumNeighbors());
            ofPoint mouse(ofGetMouseX(), ofGetMouseY());
            auto results = knnSelector.getKNearest2D(navTransform.toDataSpace(mouse), 1);
            gui.setSelectedFiles(dataHand.getMidiIdentifier(results[0].first), labels);
//            neighbors.clear();
        }
    }
    // right mouse button, close shape
    else if (button == 2)
    {
        if (!gui.isEnabled())
        {
            tsneSelector.endSelection();
        }
    }
}

