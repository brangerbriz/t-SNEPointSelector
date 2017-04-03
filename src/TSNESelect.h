#ifndef TSNESELECTION_H
#define TSNESELECTION_H
#include "ofMain.h"

class TSNESelection
{
public:
    TSNESelection();
    ofPolyline poly;

protected:
};

class TSNESelector
{
public:
    TSNESelector();
    void draw();
    void beginSelection(ofPoint point);
    void addPoint(ofPoint point);
    void endSelection();
    bool selectionPending();
    vector<TSNESelection> &getSelections();

protected:
    int _selectionColorIndex;
    vector<ofColor> _selectionColors;
    vector<TSNESelection> _selections;
};

#endif // TSNESELECTION_H
