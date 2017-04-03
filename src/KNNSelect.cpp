#include "KNNSelect.h"
KNNSelector::KNNSelector():
    _2DHash(_2DPoints)
{

}

void KNNSelector::index()
{
    _2DHash.buildIndex();
}

ofx::KDTree<ofVec2f>::SearchResults KNNSelector::getKNearest2D(ofPoint point, int k)
{
    _2DHashResults.clear();
    _2DHashResults.reserve(k);
    _2DHash.findNClosestPoints(point, k, _2DHashResults);
    return _2DHashResults;
}

vector<ofVec2f>& KNNSelector::get2DPoints()
{
    return _2DPoints;
}
