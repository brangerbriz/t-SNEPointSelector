#ifndef NAVTRANSFORMER_H
#define NAVTRANSFORMER_H
#include "ofMain.h"

class NavTransformer
{
public:
    NavTransformer();
    ~NavTransformer();
    void begin();
    void end();
    void keyPressed(ofKeyEventArgs &key);
    void mouseScrolled(ofMouseEventArgs &args);
    ofPoint toDataSpace(ofPoint p);
    ofPoint fromDataSpace(ofPoint p);

protected:
    float _scale;
    ofPoint _offset;
    ofPoint _scale_offset;
};

#endif // NAVTRANSFORMER_H
