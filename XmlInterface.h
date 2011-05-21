

#ifndef _XMLINTERFACE_H
#define	_XMLINTERFACE_H

#define TIXML_USE_TICPP
#include <ticpp/ticpp.h>
#include <string>
#include <iomanip>
#include <sstream>

#include "List.cpp"
#include "AppException.h"
#include "Artist.h"
#include "Album.h"
#include "Song.h"

using namespace ticpp;
using namespace std;

class XmlInterface {
public:
    XmlInterface();
    XmlInterface(const XmlInterface& orig);
    virtual ~XmlInterface();

    /**Solo para la base de datos*/
    List<Artist>* getArtists(string path, string tag);
    List<Album>* getAlbums(string path, string tag);
    List<Album>* getAlbumsByAttr(string path, string tag, string attr);
    List<Song>* getSongs(string path, string tag);
    /**********/

    List<Song>* getSongsByArtist(string path, string tag, string artist_attr, string attr_value);
    List<Song>* getSongsByAlbum(string path, string tag, string album_attr, string attr_value);

    /*Para una playlist*/
    List<Song>* getPlaylistSongs(string path, string tag);

private:
};

#endif	/* _XMLINTERFACE_H */

