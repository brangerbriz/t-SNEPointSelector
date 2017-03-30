#include "NavTransformer.h"

NavTransformer::NavTransformer():
    _offset(0.0, 0.0),
    _scale_offset(0.0, 0.0),
    _scale(1.0)
{
    ofAddListener(ofEvents().keyPressed, this, &NavTransformer::keyPressed);
    ofAddListener(ofEvents().mouseScrolled, this, &NavTransformer::mouseScrolled);
}

NavTransformer::~NavTransformer()
{
    ofRemoveListener(ofEvents().keyPressed, this, &NavTransformer::keyPressed);
    ofAddListener(ofEvents().mouseScrolled, this, &NavTransformer::mouseScrolled);
}

void NavTransformer::begin()
{
    ofPushMatrix();
        ofTranslate(-_offset);
        ofTranslate(-_scale_offset);
        ofScale(ofGetWidth() * _scale, ofGetHeight() * _scale, 0);
}

void NavTransformer::end()
{
    ofPopMatrix();
}

void NavTransformer::keyPressed(ofKeyEventArgs &key)
{
    float moveSpeed = 20 * _scale;
    if (key.key == OF_KEY_LEFT)  _offset.x -= moveSpeed;
    if (key.key == OF_KEY_RIGHT) _offset.x += moveSpeed;
    if (key.key == OF_KEY_UP)    _offset.y -= moveSpeed;
    if (key.key == OF_KEY_DOWN)  _offset.y += moveSpeed;
}

void NavTransformer::mouseScrolled(ofMouseEventArgs &args)
{
    float scrollSpeed = 0.1;
    _scale += ofMap(args.scrollY, -1, 1, -scrollSpeed, scrollSpeed);
    //_offset -= ofPoint(ofGetWidth(), ofGetHeight());
    _scale_offset.x = (ofGetWidth()/2) * (_scale-1);
    _scale_offset.y = (ofGetHeight()/2) * (_scale-1);

}
