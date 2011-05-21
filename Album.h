
#ifndef _ALBUM_H
#define	_ALBUM_H

#include <string>

#include "Artist.h"

using namespace std;
class Album {
public:
    Album();
    Album(string title, string year, string genre, string dir, Artist a);
    Album(const Album& orig);
    virtual ~Album();

    void SetDir(string dir);
    string GetDir() const;
    void SetGenre(string genre);
    string GetGenre() const;
    void SetYear(string year);
    string GetYear() const;
    void SetTitle(string title);
    string GetTitle() const;
    void SetArtist(Artist& artist);
    Artist& GetArtist() ;
    
private:
    string title;
    string year;
    string genre;
    string dir;
    Artist artist;
};

#endif	/* _ALBUM_H */

