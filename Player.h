

#ifndef _PLAYER_H
#define	_PLAYER_H

#include <sstream>
#include <iomanip>
#include "List.cpp"
#include "AppException.h"
#include "Audio.h"
#include "AudioMPEG.h"
#include "Song.h"

class Player {
public:

    Player();
    Player(const Player& orig);
    virtual ~Player();

    void load();
    void togglePlayPause();
    void stop();
    void next();
    void previous();
    void unload();
    
    void setSongs(List<Song>& playlist);
    List<Song>& getSongs();
    void setCurrent(int current);
    int getCurrent() const;

    string getCurrentTime();
    int getCurrentTimeInt();
    string getKbps();
    string getLength();
    int getLengthInt();

    string getSongStatus();
    void seekTime(int time);

private:
    int current;
    List<Song> songs;
    PAudio currentSong;
};

#endif	/* _PLAYER_H */

