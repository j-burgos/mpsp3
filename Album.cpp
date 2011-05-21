
#include "Album.h"

Album::Album() {
}
Album::Album(string title, string year, string genre, string dir, Artist a){
    this->title = title;
    this->year = year;
    this->genre = genre;
    this->dir = dir;
    this->artist = a;
}
Album::Album(const Album& orig) {
}

Album::~Album() {
    this->artist=Artist();
}
void Album::SetDir(string dir) {
    this->dir = dir;
}
string Album::GetDir() const {
    return dir;
}
void Album::SetGenre(string genre) {
    this->genre = genre;
}
string Album::GetGenre() const {
    return genre;
}
void Album::SetYear(string year) {
    this->year = year;
}
string Album::GetYear() const {
    return year;
}
void Album::SetTitle(string title) {
    this->title = title;
}
string Album::GetTitle() const {
    return title;
}
void Album::SetArtist(Artist& artist) {
    this->artist = artist;
}
Artist& Album::GetArtist() {
    return artist;
}

