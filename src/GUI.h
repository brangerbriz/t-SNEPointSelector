#ifndef GUI_H
#define GUI_H
#include "ofxGui.h"

class GUI
{
public:
    GUI();
    void setup(const vector<string>& toggleNames);
    void update();
    void draw();
    void setEnabled(bool enabled=true);
    void toggleEnabled();
    void printFeatureMask();
    bool isEnabled();
    const vector<bool> getFeatureMask();
protected:

    void _updateFeatureMask();
    int _featureIndex2ToggleIndex(int featIndex);

    bool _enabled;
    ofxPanel _panel;
    vector<ofxToggle*> _toggles;
    vector<bool> _featureMask;
};

#endif // GUI_H
