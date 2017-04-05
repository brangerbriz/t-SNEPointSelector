#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H
#include "ofxThreadedMidiPlayer.h"

class MidiPlayer
{
public:
    MidiPlayer();

    void play(string filename);
    void stop();
    bool isPlaying();

protected:
    bool _isPlaying;
    string _currentFile;
    ofxThreadedMidiPlayer _player;
};

#endif // MIDIPLAYER_H
