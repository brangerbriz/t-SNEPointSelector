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
    void loadTSNEPoints();
    void loadTSNESelections();
    void saveTSNESelections(const vector<TSNESelection>& selections);

    const vector<TSNEPoint>& getTSNEPoints() const;
    vector<TSNESelection>& getTSNESelections();

protected:
    vector<TSNEPoint> _points;
    vector<TSNESelection> _selections;
    string _polyToString(const ofPolyline poly);
    ofPolyline _stringToPoly(string str);
};

#endif // DATAHANDLER_H
