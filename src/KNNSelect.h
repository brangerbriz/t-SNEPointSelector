#ifndef KNNSELECT_H
#define KNNSELECT_H
#include "ofxSpatialHash.h"
#include "ofMain.h"

class KNNSelector
{
public:

    KNNSelector();
    void index();
    ofx::KDTree<ofVec2f>::SearchResults getKNearest2D(ofPoint point, int k);
    vector<ofVec2f>& get2DPoints();

protected:
    ofx::KDTree<ofVec2f> _2DHash;
    ofx::KDTree<ofVec2f>::SearchResults _2DHashResults;
    vector<ofVec2f> _2DPoints;
};

#endif // KNNSELECT_H
