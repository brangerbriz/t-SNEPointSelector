#include "TSNESelect.h"

TSNESelector::TSNESelector():
    _selectionColorIndex(0)
{
    _selectionColors.push_back(ofColor(255,   0,   0, 127));
    _selectionColors.push_back(ofColor(0  , 255,   0, 127));
    _selectionColors.push_back(ofColor(0  ,   0, 255, 127));
    _selectionColors.push_back(ofColor(255, 255,   0, 127));
    _selectionColors.push_back(ofColor(0  , 255, 255, 127));
    _selectionColors.push_back(ofColor(255,   0, 255, 127));
}

void TSNESelector::draw()
{
    ofPushStyle();
    ofFill();
    _selectionColorIndex = 0;
    for (int i = 0; i < _selections.size(); i++)
    {
        ofPolyline& poly = _selections[i].poly;
        // draw the outline
        ofSetLineWidth(2);
        ofSetColor(255);
        poly.draw();
        ofSetColor(_selectionColors[_selectionColorIndex]);

        // draw the fill
        ofBeginShape();
            for( int i = 0; i < poly.getVertices().size(); i++) {
                ofVertex(poly.getVertices().at(i).x, poly.getVertices().at(i).y);
            }
        ofEndShape();
        _selectionColorIndex = (_selectionColorIndex + 1) % _selectionColors.size();
    }
    ofPopStyle();
}

void TSNESelector::beginSelection(ofPoint point)
{
    TSNESelection sel;
    sel.poly.addVertex(point);
    _selections.push_back(sel);
}

void TSNESelector::addPoint(ofPoint point)
{
    if (_selections.size() > 0) {
        TSNESelection& sel = _selections[_selections.size() - 1];
        sel.poly.addVertex(point);
    }
}

void TSNESelector::endSelection()
{
    if (_selections.size() > 0) {
        TSNESelection& sel = _selections[_selections.size() - 1];
        sel.poly.close();
    }
}

bool TSNESelector::selectionPending()
{
    if (_selections.size() < 1) return false;
    else {
        TSNESelection& sel = _selections[_selections.size() - 1];
        return !sel.poly.isClosed();
    }
}

vector<TSNESelection>& TSNESelector::getSelections()
{
    return _selections;
}

TSNESelection::TSNESelection()
{

}
