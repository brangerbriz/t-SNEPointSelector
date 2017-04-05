#include "MidiPlayer.h"

MidiPlayer::MidiPlayer():
    _isPlaying(false)
{

}

void MidiPlayer::play(string filename)
{

    if (_isPlaying) {
        _player.stop();
    }

    if (filename != _currentFile)
    {
        int midiPortNumber = 0;
        bool shouldSequenceLoop = false;
        cout << "Setting up player with " << filename << ", " << midiPortNumber << ", " << shouldSequenceLoop << endl;
        _player.setup(filename, midiPortNumber, shouldSequenceLoop);
    }

    cout << "Starting player" << endl;
    // HACK
    ofSystem("aconnect 14:0 129:0");
    _player.start();
    _currentFile = filename;
    _isPlaying = true;
}

void MidiPlayer::stop()
{
    _isPlaying = false;
    _player.stop();
    // HACK
    ofSystem("aconnect -d 14:0 129:0");
}

bool MidiPlayer::isPlaying()
{
    return _isPlaying;
}
