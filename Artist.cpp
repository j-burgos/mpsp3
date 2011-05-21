

#include "Artist.h"

Artist::Artist() {
}
Artist::Artist(string name){
    this->name = name;
}

Artist::Artist(const Artist& orig) {
}

Artist::~Artist() {
}
void Artist::SetName(string name) {
    this->name = name;
}
string Artist::GetName() const {
    return name;
}

