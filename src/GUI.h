#ifndef GUI_H
#define GUI_H
#include "ofxGui.h"
#include "ofMain.h"

class GUI
{
public:
    GUI();
    void setup(const vector<string>& toggleNames);
    void update();
    void draw();
    void setEnabled(bool enabled=true);
    void setSelectedFiles(string selected, const vector<pair<string, float> >& neighbors);
    void toggleEnabled();
    void printFeatureMask();
    void log(string message);
    bool isEnabled();
    const vector<bool> getFeatureMask();
    int getNumNeighbors();
protected:

    void _updateFeatureMask();
    int _featureIndex2ToggleIndex(int featIndex);
    void _drawLog();

    bool _enabled;
    ofxPanel _panel;
    ofxPanel _filenamePanel;
    ofxPanel _knnPanel;
    ofParameterGroup _featureGroup;
    ofParameterGroup _knnSettingsGroup;
    ofParameterGroup _selectionGroup;
    ofParameterGroup _panelGroup;
    ofParameter<int> _knnNumNeighbors;
    vector<string> _log;
    vector<ofParameter<bool> > _featureToggles;
    vector<ofParameter<string> > _selectedMidiNames;
    vector<bool> _featureMask;
};

#endif // GUI_H
