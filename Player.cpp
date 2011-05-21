
#include "Player.h"

Player::Player() {
    this->songs = List<Song>();
    this->current = 0;
    this->currentSong = NULL;
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}
void Player::setSongs(List<Song>& songs) {
    this->songs = songs;
}
List<Song>& Player::getSongs(){
    return songs;
}
void Player::setCurrent(int current) {
    this->current = current;
}
int Player::getCurrent() const {
    return current;
}

string Player::getSongStatus(){
    if(!currentSong) return "";
    int status =getPlayAudio(currentSong);
    if(status == PLAYING) return "Reproduciendo";
    if(status == STOP) return "Detenido";
    if(status == PAUSED) return "Pausado";
}

string Player::getCurrentTime(){
    if(!currentSong) return "00:00";
    int time_secs = (int) getTimeAudio(currentSong,SZ_SECONDS)/1000 ;
    int min = time_secs/60;
    int secs = time_secs - min*60;
    stringstream s;
    s << min << ":";
    s << setfill('0') << setw(2) << secs;
    return s.str();
}
int Player::getCurrentTimeInt(){
    if(!currentSong) return 0;
    return (int)getTimeAudio(currentSong,SZ_SECONDS)/1000;
}

string Player::getLength(){
    if(!currentSong) return "00:00";
    int time_secs = (int) getLengthAudio(currentSong,SZ_SECONDS)/1000 ;
    int min = time_secs/60;
    int secs = time_secs - min*60;
    stringstream s;
    s << min << ":";
    s << setfill('0') << setw(2) << secs;
    return s.str();
}

string Player::getKbps(){
    if(!currentSong) return "Desconocido";
    int bitrate = (int) getBitrateAudio(currentSong)/1000;
    stringstream s;
    s << bitrate << " kbps";
    return s.str();
}

int Player::getLengthInt(){
    if(!currentSong) return 0;
    return (int)getLengthAudio(currentSong,SZ_SECONDS)/1000;
}

void Player::seekTime(int time){
    seekAudio(currentSong, time*1000, SZ_SECONDS, SEEK_CUR);
}

void Player::load(){
    string fullpath = this->songs.get(current).GetAlbum().GetDir() +
            this->songs.get(current).GetFilename();
    PAudio mp3 = loadMp3((char*)fullpath.c_str(), STREAM_FROM_FILE);
    if(!mp3) throw AppException("Mp3PlayerException", "No se pudo cargar el archivo: "+fullpath);
    this->currentSong = mp3;
}

void Player::togglePlayPause(){
    if(currentSong) pauseAudio2(this->currentSong);
}

void Player::stop(){
    if(currentSong) stopAudio(this->currentSong);
}

void Player::next(){
    int next_song = this->current + 1;
    if(next_song <= this->songs.size() - 1){
        stop();
        unload();
        this->current = next_song;
        load();
        togglePlayPause();
    }
}

void Player::unload(){
    if(currentSong) freeAudio(currentSong);
}

void Player::previous(){
    int prev_song = this->current - 1;
    if(prev_song >= 0){
        stop();
        unload();
        this->current = prev_song;
        load();
        togglePlayPause();
    }
}
