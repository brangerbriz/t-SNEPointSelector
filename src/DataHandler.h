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
