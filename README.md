# t-SNEPointSelector
OpenFrameworks app for interactively labeling t-SNE clusters and KNN searches for features extracted from the lakh midi dataset.

## Building

t-SNEPointSelector was built with OpenFrameworks v0.9.8. Its compatibility with other versions of OF is untested.

### ofxAddons
The following addons are required to build the app:

```
ofxGui
ofxJSON
ofxSpatialHash
ofxThreadedMidiPlayer
ofxMidi
```
### Data

Four large asset files need to be downloaded and unzipped into `/bin/data` before running the app. You can find those on the [release page](https://github.com/brangerbriz/t-SNEPointSelector/releases):

- [lmd_features.csv.tar.gz](https://github.com/brangerbriz/t-SNEPointSelector/releases/download/data/lmd_features.csv.tar.gz)
- [lmd_mono_tracks_features.csv.tar.gz](https://github.com/brangerbriz/t-SNEPointSelector/releases/download/data/lmd_mono_tracks_features.csv.tar.gz)
- [lmd_midi.tar.gz](https://github.com/brangerbriz/t-SNEPointSelector/releases/download/data/lmd_midi.tar.gz)
- [lmd_mono_tracks_seperated.tar.gz](https://github.com/brangerbriz/t-SNEPointSelector/releases/download/data/lmd_mono_tracks_seperated.tar.gz)

## Using t-SNEPointSelector

The current version of this project is INCREDIBLY experimental. Little to no though has gone into making it have a pleasant user interface. It has evolved naturally as a research tool and may be somewhat impenetrable for others trying to make use of it at the moment. That said, below is a brief description of some of the features.

- Click a point to select a midi file.
- Press the "p" key to play that midi file through your computer's midi-through port.
- Press the "s" key to stop playing a midi file. It is recommended that you explicitly stop a midi file before you play another to keep from having hung notes that continue to play.
- Once a midi note has been selected, press the "search" button on the UI panel to execute a K-nearest neighbor search. Only features that are enabled in the UI panel will be applied to the search. Enable/disable features to alter your search in different ways.
- Press "save" to save your current search to csv (`bin/data/knn_searches`)
- Pressing "g" toggles between KNN search mode (you see the GUI) and labeling mode (you don't see the GUI). In labeling mode, left mouse click to draw shapes around data points and right mouse click to close those shapes. Once you've "labeled" data points, labels can be saved to a csv in `bin/data/t-sne_selections` by pressing ENTER.

## Two Datasets

Two datasets are currently supported by this applications. The first, is the entire [Lakh Midi Dataset](http://colinraffel.com/projects/lmd/) (LMD). The second is a collection of all monophonic tracks (seperated from their original Midi files) in LMD.

To switch between them, enable/disable the pre-processor directive `MONO_TRACKS` in `defines.h`.
