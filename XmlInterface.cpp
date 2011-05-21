

#include "XmlInterface.h"


XmlInterface::XmlInterface() {
}

XmlInterface::XmlInterface(const XmlInterface& orig) {
}

XmlInterface::~XmlInterface() {
}

/*********Funciones para filtrar***********/
bool sortArtistByName(Artist* a, Artist*b){
    return (a->GetName() < b->GetName());
}
bool sortAlbumByTitle(Album* a, Album* b){
    return (a->GetTitle() < b->GetTitle());
}
bool sortAlbumByGenre(Album* a, Album* b){
    return (a->GetGenre() < b->GetGenre());
}
bool sortAlbumByYear(Album* a, Album* b){
    return (a->GetYear() < b->GetYear());
}
bool sortSongByTitle(Song* a, Song* b){
    return (a->GetTitle() < b->GetTitle());
}
/***********/

string formatSongLength(int songLength){
    int min = 0;
    int sec = 0;
    min = (int)(songLength/60);
    sec = songLength-min*60;
    stringstream s;
    s << min << ":";
    s << setfill('0') << setw(2) << sec;
    return s.str();
}

List<Artist>* XmlInterface::getArtists(string path, string tag){
    List<Artist>* list = new List<Artist>();
    try{
        Document doc;
        doc.LoadFile(path);
        Element* root = doc.FirstChildElement();
        Iterator<Element> child(tag);
        for ( child = child.begin(root); child != child.end(); child++ ){
            list->addLast(Artist(child.Get()->GetAttribute("artist")));
        }
        if(list->size()>0) list->sort(sortArtistByName);
        return list;
    }catch(ticpp::Exception& e){
        delete list;
        throw AppException("XMLParsing",string(e.what()));
    }
}
List<Album>* XmlInterface::getAlbums(string path, string tag) {
    List<Album>* list = new List<Album > ();
    try {
        
        Document doc;
        doc.LoadFile(path);

        Element* root = doc.FirstChildElement();
        Iterator<Element> artist_it;
        for (artist_it = artist_it.begin(root); artist_it != artist_it.end(); artist_it++) {

            Element* e_album = artist_it.Get()->ToElement();
            Iterator<Element> album_it(tag);
            for (album_it = album_it.begin(e_album); album_it != album_it.end(); album_it++) {

                list->addLast(
                        Album(
                        album_it.Get()->GetAttribute("album"),
                        album_it.Get()->GetAttribute("year"),
                        album_it.Get()->GetAttribute("genre"),
                        album_it.Get()->GetAttribute("dir"),
                        Artist(artist_it.Get()->GetAttribute("artist"))
                        )
                );
            }
        }
        if(list->size()>0) list->sort(sortAlbumByTitle);
        return list;
    } catch (ticpp::Exception& e) {
        throw AppException("XMLParsing", string(e.what()));
    }
}
List<Album>* XmlInterface::getAlbumsByAttr(string path, string tag, string attr) {
    List<Album>* list = new List<Album > ();
    List<string> lvalues;
    try {
        string attr_val;
        
        Document doc;
        doc.LoadFile(path);

        Element* root = doc.FirstChildElement();
        Iterator<Element> artist_it;
        for (artist_it = artist_it.begin(root); artist_it != artist_it.end(); artist_it++) {

            Element* e_album = artist_it.Get()->ToElement();
            Iterator<Element> album_it(tag);
            for (album_it = album_it.begin(e_album); album_it != album_it.end(); album_it++) {
                attr_val = album_it.Get()->GetAttribute(attr);
                if(!lvalues.exists(&attr_val)){
                    lvalues.addLast(attr_val);
                    list->addLast(
                            Album(
                        album_it.Get()->GetAttribute("album"),
                        album_it.Get()->GetAttribute("year"),
                        album_it.Get()->GetAttribute("genre"),
                        album_it.Get()->GetAttribute("dir"),
                        Artist(artist_it.Get()->GetAttribute("artist"))
                        ));
                }
            }
        }
        if(list->size()>0){
            if(attr == "album") list->sort(sortAlbumByTitle);
            if(attr == "genre") list->sort(sortAlbumByGenre);
            if(attr == "year") list->sort(sortAlbumByYear);
        }
        return list;
    } catch (ticpp::Exception& e) {
        delete list;
        throw AppException("XMLParsing", string(e.what()));
    }
}

List<Song>* XmlInterface::getSongs(string path, string tag){
    List<Song>* list = new List<Song> ();
    try {
        int length = 0;
        Document doc;
        doc.LoadFile(path);

        Element* root = doc.FirstChildElement();
        Iterator<Element> artist_it;
        for (artist_it = artist_it.begin(root); artist_it != artist_it.end(); artist_it++) {

            Element* e_album = artist_it.Get()->ToElement();
            Iterator<Element> album_it;
            for (album_it = album_it.begin(e_album); album_it != album_it.end(); album_it++) {

                Element* e_song = album_it.Get()->ToElement();
                Iterator<Element> song_it(tag);
                for (song_it = song_it.begin(e_song); song_it != song_it.end(); song_it++) {
                    song_it.Get()->GetAttribute("length",&length);
                    list->addLast(
                            Song(
                            song_it.Get()->GetAttribute("title"),
                            song_it.Get()->GetAttribute("filename"),
                            song_it.Get()->GetAttribute("track"),
                            song_it.Get()->GetAttribute("kbps"),
                            song_it.Get()->GetAttribute("size"),
                            formatSongLength(length),
                            Album(
                            album_it.Get()->GetAttribute("album"),
                            album_it.Get()->GetAttribute("year"),
                            album_it.Get()->GetAttribute("genre"),
                            album_it.Get()->GetAttribute("dir"),
                            Artist(
                            artist_it.Get()->GetAttribute("artist")
                            ))));
                }
            }
        }
        
        return list;
    }catch (ticpp::Exception& e) {
        delete list;
        throw AppException("XMLParsing", string(e.what()));
    }
}
List<Song>* XmlInterface::getPlaylistSongs(string path, string tag){
    List<Song>* list = new List<Song> ();
    try {
        int length = 0;
        Document doc;
        doc.LoadFile(path);

        Element* root = doc.FirstChildElement();
        Iterator<Element> song_it(tag);
        for (song_it = song_it.begin(root); song_it != song_it.end(); song_it++) {
            song_it.Get()->GetAttribute("length", &length);
            list->addLast(
                    Song(
                    song_it.Get()->GetAttribute("title"),
                    song_it.Get()->GetAttribute("filename"),
                    song_it.Get()->GetAttribute("track"),
                    song_it.Get()->GetAttribute("kbps"),
                    song_it.Get()->GetAttribute("size"),
                    formatSongLength(length),
                    Album(
                    song_it.Get()->GetAttribute("album"),
                    song_it.Get()->GetAttribute("year"),
                    song_it.Get()->GetAttribute("genre"),
                    song_it.Get()->GetAttribute("dir"),
                    Artist(
                    song_it.Get()->GetAttribute("artist")
                    ))));
        }
        return list;
    } catch (ticpp::Exception& e) {
        delete list;
        throw AppException("XMLParsing", string(e.what()));
    }
}
List<Song>* XmlInterface::getSongsByArtist(string path, string tag, string artist_attr, string attr_value){
    List<Song>* list = new List<Song>();
    try{
        Document doc;
        doc.LoadFile(path);
        Element* root = doc.FirstChildElement();
        int length = 0;
        bool found = false;
        Element* artist_elem;
        Iterator<Element> artist_it;
        for ( artist_it = artist_it.begin(root); artist_it != artist_it.end(); artist_it++ ){
            if( artist_it.Get()->GetAttribute(artist_attr) == attr_value){
                artist_elem = artist_it.Get()->ToElement();
                found = true;
            }
        }
        if(!found) return list;
        Iterator<Element> album_it;
        for (album_it = album_it.begin(artist_elem); album_it != album_it.end(); album_it++) {

            Element* e_album = album_it.Get()->ToElement();
            Iterator<Element> song_it(tag);
            for (song_it = song_it.begin(e_album); song_it != song_it.end(); song_it++) {
                song_it.Get()->GetAttribute("length", &length);
                list->addLast(
                        Song(
                        song_it.Get()->GetAttribute("title"),
                        song_it.Get()->GetAttribute("filename"),
                        song_it.Get()->GetAttribute("track"),
                        song_it.Get()->GetAttribute("kbps"),
                        song_it.Get()->GetAttribute("size"),
                        formatSongLength(length),
                        Album(
                        album_it.Get()->GetAttribute("album"),
                        album_it.Get()->GetAttribute("year"),
                        album_it.Get()->GetAttribute("genre"),
                        album_it.Get()->GetAttribute("dir"),
                        Artist(
                        artist_elem->GetAttribute("artist")
                        ))));
            }
        }
        return list;
    }catch(ticpp::Exception& e){
        delete list;
        throw AppException("XMLParsing",string(e.what()));
    }
}
List<Song>* XmlInterface::getSongsByAlbum(string path, string tag, string album_attr, string attr_value){
    List<Song>* list = new List<Song> ();
    try {
        int length = 0;
        Document doc;
        doc.LoadFile(path);
        Element* root = doc.FirstChildElement();
        Iterator<Element> artist_it;
        for (artist_it = artist_it.begin(root); artist_it != artist_it.end(); artist_it++) {

            Element* e_album = artist_it.Get()->ToElement();
            Iterator<Element> album_it;
            for (album_it = album_it.begin(e_album); album_it != album_it.end(); album_it++) {
                if(album_it.Get()->GetAttribute(album_attr) == attr_value){

                    Element* e_song = album_it.Get()->ToElement();
                    Iterator<Element> song_it;
                    for (song_it = song_it.begin(e_song); song_it != song_it.end(); song_it++) {
                        song_it.Get()->GetAttribute("length", &length);
                        list->addLast(
                                Song(
                                song_it.Get()->GetAttribute("title"),
                                song_it.Get()->GetAttribute("filename"),
                                song_it.Get()->GetAttribute("track"),
                                song_it.Get()->GetAttribute("kbps"),
                                song_it.Get()->GetAttribute("size"),
                                formatSongLength(length),
                                Album(
                                album_it.Get()->GetAttribute("album"),
                                album_it.Get()->GetAttribute("year"),
                                album_it.Get()->GetAttribute("genre"),
                                album_it.Get()->GetAttribute("dir"),
                                Artist(
                                artist_it.Get()->GetAttribute("artist")
                                ))));
                    }
                }
            }
        }
        return list;
    } catch (ticpp::Exception& e) {
        delete list;
        throw AppException("XMLParsing", string(e.what()));
    }
}