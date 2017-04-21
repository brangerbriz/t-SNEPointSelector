#ifndef KNNSELECT_H
#define KNNSELECT_H
#include "ofxSpatialHash.h"
#include "ofMain.h"

class KNNSelector
{
public:

    KNNSelector();
    void index();
    ofx::KDTree<ofVec2f>::SearchResults getKNearest2D(ofVec2f point, int k);
    vector<pair<int, float>> getKNearest(int nDIndex, int k, vector<bool> mask);
    vector<ofVec2f>& get2DPoints();
    vector<vector<float> >& getNDPoints();

protected:
    ofx::KDTree<ofVec2f> _2DHash;
    ofx::KDTree<ofVec2f>::SearchResults _2DHashResults;
    vector<ofVec2f> _2DPoints;
    vector<vector<float> > _nDPoints;

};

#endif // KNNSELECT_H
