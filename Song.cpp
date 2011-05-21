

#include "Song.h"

Song::Song() {
}
Song::Song(string title, string filename, string track,
        string kbps, string size, string length, Album a){
    this->title = title;
    this->filename = filename;
    this->track = track;
    this->kbps = kbps;
    this->size = size;
    this->length = length;
    this->album = a;
}
Song::Song(const Song& orig) {
}

Song::~Song() {
    this->album = Album();
}
void Song::SetTrack(string track) {
    this->track = track;
}
string Song::GetTrack() const {
    return track;
}
void Song::SetKbps(string kbps) {
    this->kbps = kbps;
}
string Song::GetKbps() const {
    return kbps;
}
void Song::SetSize(string size) {
    this->size = size;
}
string Song::GetSize() const {
    return size;
}
void Song::SetLength(string length) {
    this->length = length;
}
string Song::GetLength() const {
    return length;
}
void Song::SetFilename(string filename) {
    this->filename = filename;
}
string Song::GetFilename() const {
    return filename;
}
void Song::SetTitle(string title) {
    this->title = title;
}
string Song::GetTitle() const {
    return title;
}
void Song::SetAlbum(Album& album) {
    this->album = album;
}
Album& Song::GetAlbum() {
    return album;
}

