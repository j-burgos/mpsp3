

#include "FileLister.h"

FileLister::FileLister() {
    this->directory = "";
}
FileLister::FileLister(string dir){
    this->directory = dir;
}
FileLister::FileLister(const FileLister& orig) {
}

FileLister::~FileLister() {
}
void FileLister::SetDirectory(string directory) {
    this->directory = directory;
}
string FileLister::GetDirectory() const {
    return directory;
}

string stringToLower(string s){
    string sl = s;
    std::transform(sl.begin(),sl.end(),sl.begin(), ::tolower);
    return sl;
}
bool sortFileEntrys(string* entry1, string* entry2){
    if(*entry1 == "./") return true;
    if(*entry2 == "./") return false;
    return (*entry1 < *entry2);
}

List<string>* FileLister::getDirectories(){
    return getDirectories(this->directory, true);
}
List<string>* FileLister::getDirectories(string dir, bool self){
    List<string>* filelist = new List<string>();
    DIR* dird;
    struct dirent* file_entry;
    dird = opendir(dir.c_str());
    if (!dird) throw AppException("FileIO", "No se pudo abrir el directorio: " + dir);
    while(true) {
        file_entry = readdir(dird);
        if (!file_entry) break;
        if (file_entry->d_stat.st_attr & FIO_SO_IFDIR) {
            string filename(file_entry->d_name);
            if(filename!=".."){
                if(self) filelist->addLast(filename+"/");
                else if(filename!=".") filelist->addLast(filename);
            }
        }
    }
    closedir(dird);
    if(filelist->size() > 0) filelist->sort(sortFileEntrys);
    return filelist;
}

List<string>* FileLister::getFiles(string extension, bool withExtension){
    return getFiles(this->directory,extension, withExtension);
}
List<string>* FileLister::getFiles(string dir, string extension, bool withExtension){
    List<string>* filelist = new List<string>();
    DIR* dird;
    struct dirent* file_entry;
    dird = opendir(dir.c_str());
    if (!dird) throw AppException("FileIO", "No se pudo abrir el directorio: " + dir);
    while(true) {
        file_entry = readdir(dird);
        if (!file_entry) break;
        if (file_entry->d_stat.st_attr & FIO_SO_IFREG) {
            string filename(file_entry->d_name);
            string file_ext="";
            string file_no_ext=filename;
            unsigned int sep_pos = filename.find_last_of('.');
            if(sep_pos != filename.npos){
                file_ext = filename.substr(sep_pos+1,filename.size()-sep_pos-1);
                file_no_ext = filename.substr(0,sep_pos);
            }
            if(extension == ""){
                if(withExtension) filelist->addLast(filename);
                else filelist->addLast(file_no_ext);
            }
            else{
                if(stringToLower(extension) == stringToLower(file_ext)){
                    if(withExtension) filelist->addLast(filename);
                    else filelist->addLast(file_no_ext);
                }
            }
        }
    }
    closedir(dird);
    if(filelist->size() > 0) filelist->sort(sortFileEntrys);
    return filelist;
}