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
        ofTranslate(-_scale_offset);
        ofTranslate(-_offset);
        ofScale(ofGetWidth() * _scale, ofGetHeight() * _scale, 0);
}

void NavTransformer::end()
{
    ofPopMatrix();
}

ofPoint NavTransformer::toDataSpace(ofPoint p)
{
    p += _scale_offset + _offset;
    p /= (ofPoint(ofGetWidth(), ofGetHeight()) * _scale);
    return p;
}

ofPoint NavTransformer::fromDataSpace(ofPoint p)
{
    p -= _scale_offset + _offset;
    p *= (ofPoint(ofGetWidth(), ofGetHeight()) * _scale);
    return p;
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
//    float scrollSpeed = 0.1;
    _scale = args.scrollY == 1 ? _scale * 2.0 : _scale * 0.5;
    _scale_offset.x = (ofGetWidth() * 0.5) * (_scale - 1);
    _scale_offset.y = (ofGetHeight() * 0.5) * (_scale - 1);

}
