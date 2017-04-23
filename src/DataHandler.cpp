#include "DataHandler.h"

DataHandler::DataHandler()
{

}

void DataHandler::loadFeatures()
{
    _featureNames.clear();
    _features.clear();
#ifdef MONO_TRACKS
    ofBuffer buff = ofBufferFromFile("lmd_mono_tracks_features.csv");
    cout << "MONO" << endl;
#else
    ofBuffer buff = ofBufferFromFile("lmd_features.csv");
    cout << "NO MONO" << endl;
#endif
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
#ifdef MONO_TRACKS
    ofBuffer buff = ofBufferFromFile("t-SNE_points_mono.csv");
#else
    ofBuffer buff = ofBufferFromFile("t-SNE_points.csv");
#endif
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

    ofBuffer buff;
    buff.set(csv);
    ofBufferToFile("t-SNE_selection_data.csv", buff);

    csv = ",points\n";
    for (int i = 0; i < selections.size(); i++)
    {
        csv += ofToString(i) + "," + _polyToString(selections[i].poly) + "\n";
    }

    ofBuffer buff2;
    buff2.set(csv);
    ofBufferToFile("t-SNE_selections.csv", buff2);
}

void DataHandler::saveKnnSearch(string selected, const vector<pair<int, float> >& neighbors, const vector<bool>& featureMask)
{
    string csv = ",id,neighbor_id,distance\n";
    for (int i = 0; i < neighbors.size(); i++)
    {
        string neighborId = getMidiIdentifier(neighbors[i].first);
        string distance = ofToString(neighbors[i].second);
        csv += ofToString(i) + "," + selected + "," + neighborId + "," + distance + "\n";
    }

    ofBuffer buff;
    buff.set(csv);
    string filename = "knn_searches/knn_" + selected + ".csv";
    ofBufferToFile(filename, buff);
    ofSystem("python ~/" + ofToDataPath("knn_search_to_symlink.py") +  " " + filename);
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

const vector<vector<float>>& DataHandler::getFeatures() const
{
    return _features;
}

//const vector<vector<float>> DataHandler::getFeatures(vector<vector<float>> mask) const
//{

//}

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

string DataHandler::getMidiIdentifier(int index)
{
    return _fileIdentifiers[index];
}

int DataHandler::getMidiIndexFromIdentifier(string id)
{
    for (int i = 0; i < _fileIdentifiers.size(); i++)
    {
        if (_fileIdentifiers[i] == id)
        {
            return i;
        }
    }

    return -1;
}
