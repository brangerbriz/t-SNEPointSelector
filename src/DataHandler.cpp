#include "DataHandler.h"

DataHandler::DataHandler()
{

}

void DataHandler::loadFeatures()
{
    _featureNames.clear();
    _features.clear();

    ofBuffer buff = ofBufferFromFile("lmd_features.csv");
    int i = 0;
    for (ofBuffer::Line it = buff.getLines().begin(); it != buff.getLines().end(); it++)
    {
        std::vector<std::string> vals = ofSplitString(*it, ",");
        if (i == 0)
        {
            // hacky bullshit to get the equivalent of vector::pop_front()
            std::reverse(std::begin(vals), std::end(vals));
            vals.pop_back();
            std::reverse(std::begin(vals), std::end(vals));
            _featureNames = vals;
        }
        else
        {
            if (vals.size() > 1) {
                _fileIdentifiers.push_back(vals[1]);

                vector<float> feats;
                for (int j = 2; j < vals.size(); j++)
                {
                    feats.push_back(std::stof(vals[j]));
                }
                _features.push_back(feats);
            }
        }
        i++;
    }

//    cout << "size of featureNames: " << _featureNames.size() << endl;
//    cout << "number of rows: " << _features.size() << endl;
}

void DataHandler::loadTSNEPoints()
{
    _points.clear();
    ofBuffer buff = ofBufferFromFile("t-SNE_points.csv");
    for (ofBuffer::Line it = buff.getLines().begin(); it != buff.getLines().end(); it++)
    {
        std::vector<std::string> vals = ofSplitString(*it, ",");
        TSNEPoint d;
        if (vals[0] != "")
        {
            d.id = std::stoi(vals[0]);
            d.point.set(std::stof(vals[1]), std::stof(vals[2]));
            _points.push_back(d);
        }
    }
}

void DataHandler::loadTSNESelections()
{
    if (ofFile::doesFileExist("t-SNE_selections.csv"))
    {
        ofBuffer buff = ofBufferFromFile("t-SNE_selections.csv");
        for (ofBuffer::Line it = buff.getLines().begin(); it != buff.getLines().end(); it++)
        {
            std::vector<std::string> row = ofSplitString(*it, ",");
            // validate and ignore column row
            if (row.size() == 2 && row[1] != "points") {
                TSNESelection sel;
                sel.poly = _stringToPoly(row[1]);
                _selections.push_back(sel);
            }
        }
    }
}

void DataHandler::saveTSNESelections(const vector<TSNESelection>& selections){

    string csv = ",id,group\n";
    int rowIndex = 0;
    for (int i = 0; i < selections.size(); i++)
    {
        const TSNESelection& sel = selections[i];
        for (auto point : _points) {
            if (sel.poly.inside(point.point))
            {
                csv += ofToString(rowIndex) + "," + ofToString(point.id) + "," + ofToString(i) + "\n";
                rowIndex++;
            }
        }
    }

    ofBuffer buff(csv);
    ofBufferToFile("t-SNE_selection_data.csv", buff);

    csv = ",points\n";
    for (int i = 0; i < selections.size(); i++)
    {
        csv += ofToString(i) + "," + _polyToString(selections[i].poly) + "\n";
    }

    ofBuffer buff2(csv);
    ofBufferToFile("t-SNE_selections.csv", buff2);
}

string DataHandler::_polyToString(const ofPolyline poly)
{
    string str = "";
    for (int i = 0; i < poly.getVertices().size(); i++)
    {
       const ofPoint& vert = poly.getVertices()[i];
       str += "|" + ofToString(vert[0]) + "^" + ofToString(vert[1]);
    }
    return str;
}

ofPolyline DataHandler::_stringToPoly(string str)
{
    ofPolyline poly;
    auto points = ofSplitString(str, "|", true, true);
    for (auto point : points)
    {
        auto p = ofSplitString(point, "^");
        if (p.size() == 2) {
            poly.addVertex(std::stof(p[0]), std::stof(p[1]));
//            cout << p[0] << ", " << p[1] << endl;
        }
    }
    poly.close();
    return poly;
}

vector<TSNESelection>& DataHandler::getTSNESelections()
{
    return _selections;
}

const vector<string>& DataHandler::getFeatureNames() const
{
    return _featureNames;
}

const vector<TSNEPoint>& DataHandler::getTSNEPoints() const
{
    return _points;
}
