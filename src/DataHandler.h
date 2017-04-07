#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include "ofMain.h"
#include "TSNESelect.h"

struct TSNEPoint {
public:
    int id;
    ofPoint point;
    bool selected;
};

class DataHandler
{
public:

    DataHandler();
    void loadFeatures();
    void loadTSNEPoints();
    void loadTSNESelections();
    void saveTSNESelections(const vector<TSNESelection>& selections);

    string getMidiIdentifier(int index);
    int getMidiIndexFromIdentifier(string id);
    const vector<vector<float>>& getFeatures() const;
//    const vector<vector<float>> getFeatures(vector<vector<float>> mask) const;
    const vector<TSNEPoint>& getTSNEPoints() const;
    const vector<string>& getFeatureNames() const;
    vector<TSNESelection>& getTSNESelections();

protected:
    vector<string> _featureNames;
    vector<string> _fileIdentifiers;
    vector<vector<float>> _features;
    vector<TSNEPoint> _points;
    vector<TSNESelection> _selections;
    string _polyToString(const ofPolyline poly);
    ofPolyline _stringToPoly(string str);
};

#endif // DATAHANDLER_H
