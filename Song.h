

#ifndef _SONG_H
#define	_SONG_H

#include <string>

#include "Album.h"

using namespace std;
class Song {
public:
    Song();
    Song(string title, string filename, string track,
        string kbps, string size, string length, Album a);
    Song(const Song& orig);
    virtual ~Song();

    void SetTrack(string track);
    string GetTrack() const;
    void SetKbps(string kbps);
    string GetKbps() const;
    void SetSize(string size);
    string GetSize() const;
    void SetLength(string length);
    string GetLength() const;
    void SetFilename(string filename);
    string GetFilename() const;
    void SetTitle(string title);
    string GetTitle() const;
    void SetAlbum(Album& album);
    Album& GetAlbum();
    
private:
    string title;
    string filename;
    string length;
    string size;
    string kbps;
    string track;
    Album album;
};

#endif	/* _SONG_H */

