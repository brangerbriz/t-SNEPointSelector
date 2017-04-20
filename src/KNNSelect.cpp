#include "KNNSelect.h"

float cosine_similarity(float *A, float *B, unsigned int Vector_Length)
{
    float dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
     for(unsigned int i = 0u; i < Vector_Length; ++i) {
        dot += A[i] * B[i] ;
        denom_a += A[i] * A[i] ;
        denom_b += B[i] * B[i] ;
    }
    return dot / (sqrt(denom_a) * sqrt(denom_b)) ;
}

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

vector<pair<int, float> > KNNSelector::getKNearest(int nDIndex, int k, vector<bool> mask)
{
    cout << "Finding " << k << " neighbors near " << nDIndex << endl;
    vector<pair<int, float> > results;
    results.resize(_nDPoints.size());


    vector<vector<float> > nDPoints; // hold masked points
    nDPoints.resize(_nDPoints.size());

    // apply the mask, slow, but it gets the job done.
    for (int i = 0; i < mask.size(); i++)
    {
        if (mask[i])
        {
            for (int j = 0; j < _nDPoints.size(); j++)
            {
                nDPoints[j].push_back(_nDPoints[j][i]);
            }
        }
    }

    float* point = &nDPoints[nDIndex][0];
    for (int i = 0; i < nDPoints.size(); i++)
    {
        if (i == nDIndex) continue;

        float* neighbor = &nDPoints[i][0];
        float dist = 1.0 - cosine_similarity(point, neighbor, nDPoints[i].size());
        results[i] = pair<int, float>(i, dist);
    }

    std::sort(results.begin(), results.end(), [](const pair<int, float>& a, const pair<int, float>& b) { return a.second < b.second; });
    vector<pair<int, float> > res(results.begin(), results.begin() + k);
    return res;
}

vector<ofVec2f>& KNNSelector::get2DPoints()
{
    return _2DPoints;
}

vector<vector<float> >& KNNSelector::getNDPoints()
{
    return _nDPoints;
}
